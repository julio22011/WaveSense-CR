
/*
 * En este archivo se definen cada una de los tipos de
 * mensaje del protocolo de comunicación.
 * También se define una funcion que permite detectar de un json(string)
 * el tipo de mensaje.
*/

#include "settings.h"
#include "estructuras.h"         // Aqui estan las estructuras de los datos
#include "enums.h"               // Aqui estan los codigos de mensaje

// Depuracion
#include "depImprimirResultados.h"

// Para clasificar mensajes que vienen en formato json
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Funcion para encontrar si un valor está en una lista de char*
int findInList(const char* value, const char** list, int listSize){
  
  // Encontrar el numero correspondiente segun el valor
  for(int i=0; i<listSize; i++){
    if (strcmp(value, list[i]) == 0) {
      return i;
    }
  }
  //Serial.println("Error, cannot identify value in Julio comunication protocol");  // Nota: seria conveniente incluir un sistema de deteccion de errores
  return -1; // retornar -1 como indicativo de falla en la identificacion
}

//-----------------------------------------

struct etiqueta construirEtiqueta(const char* tipo_mensaje, const char* command_mensaje, const char* answer_mensaje, bool error){
  struct etiqueta etiq;

  // Buscar en las listas el numero que le corresponde a cada parte de la etiqueta
  //------------------
  etiq.type =     findInList( tipo_mensaje, types, sizeof(types)/sizeof(const char*) );
  
  #ifdef isHMI
  etiq.command =  findInList( command_mensaje, commandsHMI, sizeof(commandsHMI)/sizeof(const char*) );
  etiq.answer =   findInList( answer_mensaje, answersNET, sizeof(answersNET)/sizeof(const char*) );
  etiq.error =    error;
  #endif

  #ifdef isNET
  etiq.command =  findInList( command_mensaje, commandsNET, sizeof(commandsNET)/sizeof(const char*) );
  etiq.answer =   findInList( answer_mensaje, answersHMI, sizeof(answersHMI)/sizeof(const char*) );
  etiq.error =    error;
  #endif
  
  // Registrar si hubo error en la deteccion de type, commando o answer
  //------------------
  // Asignar error si no se detecta bien el el type o ambos, command y answer, son -1:
  if(etiq.type == -1 || (etiq.command == -1 && etiq.answer == -1) ) etiq.error = true;

  // Retornar el resultado
  //------------------
  return etiq;
}

//-----------------------------------------
#include "dataProcesor.h" // alli se encuentran las funciones para procesar los datos

struct datosProcesados extraerDatosDeJson(DynamicJsonDocument doc, struct etiqueta etiq){
  struct datosProcesados datos;
  datos.etiqueta = etiq; // Agregar la etiqueta a los datos
  
  // Analizar etiqueta
  switch (etiq.type) {
    case r: getRequest(doc, &datos); break;
    case a: getAnswer(doc, &datos);  break;
    case u: getUpdate(doc, &datos);  break;
    case d: getData(doc, &datos);    break;
    default:                    datos.error = true; break;
  }

  return datos;
}


//-----------------------------------------

struct datosProcesados procesar_mensaje(const char* json) {    // const char*
  const size_t bufferSize = JSON_OBJECT_SIZE(512);
  DynamicJsonDocument doc(bufferSize);

  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print(F("Error al analizar el JSON: "));
    Serial.println(error.f_str());
    //return "Error";
  }

  // Extraer datos del json
  //-------------------
  const char* tipo_mensaje = doc["type"].as<const char*>();
  const char* command_mensaje = doc["command"].as<const char*>();
  const char* answer_mensaje = doc["answer"].as<const char*>();

  // Conformar etiqueta
  //-------------------
  struct etiqueta etiq = construirEtiqueta(tipo_mensaje, command_mensaje, answer_mensaje, error);

  // Extraer datos segun etiqueta
  //-------------------
  struct datosProcesados datos = extraerDatosDeJson(doc, etiq);

  // Retornar datos
  //-------------------
  return datos;  
  
}
