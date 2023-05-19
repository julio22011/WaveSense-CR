
#include "protocoloJulio/protocoloJulio.h"

protocoloJulio protocolo(asHMI);  // crear un objeto para ejecutar el protocolo


String msg;

void setup(){
  Serial.begin(115200);

  String msg = "{\"command\": \"restartOk\"}";
  DynamicJsonDocument jsonPrueba(1024);

  deserializeJson(jsonPrueba, msg);

  JsonObject pruebaObj = jsonPrueba.to<JsonObject>();
  Serial.println(pruebaObj["command"].as<char*>());
}

void loop(){
  //String msg = "{\"command\": \"restartOk\"}";
  //String msg = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

  Serial.println(msg);
  
  int numero = protocolo.identifyCommandNumber(msg);
  Serial.println(numero);
  delay(1000);
}
