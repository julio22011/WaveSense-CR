#include "freertos/projdefs.h"
/****************************************************************************************************
 * Archivo para la gestion de las tareas
 *
*****************************************************************************************************/


// Prueba de task scheduller
//********************************************

void UI(){
  // Tarea que mantiene funcionando el UI de la OLED
  ui.update();
}

Task taskUI( TASK_MILLISECOND * 10 , TASK_FOREVER, &UI );  // crear tarea de envio de mensajes


void ejecucionDeRetrolavadoInterno(){
  // Tarea para efectuar un retrolavado
  filtro1.aplicarRetrolavado(filtro1.horarioInt[3],filtro1.horarioInt[4]);     // (segundos de retro, segundos de succion y enjuague)
  //filtro2.aplicarRetrolavado(filtro2.horarioInt[3],filtro2.horarioInt[4]);   // 
  //filtro3.aplicarRetrolavado(filtro3.horarioInt[3],filtro3.horarioInt[4]);   //  
}
Task taskEjecucionDeRetrolavadoInterno(0, TASK_ONCE, &ejecucionDeRetrolavadoInterno);  // (tiempo de espera entre ejecuciones, cantidad de veces, funcion de la tarea)


///////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------
// FreRTOS

void iniciarTareaBip(int stack); // para que compile tareaIrPosServicio

void tareaEjecucionDeRetrolavadoInterno(void * parameters){
  aplicandoRetro = true;
  // Tarea para efectuar un retrolavado
  filtro1.aplicarRetrolavado(filtro1.horarioInt[3],filtro1.horarioInt[4]);     // (segundos de retro, segundos de succion y enjuague)
  filtro2.aplicarRetrolavado(filtro2.horarioInt[3],filtro2.horarioInt[4]);   // 
  filtro3.aplicarRetrolavado(filtro3.horarioInt[3],filtro3.horarioInt[4]);   //
  iniciarTareaBip(512);

  aplicandoRetro = false;
  vTaskDelete(NULL); // elimina la tarea una vez finalizada
}

//-------------------------------------------------------------------------------------------------------
void tareaIrPosServicio(void * parameters){
  yendoPosServicio = true;
  ui.mostrarMensaje("F:Colocado todos en pos. servicio");
  
  if(!todosLosFiltros[0].colocarEtapaServicio()) {ui.mostrarMensaje("Error en F1,continuando con F2");}
  if(!todosLosFiltros[1].colocarEtapaServicio()) {ui.mostrarMensaje("Error en F2,continuando con F3");}
  if(!todosLosFiltros[2].colocarEtapaServicio()) {ui.mostrarMensaje("Error en F3,continuando"); vTaskDelay(pdMS_TO_TICKS(2000));}
  iniciarTareaBip(512);  

  yendoPosServicio = false;
  vTaskDelete(NULL);
}
//-------------------------------------------------------------------------------------------------------
void tareaBip(void * parameters){
  // Hace ruido corto
  for(int i=0; i<5; i++){
    digitalWrite(pinBuzzer, HIGH);
    vTaskDelay(pdMS_TO_TICKS(50));
    digitalWrite(pinBuzzer, LOW);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  vTaskDelete(NULL); // elimina la tarea una vez finalizada

}
//-------------------------------------------------------------------------------------------------------
// Funcion para mostrar en la pantalla el estado de los retrolavados
void mostrarEstadoDeRetroEnUI(){
  //
  if(aplicandoRetro){
    for(int i = 0; i<cantidadDeFiltros; i++){
      if(todosLosFiltros[i].etapa == 0){ui.mostrarMensaje("F1:Moviendo valvula");}
      if(todosLosFiltros[i].etapa == 1){ui.mostrarMensaje("F1:Colocado en pos. servicio"); vTaskDelay(pdMS_TO_TICKS(1000));}
      if(todosLosFiltros[i].etapa == 2){ui.mostrarMensaje("F1:Retrolavado, 10");}
      if(todosLosFiltros[i].etapa == 3){ui.mostrarMensaje("F1:Succ. y enjuague");}
    }
    
    //if(cuenta == 2) { cuenta = 0; retrolavadoIniciado = false; iniciarTareaBip(512);} // indica que se acabado el proceso de retrolavado
                                                                // una vez se ha regresado a la etapa de servicio    
  }
}

void IRAM_ATTR tareaUI(void * parameters){
  // Tarea que mantiene funcionando el UI de la OLED
  while(true){
    ui.update();
    mostrarEstadoDeRetroEnUI();
    vTaskDelay(pdMS_TO_TICKS(200));
  } // nunca salirse del bucle
  vTaskDelete(NULL);
}

//-------------------------------------------------------------------------------------------------------
DynamicJsonDocument jsonBufferRut(1024); // Crear instancia para los documentos JSON
DynamicJsonDocument jsonBufferOtros(1024); // Crear instancia para los documentos JSON

JsonObject generarJsonDatosRutinarios(){
  // Crear objeto json para los mensajes
  JsonObject mensaje = jsonBufferRut.to<JsonObject>();
  mensaje["ID"] = IDdelDispositivo;                          // guarda el ID del dispositivo
  mensaje["topic"] = "Rutinario";                            // indica que es un mensaje rutinario 

  // Pruebas mediante for (da error el de TDS)
  int cantidadSensores = sizeof(todosLosSensores)/sizeof(sensor);  // determina la cantidad de sensores anadidos
  int cantidadFiltros = sizeof(todosLosFiltros)/sizeof(filtro);    // determina la cantidad de filtros

  char buffer[30]; // buffer para la conversion de strings a char*
  
  // Anadir los datos de todos los sensores
  for(int i = 0; i<cantidadSensores; i++){                       // El -1 es para ignorar el sensor de TDS, el cual esta dando error
    sprintf(buffer, "%s", todosLosSensores[i].parametro); // cambia de string a char*
    mensaje[buffer] = todosLosSensores[i].devolverParametroFisico(); 
  }

/*
  // Anadir los datos de todos los filtros (error: el for solo envia el filtro 0)
  for(int i = 0; i<cantidadFiltros; i++){
    sprintf(buffer, "filtro%i_etapa", todosLosFiltros[i].numeroDeFiltro); // cambia de string a char*
    mensaje[buffer] = todosLosFiltros[i].etapa;

    sprintf(buffer, "filtro%i_falloMotor", todosLosFiltros[i].numeroDeFiltro); // cambia de string a char*  //todosLosFiltros[i].topic,
    mensaje[buffer] = todosLosFiltros[i].falloMotor;
  }
*/

  // Anadir los datos de todos los filtros
  mensaje["Fitro1_etapa"] = todosLosFiltros[0].etapa;
  mensaje["Fitro2_etapa"] = todosLosFiltros[1].etapa;
  mensaje["Fitro3_etapa"] = todosLosFiltros[2].etapa;
  mensaje["Fitro1_falloMotor"] = todosLosFiltros[0].falloMotor;
  mensaje["Fitro2_falloMotor"] = todosLosFiltros[1].falloMotor;
  mensaje["Fitro3_falloMotor"] = todosLosFiltros[2].falloMotor;

   mensaje["fallaAgua"] = todosLosFiltros[0].fallaAgua;  // varible para notificar si se presento una falla en el agua despues de los filtros

    // Anadir las lecturas de todos los sensores
  //mensaje["Temp"] = todosLosSensores[0].devolverParametroFisico();
  //mensaje["pH"] = todosLosSensores[1].devolverParametroFisico();
  //mensaje["Cond"] = todosLosSensores[2].devolverParametroFisico();
  //mensaje["Turb"] = todosLosSensores[3].devolverParametroFisico();
  //mensaje["TDS"] = todosLosSensores[4].devolverParametroFisico();   // da error

  return mensaje;
}

// Funcion para generar un documento convertir un string en un documento Json
DynamicJsonDocument genJsonDeString(String stringRecibido){
  // Crear objeto json con el mensaje recibido
  //JsonObject json = jsonBufferOtros.to<JsonObject>();
  DeserializationError error = deserializeJson(jsonBufferOtros, stringRecibido);  // verificar // jsonBufferMen
  
  return jsonBufferOtros;
}

String genMensajeConfirmacion(){
  String strGenerado;
  JsonObject objetoJson = jsonBufferOtros.to<JsonObject>();

  objetoJson["ID"] = IDdelDispositivo;
  objetoJson["topic"] = "Confirm";   
  
  serializeJson(jsonBufferOtros, strGenerado);
  return strGenerado;    
}

// Tarea que hace el envio de datos
void tareaEnviarDatos(void * parameters){
  // setup

  // loop
  while(true){
    JsonObject resultadoJsonPru = generarJsonDatosRutinarios();               // prueba con paquete general rutinario
    String mensaje;
    serializeJson(resultadoJsonPru, mensaje);
    mesh.sendBroadcast( mensaje );
    
    //mesh.sendBroadcast( "Hola" );    
    //taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 3 )); // Establece un intervalo aleatorio de tiempo (cambiado por vTaskDelay())
    vTaskDelay(pdMS_TO_TICKS(msDeMensajeRutinario));
  }
  vTaskDelete(NULL);
}

void tareaMesh(void * parameters){
  // Tarea que mantiene funcionando el UI de la OLED
  while(true){
    mesh.update();
  } 
  vTaskDelete(NULL);
}

//*********************************************************************************************************************************
// carfa de las tareas
/*

*/

TaskHandle_t TaskHandle_1;
//#include "archivoTarea/archivoTareaUI.h"
void iniciarUI(int stack) {    //  stack> 1000
  BaseType_t tar1 = xTaskCreatePinnedToCore(
    tareaUI,      // Function that should be called
    "UI-OLED",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    1,                  // 3 Task priority, mientras mas pequeno...
    NULL,                // Task handle, NULL si no tiene
    1                    // Nucleo en el que corre
  );
}

TaskHandle_t TaskHandle_3;
//#include "archivoTarea/archivoTareaMesh.h"
void iniciarTareaEjecucionDeRetrolavadoInterno(int stack) {    //  stack> 1000
  BaseType_t tar3 = xTaskCreatePinnedToCore(
    tareaEjecucionDeRetrolavadoInterno,      // Function that should be called
    "Retro-int",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    2,                  // Task priority, mientras mas pequeno...
    NULL,                // Task handle, NULL si no tiene
    1                    // Nucleo en el que corre
  );
}

TaskHandle_t TaskHandle_4;
//#include "archivoTarea/archivoTareaMesh.h"
void iniciarTareaBip(int stack) {    //  stack> 1000
  BaseType_t tar4 = xTaskCreatePinnedToCore(
    tareaBip,      // Function that should be called
    "Bip",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    1,                  // Task priority, mientras mas pequeno...
    NULL,                // Task handle, NULL si no tiene
    1                    // Nucleo en el que corre
  );
}

TaskHandle_t TaskHandle_5;
//#include "archivoTarea/archivoTareaMesh.h"
void iniciarTareaIrPosServicio(int stack) {    //  stack> 1000
  BaseType_t tar5 = xTaskCreatePinnedToCore(
    tareaIrPosServicio,      // Function that should be called
    "IrPServicio",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    2,                  // Task priority, mientras mas pequeno...
    NULL,                // Task handle, NULL si no tiene
    1                    // Nucleo en el que corre
  );
}


TaskHandle_t TaskHandle_2;
//#include "archivoTarea/archivoTareaMesh.h"
void iniciarTareaEnviarDatos(int stack) {    //  stack> 1000
  BaseType_t tar6 = xTaskCreatePinnedToCore(
    tareaEnviarDatos,      // Function that should be called
    "enviarDatos",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority, mientras mas pequeno...
    NULL,                // Task handle, NULL si no tiene
    1                    // Nucleo en el que corre
  );
}

TaskHandle_t TaskHandle_7;
//#include "archivoTarea/archivoTareaMesh.h"
void iniciarTareaMesh(int stack) {    //  stack> 1000
  BaseType_t tar7 = xTaskCreatePinnedToCore(
    tareaMesh,      // Function that should be called
    "Mesh",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    5,                  // Task priority, mientras mas pequeno...
    NULL,                // Task handle, NULL si no tiene
    0                    // Nucleo en el que corre
  );
}
