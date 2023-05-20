/*
 * Este archivo contiene funciones que permiten imprimir los resultados con
 * intenciones principalmente de depuracion del codigo.
*/


// Para imprimir por serial el resultado del procesado
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void imprimirPorSerialEtiqueta(struct datosProcesados* datos){

  #ifdef isHMI
    #ifdef isNET
      Serial.println("Error: Se definió el dispositivo como HMI y NET al mismo tiempo. Solo debe definirse un tipo."); 
    #endif
  #endif

  #ifndef isHMI
    #ifndef isNET
      Serial.println("Error: No se definio el tipo de dispositivo. Define isHMI o isNET segun corresponda."); 
    #endif
  #endif
  
  bool errorEtiqueta = datos->etiqueta.error;
  bool errorDatos = datos->error;

  if(!errorEtiqueta){
    if(!errorDatos){
      #ifdef isHMI
        Serial.println("Mensaje procesado como HMI");
        Serial.printf("Type: %s\n", types[datos->etiqueta.type]);
        if(datos->etiqueta.type == a){
          Serial.printf("Answer: %s\n", answersNET[datos->etiqueta.answer]);
        } else{
          Serial.printf("Command: %s\n", commandsNET[datos->etiqueta.command]);
        }
      #endif
      
      #ifdef isNET
        Serial.println("Mensaje procesado como NET");
        Serial.printf("Type: %s\n", types[datos->etiqueta.type]);
        if(datos->etiqueta.type == a){
          Serial.printf("Answer: %s\n", answersHMI[datos->etiqueta.answer]);
        } else{
          Serial.printf("Command: %s\n", commandsHMI[datos->etiqueta.command]);
        }
      #endif
    }else{
      Serial.println("Ocurrió un error durante el procesado de los datos.");
    }
  } else{
    Serial.println("Ocurrió un error durante el etiquetado del mensaje.");
  }
}
