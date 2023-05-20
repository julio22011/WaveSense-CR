
// struct: permiten almacenar informacion con estructuras de variables diversas
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "estructurasData.h"  // Aqui estan las extructuras que permiten almacenar los datos recibidos

// Etiqueta de mensajes: permite almacenar las clasificaciones de un mensaje
// --------------------------
struct etiqueta {
  int8_t type;
  int8_t command;
  int8_t answer;
  bool error = false; // Almacena true si hubo un error
};


//********************************************************************************
// Estructura de los datos procesados
// ---------------------------
struct datosProcesados {
  struct etiqueta etiqueta; // etiqueta de datos
  bool error = false;

  // Distintos posibles datos que se pueden recibir en estructuras
  struct WiFiCredentialsData WiFiCredentialsData;
  struct WifiListData WifiListData;
  struct timestampData timestampData;
  struct nodeListData nodeListData;
  struct SensorCalibrationData SensorCalibrationData;
  struct PlatformCredentialsData PlatformCredentialsData;
  struct MsgPlatformData MsgPlatformData;
  struct ConnectionsChangedData ConnectionsChangedData;
  struct AlarmEmailData AlarmEmailData;
  struct AlarmGotActivatedData AlarmGotActivatedData; 
};
