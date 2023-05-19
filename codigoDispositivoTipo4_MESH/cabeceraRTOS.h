
/*************************************************************************
 * En este arhivo se configuran las tareas RTOS del microcontrolados
**************************************************************************/



//====================================================================
#include "archivoTarea/archivoTareaFechaHora.h"
void iniciarFechaHora(int stack) {    //  stack> 1000
  BaseType_t tar12 = xTaskCreatePinnedToCore(
    tareaFechaHora,      // Function that should be called
    "FechaHora",         // Name of the task (for debugging) // 5000 ok
    stack,               // Stack size (bytes)
    NULL,                // Parameter to pass
    2,                   // Task priority
    NULL,                // Task handle
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
