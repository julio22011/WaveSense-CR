
/*
 * Aqui se definin las funciones que se ejecutan segun la etiqueta del mensaje recibido
 * (son distintas para HMI o NET)
*/


#ifdef isHMI

// Guardado de Answers
//****************************************************************
struct datosProcesados* WifiListSave(DynamicJsonDocument doc, struct datosProcesados* datos){

  // Nota: falta usar el json para definir valores

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
  datos->WifiListData.SSIDs = SSIDs;

  // Retornar resultado
  //-------------------------------------------------
  return datos;
}


// Guardado de Update
//****************************************************************


// Guardado de  Datos
//****************************************************************


#endif

//__________________________________________________________________
//__________________________________________________________________o
//__________________________________________________________________
//__________________________________________________________________o

#ifdef isNET

// Answers
//****************************************************************

// Update
//****************************************************************

// Datos
//****************************************************************


#endif
