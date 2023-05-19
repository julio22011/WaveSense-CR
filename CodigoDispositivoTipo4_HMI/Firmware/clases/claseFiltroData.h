/************************************************************************************************
 * Clase que permite gestionar los datos entrantes desde los objetos de tipo filtro
************************************************************************************************/

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif


#if !defined(claseFiltroDataIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseFiltroDataIncluida

// Etapas de los filtros
#define etapaTransicion        0
#define etapaServicio          1
#define etapaRetrolavado       2
#define etapaSuccion_Enjuague  3


// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
DynamicJsonDocument jsonBufferFilt(1024); // Crear instancia para los documentos JSON

class filtroData{
  private:

  public:
  // Variables:
  uint16_t numeroDeFiltro;
  uint16_t interruptorA;
  uint16_t interruptorB;
  uint16_t rele;


  // Nuevos
  int8_t etapa = 0;
  bool falloMotor = false; bool fallaAgua = false;
  int ID;
  String topic;
  JsonObject objetoJson = jsonBufferFilt.to<JsonObject>();

  int horario1[5];   // activado, hora, min, t1, t2: ejemplo: {1,13,50,15,5} significa activado, a la 1:50 pm con retro: 15min, succion: 5 min
  int horario2[5];
  int horario3[5];
  int horario4[5];

  float disparoTurbMin = -100.0;
  float disparoTurbMax = 3000.0;

  // Funciones
  bool inicializar(uint16_t nDeFiltro);
  bool guardarDatosRecibidosDeJson(JsonObject jsonDoc);
  JsonObject genJsonParaActualizacionDatos();
  JsonObject genJsonParaEnviarOrden(int numOrden);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcion de inicializacion del filtro
bool filtroData::inicializar(uint16_t nDeFiltro){
  numeroDeFiltro = nDeFiltro;
  return 1;
}


// Funcion para almacenar los datos que se recibieron del archivo Json
bool filtroData::guardarDatosRecibidosDeJson(JsonObject jsonDoc){
  ID =                    jsonDoc["ID"];
  topic =    (const char*)jsonDoc["topic"];
  etapa =                 jsonDoc["etapa"];
  numeroDeFiltro =        jsonDoc["numeroDeFiltro"];
  interruptorA =          jsonDoc["interruptorA"];
  interruptorB =          jsonDoc["interruptorB"];
  rele =                  jsonDoc["rele"];
}

// Funcion para generar el json que permita actualizar los datos en los dipositivo 2
JsonObject filtroData::genJsonParaActualizacionDatos(){
  //objetoJson["topic"] =        topic;
  objetoJson["numeroDeFiltro"] =   numeroDeFiltro;
  objetoJson["interruptorA"] =     interruptorA;
  objetoJson["interruptorB"] =     interruptorB;
  objetoJson["rele"] =             rele;

  // Rango de disparo de retrolavado segun turbidez
  objetoJson["disparoTurbMin"] =   disparoTurbMin;
  objetoJson["disparoTurbMax"] =   disparoTurbMax;
  
  // Horarios (lo siguiente se podria mejorar con un for, con matrices)
  JsonObject horarioJson1 = objetoJson.createNestedObject("horario1"); // crea un objeto anidado con los siguientes datos
  horarioJson1["activado"] =    horario1[0];
  horarioJson1["hora"] =        horario1[1];
  horarioJson1["minuto"] =      horario1[2];
  horarioJson1["tiempoRetro"] = horario1[3];
  horarioJson1["tiempoSucc"] =  horario1[4];

  JsonObject horarioJson2 = objetoJson.createNestedObject("horario2"); // crea un objeto anidado con los siguientes datos
  horarioJson2["activado"] =    horario2[0];
  horarioJson2["hora"] =        horario2[1];
  horarioJson2["minuto"] =      horario2[2];
  horarioJson2["tiempoRetro"] = horario2[3];
  horarioJson2["tiempoSucc"] =  horario2[4];

  JsonObject horarioJson3 = objetoJson.createNestedObject("horario3"); // crea un objeto anidado con los siguientes datos
  horarioJson3["activado"] =    horario3[0];
  horarioJson3["hora"] =        horario3[1];
  horarioJson3["minuto"] =      horario3[2];
  horarioJson3["tiempoRetro"] = horario3[3];
  horarioJson3["tiempoSucc"] =  horario3[4];

  JsonObject horarioJson4 = objetoJson.createNestedObject("horario4"); // crea un objeto anidado con los siguientes datos
  horarioJson4["activado"] =    horario4[0];
  horarioJson4["hora"] =        horario4[1];
  horarioJson4["minuto"] =      horario4[2];
  horarioJson4["tiempoRetro"] = horario4[3];
  horarioJson4["tiempoSucc"] =  horario4[4];

  return objetoJson;  // retrona el objeto json completado
}


// Funcion para generar el json que permita actualizar los datos en los dipositivo 2
JsonObject filtroData::genJsonParaEnviarOrden(int numOrden){
  objetoJson["ID"] =               ID;
  objetoJson["topic"] =            "OrdenFiltro";    // Indica en el topico que es una orden hacia un filtro
  objetoJson["numeroDeFiltro"] =   numeroDeFiltro;
  objetoJson["orden"] =            numOrden;         // cada orden tendra asociado un nuemero, para disparar cada funcion de la clase filtro

  return objetoJson;
}


#endif