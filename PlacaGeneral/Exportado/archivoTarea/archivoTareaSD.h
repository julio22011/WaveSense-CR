

void tareaSD(void * parameter){
  bool continuarTarea = true;
  while(continuarTarea){
    montarSD(); // monta la SD
    vTaskDelay(100 / portTICK_PERIOD_MS);

    // Aqui se puede implementar en el futuro una funcion que permita leer un archivo y almacenar sus datos
    /// *******

    // lo siguiente realiza una prueba de la SD para verificar su funcionamiento
    if (probarSDestado) {
      probarSD();
      probarSDestado = false; // desactiva la prueba
    }

    continuarTarea = false; 
  } // fin del bucle infinito
  vTaskDelete(NULL);
} // fin de la tarea
