
//#include <WiFiManager.h>
//#include <strings_en.h>
#include "variablesGenerales.h"

// Julio 0
AsyncWebServer server(80);
// Julio 0 fin

#define   MESH_PREFIX     "redMeshParqueIndustrialZeta"
#define   MESH_PASSWORD   "TEC_Zeta_acueducto"
#define   MESH_PORT       5555

#define   STATION_PORT     5555
uint8_t   station_ip[4] =  {192,168,100,150}; // IP of the server

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// Crear objeto json para los mensajes
DynamicJsonDocument jsonBuffer(1024);
JsonObject msg = jsonBuffer.to<JsonObject>();

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

#include "cabeceraRTOS.h"

// Funcion para obtener el id del chip
uint32_t chipId = 0;
void getChipID(){
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
}

void sendMessage() {
  String msg = "Hi from node1";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

String strMensajeRecibido = "Ningun mensaje aun!";

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  strMensajeRecibido = msg.c_str();
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  //Serial2.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  Serial2.printf(msg.c_str());

  // Acciones:
  //------------------------------
  //enviarDatosInternet();     // ejecuta funcion que envia los datos a internet (a archivo de excel)
  enviarDatosThingSpeak(msg);  // enviar datos a ThingSpeak
  sendDataRTDB(msg, mesh.subConnectionJson(false)); // envia datos del mensaje y la lista de nodos conectados al root

  // Mostrar en navegador el ultimo mensaje recibido
  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", strMensajeRecibido);
  });
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: Nueva conexion, nodeId = %u\n", nodeId);
  Serial2.printf("--> startHere: Nueva conexion, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  // Actualizar los nodos en la RTDB cada 10 segundos
  Serial.printf("Cambiaron las conexiones\n");
  Serial2.printf("Cambiaron las conexiones\n");

  sendSettingsRTDB(mesh.subConnectionJson(false));  // enviar los nuevos ajustes a la RTDB
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
  Serial2.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX_ESP, TX_ESP);

  getChipID(); // le aigna a la variable global chipId (uint_32) el valor del id

  preferences.begin("settings"); // iniciar las preferencias
  recuperarContasenaWiFi();      // modifica las variables de si se han hecho cambios

  delay(3000);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
//mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before linit() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);      // permite que se mantegan coordinados los tiempos de los dispostivos

  // Julio
  mesh.stationManual(ssidModem, passwordModem);  //STATION_PORT, station_ip

  mesh.setRoot(true); // hace que este sea el dispositivo root, solo en uno de los dispositivos
  //mesh.setContainsRoot(true); // debe hacerse en todos los dispositvos
  //mesh.initOTAReceive("otareceiverDispTipo4Mesh"); // permite recibir actualizaciones por OTA

  // Julio fin
  
  #define HOSTNAME "Red_Mesh"
  mesh.setHostname(HOSTNAME); //const char *hostname, puente para MQTT

  userScheduler.addTask( taskSendMessage );
  //taskSendMessage.enable();                      // (deshabilitado para pruebas)

  // Recibir mensajes por serial y enviarlos por mesh:
  iniciarUART_ESP32_2(5000); // Inicia programa para recibrir datos por Uart de la ESP32 del HMI (recibir mensajes dirigidos a los dispositivos)

  // Iniciar tarea para recuperar la hora
  //iniciarFechaHora(2000);

  setupFirebaseRTDB();

  // Julio2*******************************************
  Serial.println(WiFi.localIP());

  server.on("/mensajeUltimo", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", strMensajeRecibido);
  });
  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request)
    {
    request->send(200, "application/json", mesh.subConnectionJson(false) );
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
    request->send(200, "text/html", paginaPrincipalSt);  // "<form>Text to Broadcast<br><input type='text' name='BROADCAST'><br><br><input type='submit' value='Submit'></form>"
    if (request->hasArg("BROADCAST"))
      {
      String msg = request->arg("BROADCAST");
      mesh.sendBroadcast(msg);
      }
  });

///////////////////////////// OTA
  // Da error?
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  Serial.println("OTA por navegador iniciado.");
////////////////////////////////////////////////////////////

  server.on("/map", HTTP_GET, [](AsyncWebServerRequest *request)
    {
    request->send_P(200, "text/html", "<html><head><script type='text/javascript' src='https://cdnjs.cloudflare.com/ajax/libs/vis/4.21.0/vis.js'></script><link href='https://cdnjs.cloudflare.com/ajax/libs/vis/4.21.0/vis-network.min.css' rel='stylesheet' type='text/css' /><style type='text/css'>#mynetwork {width: 1024px;height: 768px;border: 1px solid lightgray;}</style></head><body><h1>PainlessMesh Network Map</h1><div id='mynetwork'></div><a href=https://visjs.org>Made with vis.js<img src='http://www.davidefabbri.net/files/visjs_logo.png' width=40 height=40></a><script>var txt = '%SCAN%';</script><script type='text/javascript' src='http://www.davidefabbri.net/files/painlessmeshmap.js'></script></body></html>", scanprocessor );
  });
  server.begin();
  
  // Julio2 fin***************************************
}


void loop() {
  // it will run the user scheduler as well
  mesh.update();
}

//////////////
// Escanear la configuracion de la red
String scanprocessor(const String& var)
{
  if(var == "SCAN")
    return mesh.subConnectionJson(false);
  return String();
}
