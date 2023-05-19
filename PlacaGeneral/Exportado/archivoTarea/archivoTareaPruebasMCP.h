// Esta tarea permite ejecutar una prueba de las salidas de los chips MCP23017


void tareaPruebasMCP(void * parameters){
   for (int i = 0; i<=15 ; i++){

    // Preder LED
    mcp.digitalWrite(i, HIGH);

    // Apagar el LED anterior
    if (i != 0){
      mcp.digitalWrite(i-1, LOW);
    }
    else{
      mcp.digitalWrite(15, LOW);
    }
    analogWrite(vibrador, 255);
    vTaskDelay(pdMS_TO_TICKS(300));
    analogWrite(vibrador, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
   }
  vTaskDelete(NULL);
}
