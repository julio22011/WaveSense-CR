
/*
 * Aqui se definin las funciones que se ejecutan segun la etiqueta del mensaje recibido
 * (son distintas para HMI o NET)
*/


#ifdef isHMI

// Guardado de Answers
//8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8

struct datosProcesados* WifiListSave(DynamicJsonDocument doc, struct datosProcesados* datos){

  // Obtener los datos del json
  //-------------------------------------------------
  String ActualWiFiConnected = doc["ActualWiFiConnected"].as<String>();  // agregar al documento
  JsonArray arraySSIDs = doc["SSIDs"].as<JsonArray>();
  JsonArray arrayPass = doc["passwords"].as<JsonArray>();
  JsonArray arraySig = doc["sinalDBs"].as<JsonArray>();
  int n = arraySSIDs.size();

  /*
  for (const JsonVariant& value : array) {
    String stringValue = value.as<String>();
  }
  */

  // Crear estructura para almacenar las redes recibidas
  //-------------------------------------------------
  struct WiFiCredentialsData SSIDs[ssidBufferSize];        // estructura de redes
  
  for (size_t i=0; i<arraySSIDs.size(); i++) {
    SSIDs[i].SSID =           arraySSIDs[i].as<String>();  // almacenar el nombre de la red
    SSIDs[i].password =       arrayPass[i].as<String>();   // almacenar la contrasena de la red
    SSIDs[i].SignalStrength = arraySig[i].as<float>();     // almacenar la intensidad de senal de la red en dB
  }

  // Conformar WifiListData
  //-------------------------------------------------
  datos->WifiListData.foundNetworks = n;
  datos->WifiListData.ActualWiFiConnected = ActualWiFiConnected;
  datos->WifiListData.SSIDs = SSIDs; // asigna todo de las distintas redes: SSIDs, contrasenas, senales

  // Retornar resultado
  //-------------------------------------------------
  return datos;
}

struct datosProcesados* timestampSave(DynamicJsonDocument doc, struct datosProcesados* datos){

  // Obtener los datos del json
  //-------------------------------------------------
  long int timestampSec = doc["timestampSec"].as<long int>();
  long int timestampMiliSec = doc["timestampMiliSec"].as<long int>();

  // Crear estructura para almacenar el nuevo timestamp
  //-------------------------------------------------
  datos->timestampData.timestampNumberSeconds = timestampSec;
  datos->timestampData.timestampNumberMiliSeconds = timestampMiliSec;

  // Retornar resultado
  //-------------------------------------------------
  return datos;
}

struct datosProcesados* nodeListSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

// Guardado de Update
//8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8
struct datosProcesados* ConnectionsChangedSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

// Guardado de  Datos
//8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8
struct datosProcesados* MsgPlatformSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* alarmGotActivatedSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* NewDataSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

#endif

//__________________________________________________________________
//__________________________________________________________________o
//__________________________________________________________________
//__________________________________________________________________o

#ifdef isNET

// Answers
//8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8
// (no hay nada en el protocolo)

// Update
//8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8
struct datosProcesados* WiFiCredentialsSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* SensorCalibrationSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* PlatformCredentialsSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* AlarmLimitsSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* FilterScheduleSave(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* ConfigDispType1Save(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

struct datosProcesados* ConfigDispType23Save(DynamicJsonDocument doc, struct datosProcesados* datos){
  //
}

// Datos
//8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8-8
// (no hay nada en el protocolo)

#endif
