

// La siguiente tarea realiza una vibracion con un determinado patrón
void tareaVibracion (void * parameter) {
  for(int i = 4;i>0;i--){
    vTaskDelay(100 / portTICK_PERIOD_MS);
    analogWrite(vibrador,0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    analogWrite(vibrador,170);
    //digitalWrite(vibrador, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    analogWrite(vibrador,0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    //digitalWrite(vibrador, HIGH);
    analogWrite(vibrador,255);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    analogWrite(vibrador,0);
  }
  vTaskDelete(NULL);
}