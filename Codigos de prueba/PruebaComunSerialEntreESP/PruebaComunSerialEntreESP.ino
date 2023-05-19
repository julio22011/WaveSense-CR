/* Codigo de prueba de recibimiento de señales por serial
 * ESP32 (pantalla): RX: 12, TX: 14
 * ESP32 (root mesh): RX: 14, TX: 12
*/

#define RXD2 14
#define TXD2 12

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

}

String datoRecibido;

void loop() {
  //
  datoRecibido = "";
  while(true){
    if(Serial2.available()){
      datoRecibido = Serial2.readStringUntil('\n');
      Serial.println(datoRecibido);
    }
    vTaskDelay(pdMS_TO_TICKS(20)); // darle un momento para que se llene el buffer del serial
  }


}
