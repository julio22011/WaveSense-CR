
/*
 * Aqui se definin las funciones que se ejecutan segun la etiqueta del mensaje recibido
 * (son distintas para HMI o NET)
*/


#ifdef isHMI

// Answers
//****************************************************************
struct datosProcesados* WifiListSave(DynamicJsonDocument * doc, struct datosProcesados* datos){

  // Crear estructura para almacenar las redes recibidas
  //-------------------------------------------------
  struct WiFiCredentialsData SSIDs[ssidBufferSize]; // estructura de redes
  SSIDs[0].SSID = "prueba";
  //...

  
  // Conformar WifiListData
  //-------------------------------------------------
  //datos->WifiListData.SSIDs = ;
  datos->WifiListData.ActualWiFiConnected = "none!!!";
  
}

// Update
//****************************************************************


// Datos
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
