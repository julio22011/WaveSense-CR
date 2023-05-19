
/* ***********************************************************************************************
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
cabeceraRTOS.h:
  En este archivo se establecen las funciones para ejecutar las tareas del sistema
Notas:
  -Includes de los archivos requeridos para las tareas
  las funciones que se llaman deben ir antes de la tarea desde la cual se les llama
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*********************************************************************************************** */


/*
// Definicion de los task handles de las tareas, cada tarea debe tener un handle para desactivarla
 */
TaskHandle_t tareaPantallaHandle = NULL;


/*Prototipo de las funciones> Lo siguiente permite poder llamar las funciones de inicio
de tareas desde cualquier partes anteriores del codigo donde se define la funcion*/
//void iniciarPantalla(int stack);

//=====================================================================
// Definicion de las funciones que permiten llamar y activar las tareas
//=====================================================================

#include "archivoTarea/archivoTareaAudBlue.h"
void iniciarAudBlue(int stack) {    //  stack> 500
  BaseType_t tar1 = xTaskCreatePinnedToCore(
    tareaAudBlue,      // Function that should be called
    "Audio Bluetooth",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    2,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}
//=====================================================================
#include "archivoTarea/archivoTareaBateria.h"
void iniciarBateria(int stack) {    //  stack> 1000
  BaseType_t tar5 = xTaskCreatePinnedToCore(
    tareaBateria,      // Function that should be called
    "bateria",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}
//=====================================================================
#include "archivoTarea/archivoTareaVibracion.h"
void iniciarVibracion(int stack) {    //  stack> 1000
  BaseType_t tar6 = xTaskCreatePinnedToCore(
    tareaVibracion,      // Function that should be called
    "Vibracion",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}
//=====================================================================
#include "archivoTarea/archivoTareaBotones.h"
void iniciarBotones(int stack) {    //  stack> 1000
  BaseType_t tar10 = xTaskCreatePinnedToCore(
    tareaBotones,      // Function that should be called
    "Botones",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    6,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}
//====================================================================
#include "archivoTarea/archivoTareaMouseBLE.h"
void iniciarMouseBLE(int stack) {    //  stack> 1000
  BaseType_t tar11 = xTaskCreatePinnedToCore(
    tareaMouseBLE,      // Function that should be called
    "Mouse",    // Name of the task (for debugging) // 5000 ok
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    5,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}
//====================================================================
#include "archivoTarea/archivoTareaPruebasMCP.h"
void iniciarPruebasMCP(int stack) {    //  stack> 1000
  BaseType_t tar11 = xTaskCreatePinnedToCore(
    tareaPruebasMCP,      // Function that should be called
    "PruebasMCP",    // Name of the task (for debugging) // 5000 ok
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    5,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}
//====================================================================
#include "archivoTarea/archivoTareaUART_ESP32_2.h"
void iniciarUART_ESP32_2(int stack) {    //  stack> 1000
  BaseType_t tar11 = xTaskCreatePinnedToCore(
    tareaUART_ESP32_2,      // Function that should be called
    "UART_ESP32_2",    // Name of the task (for debugging) // 5000 ok
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}
//====================================================================
#include "archivoTarea/archivoTareaServo.h"
void iniciarServo(int stack) {    //  stack> 500
  BaseType_t tar2 = xTaskCreatePinnedToCore(
    tareaServo,      // Function that should be called
    "servo",    // Name of the task (for debugging)
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}
//====================================================================
#include "archivoTarea/archivoTareaGrafica.h"
void iniciarGrafica(int stack) {    //  stack> 500
  BaseType_t tar2 = xTaskCreatePinnedToCore(
    tareaGrafica,      // Function that should be called
    "Grafica",    // Name of the task (for debugging)
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}
