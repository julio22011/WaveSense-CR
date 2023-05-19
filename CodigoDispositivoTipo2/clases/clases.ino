// Dejar este archivo en blanco o usar para pruebas de las clases, solamente es para permitir
// editar los archivos de la carpeta con Arduino



//////////////////////////////
// Lo siguiente es una prueba de las clases


///////////////////////
// Filtro 1
#define f1_1 4
#define f1_2 27 //

// Filtro 2
#define f2_1 17 //
#define f2_2 35

// Filtro 3
#define f3_1 34
#define f3_2 36
/////////////////////////
// Rele doble 1
#define rele1_1 2
#define rele1_2 13

// Rele doble 2
#define rele2_1 26
#define rele2_2 16
/////////////////////////


// Pines de I2C
//-----------------------------
int I2C_SDA = 22;
int I2C_SCL = 21;

// Definir pines de sensores
#define pinADC_pH 2
#define pinADC_Cond 1
#define pinADC_Cond 1
#define pinADC_Turb 0
#define pin_Temp 15

#include "claseSensor.h" // Necesita definir pin_Temp antes para compilar
#include "claseFiltros.h"
#include "claseUI_OLED.h"
#include "claseBotones.h"

filtro filtro1; // crear objeto tipo filtro

UI_OLED ui;    // crear objeto de ui

// Crear los sensores
sensor sTemperatura, sPH, sConductividad, sTurbidez, sTDS;
sensor todosLosSensores[] = {sTemperatura, sPH, sConductividad, sTurbidez, sTDS}; // crear vector con todos los sensores

// Para painless mesh
////////////////////////////////////////////////////////////////
#include "painlessMesh.h"

#define   MESH_PREFIX     "redMeshParqueIndustrialZeta"
#define   MESH_PASSWORD   "TEC_Zeta_acueducto=mesh"
#define   MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

void sendMessage(); // para compilar

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  //String msg = "Hi from node1";
  //msg += mesh.getNodeId();
  //mesh.sendBroadcast( msg );
  JsonObject resultadoJsonPru = todosLosSensores[2].obtenerArchivoJson();
  String mensaje;
  serializeJson(resultadoJsonPru, mensaje);
  //mensaje = "Hi from node1"; // provando
  //mensaje += mesh.getNodeId();
  mesh.sendBroadcast( mensaje );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 3 )); // Establece un intervalo aleatorio de tiempo
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  //Serial2.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
    //Serial2.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
  //Serial2.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
    //Serial2.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setupRedMesh(){
//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  //mesh.onNewConnection(&newConnectionCallback);
  //mesh.onChangedConnections(&changedConnectionCallback);
  //mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);      // permite que se mantegan coordinados los tiempos de los dispostivos

  mesh.setContainsRoot(true); // debe hacerse en todos los dispositvos
  mesh.initOTAReceive("otareceiverDispTipo2"); // permite recibir actualizaciones por OTA

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void setup(){
  Serial.begin(115200);

  // Probar red mesh
  setupRedMesh();
  
  filtro1.caracteristicas(1,f1_1,f1_2,rele1_1);
  if (!filtro1.inicializar()){                     // Enviar true como parametro para activar la logica negativa en los reles
    Serial.println("Error al iniciar el filtro 1");
  }
  
  filtro1.activarLogicaNegativaEnReles(); // Habilitar si los reles trabajan con logica negativa
  filtro1.colocarEtapaServicio(); // pone el filtro en posicion de servicio
  //filtro1.aplicarRetrolavado(5,3);

  funcionPruebaMenu();
  funcionPruebaDeSensores();
  vTaskDelay(pdMS_TO_TICKS(1000));
  ui.mostrarLecturasSensores(todosLosSensores); // provando
      
}

void loop(){
  Serial.println(todosLosSensores[0].devolverParametroFisico());
  mesh.update();
  /*
  Serial.print("Voltaje turbidez: ");
  Serial.print(todosLosSensores[3].devolverVoltaje());
  Serial.print(" Voltaje pH: ");
  Serial.print(todosLosSensores[1].devolverVoltaje());
  Serial.print(" Temperatura: ");
  Serial.print(todosLosSensores[0].devolverParametroFisico());
  Serial.println(todosLosSensores[0].devolverUnidadesFisicas());
  vTaskDelay(pdMS_TO_TICKS(1000));
  */

  /*
  JsonObject resultadoJson = todosLosSensores[2].obtenerArchivoJson();
  serializeJson(resultadoJson, Serial);
  Serial.println();
  vTaskDelay(pdMS_TO_TICKS(1000));
  */  
} // fin del loop


void funcionPruebaDeSensores(){
  //Funcion para verificar funcionamiento de clase sensor
  // Inciar los sensores:
  todosLosSensores[0].inicializar("Temperatura", sensorTemp, pin_Temp, false);                    // false, no utiliza ADC
  todosLosSensores[1].inicializar("pH", sensorPH, pinADC_pH, true, &ads1);
  todosLosSensores[2].inicializar("Conductividad", sensorConductividad, pinADC_Cond, true, &ads1);
  todosLosSensores[3].inicializar("Turbidez", sensorTurbidez, pinADC_Turb, true, &ads1);
  todosLosSensores[4].inicializar("TDS", sensorTDS, pinADC_Cond, true, &ads1);                           // usa el mismo sensor de conductividad
}

void funcionPruebaMenu(){
  String titulosMenuPrincipal[] = {
    "Hacer retrolavado",
    "Ir a pos. servicio",
    "Apagar alarma",
    "Mediciones sensores",
    "Red mesh",
    "Configuraciones"};
  menu menuPrincipal;
  int numDeOpciones = (sizeof(titulosMenuPrincipal)/sizeof(titulosMenuPrincipal[0])); // determinar la cantidad de elementos

  menuPrincipal.configurarMenu(0, numDeOpciones, "Menu Principal", titulosMenuPrincipal);
  menuPrincipal.imprimirOpcionesEnSerial();

  ////
  menu menuSecundario;
  String titulosMenuSecundario[] = {"Reinicio", "Loc"};
  int numDeOpcionesSec = (sizeof(titulosMenuSecundario)/sizeof(titulosMenuSecundario[0])); // determinar la cantidad de elementos
  menuSecundario.configurarMenu(1, numDeOpcionesSec, "Menu 2", titulosMenuSecundario);
  menuSecundario.imprimirOpcionesEnSerial();

  //// Crear la ui de la pantalla
  menu todosLosMenus[] = {menuPrincipal,menuSecundario}; // Vector de los menus
  ui.asociarMenu(2, todosLosMenus);
  ui.imprimirTitulosDeMenusSerial();

  ////////////////////////////////
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  ui.asociarPantalla(display);
  ui.setupPantallaOled(I2C_SDA, I2C_SCL);
  ui.mostrarMenuEnOLED(menuPrincipal);

  vTaskDelay(pdMS_TO_TICKS(2000)); // espera
  menuPrincipal.opcionSelecionada = 1;
  ui.mostrarMenuEnOLED(menuPrincipal);

  vTaskDelay(pdMS_TO_TICKS(2000)); // espera
  ui.mostrarMenuEnOLED(menuSecundario);
}




