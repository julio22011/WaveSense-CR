
/*
 * Definicion de las formatos(cajas) para almacenar los datos que vienen de los comandos
*/

// Lista de formatos con {data}
//********************************
// WiFiCredentials {data} (3)
// WifiList {data} (2)
// timestamp {data} (6)
// nodeList {data} (9)
// SensorCalibration {data} (10)
// PlatformCredentials {data} (16)
// MsgPlatform {data} (18)
// ConnectionsChanged {data} (21)
// AlarmEmail {data} (27)
// AlarmGotActivated {data} (30)
// FilterSchedule {data} (35)
// ConfigDispType1 {data} (38)
// ConfigDispType23 {data} (41)
// NewData {data} (44)
// ...

// WiFiCredentials {data} (3) -->
//********************************
struct WiFiCredentialsData{
  String SSID;
  String password;
  float SignalStrength;
};

// WifiList {data} (2)
//********************************
struct WifiListData{
  int foundNetworks;
  struct WiFiCredentialsData * SSIDs; // extructura de redes
  String ActualWiFiConnected = "none!!!";     // es "none!!!" si no esta conectado
};

// timestamp {data} (6)
//********************************
struct timestampData{
  long int timestampNumberSeconds = 0;
  long int timestampNumberMiliSeconds = 0;
};

// nodeList {data} (9)
//********************************
struct nodeListData{
  int * nodesID;
  float  * nodesSignalStrength;
  int * accessNode;                // podria dar problemas si un nodo tiene mas de una conexion
};

// ConnectionsChanged {data} (21)
//********************************
struct ConnectionsChangedData{
  int * nodesID;
  float * nodesSignalStrength;
  int * accessNode;                // podria dar problemas si un nodo tiene mas de una conexion
};

// SensorCalibration {data} (10)
//********************************
struct SensorCalibrationData{
  int nodeID;
  int sensorID;
  int sensorType;
  float newValues[8];
};

// PlatformCredentials {data} (16)
//********************************
struct PlatformCredentialsData{
  String key = "none!!!";       // "none!!!" por defecto
  String email;
  String password;
};

// MsgPlatform {data} (18)
//********************************
struct MsgPlatformData{
  String message;  // Texto con el mensaje de la plataforma
  //...
};

// AlarmEmail {data} (27)
//********************************
struct AlarmEmailData{
  String alarmEmail;
  String alarmNumber = "none!!!";
};

// AlarmGotActivated {data} (30)
//********************************
struct AlarmGotActivatedData{
  String reason = "Indefinido";
};

// FilterSchedule {data} (35)
//********************************
struct FilterScheduleData{
  int nodeID;
  int filterID;
  bool * state;   // [] por definir. Para evitar errores, hay que usar punteros para los arrays. No usar []
  int * retro1;   // [] por definir
  int * retro2;   // [] por definir
  int * retro3;   // [] por definir
  int * retro4;   // [] por definir
};

// ConfigDispType1 {data} (38)
//********************************
struct ConfigDispType1Data{
  int nodeID;
  bool eraseVolume;
  float unitsPerPulse;
  int updateSeconds;
};

// ConfigDispType23 {data} (41)
//********************************
struct ConfigDispType23Data{
  int nodeID;
  int updateSeconds;  
};

// NewData {data} (44)
//********************************
struct NewDataData{
  int nodeID;
  String dataType;
  //...
};
