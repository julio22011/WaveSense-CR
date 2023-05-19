
// struct: permiten almacenar informacion con estructuras de variables diversas
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Etiqueta de mensajes: permite almacenar las clasificaciones de un mensaje
// --------------------------
struct etiqueta {
  int8_t type;
  int8_t command;
  int8_t answer;
  bool error = false; // Almacena true si hubo un error
};

// Busqueda de redes WiFi
// ---------------------------
struct searchWiFi{
  const char** ssidList;
  const char** passwordList;
  // Señal dB ...
};

// Credenciales nuevas WiFi
// ---------------------------
struct credentialsWiFi{
  const char* ssid;
  const char* password;
};

// Fecha nueva
// ---------------------------
struct newTime{
  long int timestamp;
  bool error;
};


//********************************************************************************
// Estructura de los datos procesados
// ---------------------------
struct datosProcesados {
  struct etiqueta etiqueta; // etiqueta de datos
  bool error = false;

  // Distintos posibles datos que se pueden recibir en estructuras
  struct searchWiFi searchWiFi;
  struct credentialsWiFi credentialsWiFi;
  struct newTime newTime;
};
