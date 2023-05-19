/*************************************************************************************************
* Clase que permite gestionar los mensajes entrantes y salientes del dispositivo.
* Los mensajes se clasifican segun el ID y el topic.
*************************************************************************************************/

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif


#if !defined(claseMensajeIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseMensajeIncluida

// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

// Librerias de otras clases
#include "claseSensorData.h"
#include "claseFiltroData.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
DynamicJsonDocument jsonBufferMen(1024); // Crear instancia en memoria dinamica para los documentos JSON

class mensaje {
  private:

  public:
  // Variables
  int ID;
  String topic;                                                    // Indica el tipo de mensaje que es
  JsonObject ultimoJsonRecibido = jsonBufferMen.to<JsonObject>();  // almacena el json convertido, convierte el documento en un "JsonObject", tambien puede ser "array"
  String ultimoStringRecibido;                                     // Almecena el String del ultimo mensaje recibido
  String strGenerado;
  bool entregaPendiente = false;

  // Objetos asociados
  sensorData *sensoresAsociados = NULL;
  filtroData *filtrosAsociados = NULL;
  int numeroSensores;
  int numeroFiltros;

  // Funciones
  bool asociarObjetos(sensorData *sensores, filtroData *filtros, int numSensores, int numFiltros);
  String convertirJsonEnString(JsonObject jsonDoc, bool eviarPorSerial2);
  JsonObject convertirStringEnJson(String stringRecibido);
  bool almacenarMensaje(String stringRecibido);
  String generarMensaje(JsonObject jsonDoc);
  int entregarMensajeRecibido(String strEntrante); // funcion que utiliza las demas para entregar el mensaje
  //JsonObject generarMensajeDeConfirmacion();        // incompleto
};
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Funcion para vincular los objetos con el gestor de mensajes
bool mensaje::asociarObjetos(sensorData *sensores, filtroData *filtros, int numSensores, int numFiltros){
  numeroSensores = numSensores;
  numeroFiltros = numFiltros;
  sensoresAsociados = new sensorData[numSensores]; // aparta un espacio en memoria para cada objeto  
  filtrosAsociados = new filtroData[numFiltros];                                                 

  // Agregar sensores:
  for (int i = 0; i < numSensores; i++)
  {
    sensoresAsociados[i] = sensores[i]; // asocia cada uno de los sensores
  }
  // Agregar filtros:
  for (int i = 0; i < numFiltros; i++)
  {
    filtrosAsociados[i] = filtros[i]; // asocia cada uno de los filtros
  }

  return 1;
}

// Esta funcion permite convertir los json en mensajes para enviarlos
String mensaje::convertirJsonEnString(JsonObject jsonDoc, bool eviarPorSerial2 = false){
  String str;
  serializeJson(jsonDoc, str);
  if (eviarPorSerial2) Serial2.println(str);  // enviar al serial2 el mensjae
  return str;
}

// Esta funcion permite convertir los String recibidos en archivos json
JsonObject mensaje::convertirStringEnJson(String stringRecibido){
  //
  DeserializationError error = deserializeJson(jsonBufferMen, stringRecibido);  // verificar // jsonBufferMen
  ultimoJsonRecibido = jsonBufferMen.as<JsonObject>();
  return ultimoJsonRecibido;
  //ultimoJsonRecibido = jsonBufferMen.to<JsonObject>(); // no poner, se borar la informacion
  //Serial.print("Ultimo json: ");
  //Serial.println((const float)jsonBufferMen["voltaje"]);
}


// Funcion para almacenar en el objeto los mensajes recibidos o enviados
bool mensaje::almacenarMensaje(String stringRecibido){
  ultimoStringRecibido = stringRecibido;
  ultimoJsonRecibido = convertirStringEnJson(stringRecibido);

  // Almacenar el tipo de mensaje para poder diferenciarlo
  ID =                 ultimoJsonRecibido["ID"];
  topic = (const char*)ultimoJsonRecibido["topic"];  // (const char*) permite que compile

  return true;
}


// Funcion para generar el mensaje(String) que se envia por serial o por Mesh
String mensaje::generarMensaje(JsonObject jsonDoc){
  serializeJson(jsonDoc, strGenerado);
  return strGenerado;
}

// Funcion para diferenciar tipos de mensajes y dirigir mensaje a cada clase interesada
int mensaje::entregarMensajeRecibido(String strEntrante){
  
  convertirStringEnJson(strEntrante);             // crea el archivo json a partir del string

  // falta verificar el ID

  // Caso 1: Llega paquete de sensores
  if(ultimoJsonRecibido["topic"] == "sensor"){
    for (int i = 0; i < numeroSensores; i++){
      if(ultimoJsonRecibido["tipoDeSensor"] == sensoresAsociados[i].tipoDeSensor){                          // ultimoJsonRecibido["ID"] == sensoresAsociados[i].ID &&  (volver a poner)
        Serial.print("Mensaje de sensor recibido, de: "); Serial.println(sensoresAsociados[i].ID);
        sensoresAsociados[i].guardarDatosRecibidosDeJson(ultimoJsonRecibido); // guardar datos en el objeto correspondiente
        return 1;
      }
    }

  // Caso 2: Llega paquete de filtros
  } else if (ultimoJsonRecibido["topic"] == "filtro"){
    // falta verificar el ID
    for (int i = 0; i < numeroFiltros; i++){
      if(ultimoJsonRecibido["ID"] == filtrosAsociados[i].ID && ultimoJsonRecibido["numeroDeFiltro"] == filtrosAsociados[i].numeroDeFiltro){
        Serial.print("Mensaje de filtro recibido, de: "); Serial.println(filtrosAsociados[i].ID);
        filtrosAsociados[i].guardarDatosRecibidosDeJson(ultimoJsonRecibido); // guardar datos en el objeto correspondiente
        return 2;
      }
    }

  //Caso 3: Llega un mensaje rutinario
  } else if (ultimoJsonRecibido["topic"] == "Rutinario"){  // se recibe un mensaje rutinario
    if(ultimoJsonRecibido["ID"] == sensoresAsociados[0].ID){                          // verifica si el ID corresponde con el ID registrado en el objeto
      Serial.print("Mensaje de sensor recibido, de: "); Serial.println( sensoresAsociados[0].ID );
      sensoresAsociados[0].lecturaFisica = ultimoJsonRecibido["Temp"];
      sensoresAsociados[1].lecturaFisica = ultimoJsonRecibido["pH"];
      sensoresAsociados[2].lecturaFisica = ultimoJsonRecibido["Cond"];
      sensoresAsociados[3].lecturaFisica = ultimoJsonRecibido["Turb"];
      sensoresAsociados[4].lecturaFisica = ultimoJsonRecibido["TDS"];  // desactivado temporalmente

      for(int i = 0; i < numeroSensores; i++){  // guardar la temperatura en todos los sensores
        sensoresAsociados[i].temperatura = ultimoJsonRecibido["Temp"];
      }

      // Registrar datos de los filtros
      filtrosAsociados[0].etapa = ultimoJsonRecibido["Filtro1_etapa"];
      filtrosAsociados[1].etapa = ultimoJsonRecibido["Filtro2_etapa"];
      filtrosAsociados[2].etapa = ultimoJsonRecibido["Filtro3_etapa"];
      filtrosAsociados[0].falloMotor = ultimoJsonRecibido["Filtro1_falloMotor"];
      filtrosAsociados[1].falloMotor = ultimoJsonRecibido["Filtro2_falloMotor"];
      filtrosAsociados[2].falloMotor = ultimoJsonRecibido["Filtro3_falloMotor"];

      filtrosAsociados[0].fallaAgua = ultimoJsonRecibido["fallaAgua"];
      //...
      return 3;    
    } 
    
  // Caso 4: Llega confirmacion de recibido
  } else if (ultimoJsonRecibido["topic"] == "Confirm"){
      return 4; // retorna un 4 para indicar que llego confirmacion
  }

  return 0;  // si no entra al if, retorna 0 de error
} // fin de funcion


/*
// Funcion para generar un mensaje para indicarle al root que se ha recibido la informacion (no eberia ir aqui, sino en el disp 2 y 3)
JsonObject mensaje::generarMensajeDeConfirmacion(){
  // ...
}
*/

/*
bool mensaje::entregarMensajeSaliente(JsonObject jsonDoc){
  //
}
*/


#endif
