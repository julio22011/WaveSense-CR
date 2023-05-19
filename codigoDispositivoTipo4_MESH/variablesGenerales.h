//=====================================================================
//      Credenciales
//=====================================================================


// Credenciales de ThingSpeak
#define channelID 1097748
#define apikey "2YPTEQDZPOFMIV40"

//=====================================================================
//      Librerias de codigo
//=====================================================================


// Para painless mesh y servidor local
#include <WiFiClient.h> // para poder conectarse a router de Internet
#include "painlessMesh.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <AsyncElegantOTA.h>   // para hacer ota por el navegador
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria

// Para el metodo post y get
#include <HTTPClient.h>
const char* serverName = "docs.google.com";
const char* serverName2 = "www.google.com";

// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

//https://docs.google.com/forms/d/e/1FAIpQLSfzXVoGyFJpHrF6s6Slpw7AKSetiaOwNH3qyR-ZRlJg8o9M4A/formResponse?usp=pp_url&entry.1016553776=12&entry.1220796517=12&entry.574086702=12&entry.1428969291=23&entry.94691886=22&entry.1646211311=13&entry.439089844=31&entry.1066755542=34&entry.789382520=53&entry.827615926=2&entry.1336955858=f&entry.2102956456=3&entry.157041573=2&entry.380290552=2";

//=====================================================================
//      GPIO utilizados
//=====================================================================
#define RX_ESP 4  // 12
#define TX_ESP 14


//=====================================================================
//      Variables para recepcion de Json
//=====================================================================
String datoRecibido;
bool mensajeNuevo = false;


//=====================================================================
//      Variables de configuracion en memoeria permanente
//=====================================================================

// objeto que permite guardar datos en la memoria permanente
Preferences preferences;  // para guardar datos en la memoria NVR

TSTRING ssidModem = "KONOHA2";
TSTRING passwordModem = "familiars58";
TSTRING ssidModem2 = "indefinido";
TSTRING passwordModem2 = "indefinido";

void recuperarContasenaWiFi(){
  ssidModem = preferences.getString("ssid", "KONOHA2");              //"KONOHA";        // char*
  passwordModem = preferences.getString("password", "familiars58");     //"familiars58";  // char*
  //strcpy(ssid, ssidSt.c_str());
  //strcpy(password, passwordSt.c_str());
}


//=====================================================================
//      variables del sistema booleanas
//=====================================================================

// Para la hora:
//-------------------------------------
bool actualizarHora = false;
bool errorEnHora = false;

//=====================================================================
//      Archivos adicionales del programa
//=====================================================================

#include "envioDatosInternet.h"
#include "libreriasCreadas/firebaseServices.h"
