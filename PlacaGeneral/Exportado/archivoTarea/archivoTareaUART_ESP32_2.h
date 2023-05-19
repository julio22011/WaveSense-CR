
// Esta tarea permite recibir datos por Uart desde la ESP32 secundaria



void tareaUART_ESP32_2(void * parameters){
  //
  Serial2.begin(115200, SERIAL_8N1, RX_ESP, TX_ESP);
  String datoRecibido;
  while(true){
    if(Serial2.available()){
      datoRecibido = Serial2.readStringUntil('\n');
      Serial.println(datoRecibido);
    }
    vTaskDelay(pdMS_TO_TICKS(20)); // darle un momento para que se llene el buffer del serial
  }
  //if (cuenta>200){vTaskDelay(pdMS_TO_TICKS(10));cuenta = 0;}
  vTaskDelete(NULL);
}
