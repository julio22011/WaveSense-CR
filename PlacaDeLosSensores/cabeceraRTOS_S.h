

#include "archivoTarea/archivoTareaESP_NOW_master.h"
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
