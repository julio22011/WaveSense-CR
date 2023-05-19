
//#include <WiFiManager.h>
//#include <strings_en.h>

#include <WiFiClient.h> // para poder conectarse a router de Internet
#include "painlessMesh.h"

// Julio 0
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
AsyncWebServer server(80);

#define RXD2 12
#define TXD2 14
// Julio 0 fin


#define   MESH_PREFIX     "redMeshParqueIndustrialZeta"
#define   MESH_PASSWORD   "TEC_Zeta_acueducto"
#define   MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// Crear objeto json para los mensajes
DynamicJsonDocument jsonBuffer(1024);
JsonObject msg = jsonBuffer.to<JsonObject>();

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't compl
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  String msg = "Hi from node1";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  Serial2.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
    Serial2.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
  Serial2.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
    Serial2.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);      // permite que se mantegan coordinados los tiempos de los dispostivos

  // Julio
  TSTRING ssidModem = "KONOHA";
  TSTRING passwordModem = "familiars58";
  mesh.stationManual(ssidModem, passwordModem);

  //#define HOSTNAME "Julio"
  //mesh.setHostname(HOSTNAME); //const char *hostname, puente para MQTT

  //mesh.setRoot(true); // hace que este sea el dispositivo root, solo en uno de los dispositivos

  //mesh.setContainsRoot(true); // debe hacerse en todos los dispositvos

  mesh.initOTAReceive("otareceiverDispTipo4"); // permite recibir actualizaciones por OTA

  // Julio fin

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();

  // Julio2
  Serial.println(WiFi.localIP());

  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "This is HTML!");
  });
  
  server.begin();
  // Julio2 fin
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}
