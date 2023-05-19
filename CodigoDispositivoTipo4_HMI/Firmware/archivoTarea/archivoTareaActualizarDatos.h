

/*
 * Tarea que permite actualizar continuamente los datos de los graficos
*/

// Funcion de la tarea
void tareaActualizarDatos(void * parameters){
  // Setup


  // Loop
  while(true){
    // Medidor Gauge
    set_value(indic, 25); // poner en el medior Gauge la medicion (prueba) gestorMensajes.sensoresAsociados[2].temperatura
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  vTaskDelete(NULL);
}




