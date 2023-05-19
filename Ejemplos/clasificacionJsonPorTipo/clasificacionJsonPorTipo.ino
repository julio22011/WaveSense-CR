/*
 * Programa para probar la clasificacion de json por tipos
*/

// Los siguientes define permiten establecer que tipo de dispositivo es, un HMI o un NET. Solamente activar uno de los dos.
//#define isHMI
#define isNET

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

  imprimirPorSerialResultado(&datos);
  
  delay(3000);
}
