/*
 * Programa para probar la clasificacion de json por tipos
*/

#include <ArduinoJson.h>

#include "comunicationProtocolTypes.h"

const char* ejemplo_json = "{"
                          "  \"type\": \"a\","
                          "  \"command\": \"WiFiSearchQQ\","
                          "  \"answer\": \"dataRecOk\","
                          "  \"data\": {"
                          "    \"temperatura\": 25.0,"
                          "    \"humedad\": 50.0"
                          "  }"
                          "}";

void setup() {
  Serial.begin(115200);
}

void loop() {
  struct datosProcesados datos = procesar_mensaje(ejemplo_json);

  imprimirPorSerialEtiqueta(&datos);
  
  delay(3000);
}
