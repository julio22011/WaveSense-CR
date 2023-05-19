// En este archivo se establecen las funciones para ejecutar las tareas del sistema



// Includes de los archivos requeridos para las tareas
// las funciones que se llaman deben ir antes de la tarea desde la cual se les llama


/*
// Definicion de los task handles de las tareas, cada tarea debe tener un handle para desactivarla
TaskHandle_t tareaAudBlueHandle = NULL;
TaskHandle_t tareaServoHandle = NULL;
TaskHandle_t tareaWifiHandle = NULL;
TaskHandle_t tareaSDHandle = NULL;
TaskHandle_t tareaBateriaHandle = NULL;
TaskHandle_t tareaPantallaHandle = NULL;   */

TaskHandle_t tareaPantallaHandle = NULL;


/*Prototipo de las funciones> Lo siguiente permite poder llamar las funciones de inicio
de tareas desde cualquier partes anteriores del codigo donde se define la funcion*/
void iniciarPantalla(int stack);


// Definicion de las funciones que permiten llamar y activar las tareas
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

#include "archivoTarea/archivoTareaWifi.h"
void iniciarWifi(int stack) {    //  stack> 5000
  BaseType_t tar3 = xTaskCreatePinnedToCore(
    tareaWifi,      // Function that should be called
    "wifi",    // Name of the task (for debugging)
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    6,                  // Task priority
    NULL,               // Task handle
    CONFIG_ARDUINO_RUNNING_CORE  // Core you want to run the task on (0 or 1)
  );
}

#include "archivoTarea/archivoTareaSD.h"
void iniciarSD(int stack) {    //  stack> 5000
  BaseType_t tar4 = xTaskCreatePinnedToCore(
    tareaSD,      // Function that should be called
    "SD",    // Name of the task (for debugging)
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority
    NULL,               // Task handle
    CONFIG_ARDUINO_RUNNING_CORE  // Core you want to run the task on (0 or 1)
  );
}

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

#include "archivoTarea/archivoTareaSerialBT.h"
void iniciarSerialBT(int stack) {    //  stack> 1000
  BaseType_t tar7 = xTaskCreatePinnedToCore(
    tareaSerialBT,      // Function that should be called
    "Serial BT",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}

#include "archivoTarea/archivoTareaServidor.h"
void iniciarServidor(int stack) {    //  stack> 1000
  BaseType_t tar8 = xTaskCreatePinnedToCore(
    tareaServidor,      // Function that should be called
    "Servidor",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}

#include "archivoTarea/archivoTareaESP_NOW.h"
void iniciarESPNOW(int stack) {    //  stack> 1000
  BaseType_t tar9 = xTaskCreatePinnedToCore(
    tareaESPNOW,      // Function that should be called
    "ESP_NOW",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    3,                  // Task priority
    NULL,               // Task handle
    1          // Core you want to run the task on (0 or 1)
  );
}

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

#include "archivoTarea/archivoTareaMouseBLE.h"
void iniciarMouseBLE(int stack) {    //  stack> 1000
  BaseType_t tar11 = xTaskCreatePinnedToCore(
    tareaMouseBLE,      // Function that should be called
    "Mouse",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    5,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}

#include "archivoTarea/archivoTareaGraficacion.h"
void iniciarGraficacion(int stack) {    //  stack> 1000
  BaseType_t tar12 = xTaskCreatePinnedToCore(
    tareaGraficacion,      // Function that should be called
    "Gráficas",    // Name of the task (for debugging) // 5000
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    5,                  // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}


#include "archivoTarea/archivoTareaLVGL.h"
void iniciarLVGL(int stack) {    // stack> 5000
  BaseType_t tar13 = xTaskCreatePinnedToCore(
    tareaLVGL,      // Function that should be called
    "LVGL",    // Name of the task (for debugging)
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    6,     //4             // Task priority
    NULL,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}

/////////////////////////////////////////////////////////////////////////////
// la tarea pantalla debe ir al final porque es la que ejecuta desde allí otras tareas
#include "archivoTarea/archivoTareaPantalla.h"
void iniciarPantalla(int stack) {    // stack> 5000
  BaseType_t tarMain = xTaskCreatePinnedToCore(
    tareaPantalla,      // Function that should be called
    "pantallaLCD",    // Name of the task (for debugging)
    stack,               // Stack size (bytes)
    NULL,               // Parameter to pass
    4,                  // Task priority
    &tareaPantallaHandle,               // Task handle
    0          // Core you want to run the task on (0 or 1)
  );
}
