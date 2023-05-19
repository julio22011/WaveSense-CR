//**************************************************
//  En este archivo estan las funciones que permiten
//  activar cada una de las tareas.
//**************************************************


//#1*****************************************************
TaskHandle_t TaskHandle_1;
#include "archivoTarea/archivoTareaESP_NOW_master.h"
void iniciarESPNOW(int stack) {    //  stack> 1000
  BaseType_t tar1 = xTaskCreatePinnedToCore(
    tareaESPNOW,      // Function that should be called
    "ESP_NOW",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle, NULL si no tiene
    1          // Core you want to run the task on (0 or 1)
  );
}
//#2*****************************************************
TaskHandle_t TaskHandle_2;
#include "archivoTarea/archivoTareaBotones.h"
void iniciarBotones(int stack) {    //  stack> 1000
  BaseType_t tar2 = xTaskCreatePinnedToCore(
    tareaBotones,      // Function that should be called
    "Botones",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle, NULL si no tiene
    1          // Core you want to run the task on (0 or 1)
  );
}
//#3*****************************************************
TaskHandle_t TaskHandle_3;
#include "archivoTarea/archivoTareaUI.h"
void iniciarUI(int stack) {    //  stack> 1000
  BaseType_t tar3 = xTaskCreatePinnedToCore(
    tareaUI,      // Function that should be called
    "UI",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle, NULL si no tiene
    1          // Core you want to run the task on (0 or 1)
  );
}
//#4*****************************************************


//#5*****************************************************

//#6*****************************************************

//#7*****************************************************
