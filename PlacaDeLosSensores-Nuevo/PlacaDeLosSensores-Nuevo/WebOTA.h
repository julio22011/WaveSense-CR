#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

const char* ssid = "KONOHA";
const char* password = "familiars58";

AsyncWebServer server(80);


void iniciarOTA(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  for(int i=0; i<= 10 ;i++){
    if (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }

  if(WiFi.status() == WL_CONNECTED){ // si esta conectado a WiFI se activa el OTA
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "Hi! I am ESP32.");
    });
  
    AsyncElegantOTA.begin(&server);    // Start ElegantOTA
    server.begin();
    Serial.println("HTTP server started");
  }

}
