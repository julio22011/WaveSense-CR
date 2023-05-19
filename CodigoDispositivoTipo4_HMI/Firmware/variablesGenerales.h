

#include <Hash.h>
#include <elegantWebpage.h>

/**************************************************************** 
 * En este archivo se realizan las configuraciones del dispositivo
 *
******************************************************************/

//=====================================================================
//           Librerias utilizadas
//=====================================================================

#include "lvgl.h"                     // para evitar error con ui.h
#include <Adafruit_MCP23X17.h>        // Libreria para usar el expansor de puestas
#include <AsyncElegantOTA.h>          // OTA
AsyncWebServer server(80);
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#include <nvs_flash.h>                // Para la funcion de reset de la particion
#include <analogWrite.h>              // Libraria para poder utilizar analogWrite con ESP32

// Clases
#include "clases/claseMensajes.h"
#include "clases/claseSensorData.h"
#include "clases/claseFiltroData.h"
#include "clases/claseMacromedidorData.h"
#include "clases/claseBotones.h" // clase para interpretar los botones
#include "clases/claseBateriaUI.h" // clase para mostrar el estado de la baria

// Funciones especiales
#include "funcionesEspeciales/funcionesSpiffs.h"  // funciones para utilizar la memoria spiffis del ESP32

//=====================================================================
//      Definiciones de objetos de uso general
//=====================================================================
Adafruit_MCP23X17 mcp; // Crea objeto de tipo MCP

Preferences preferences;  // para guardar datos en la memoria NVR

// Clases de recepcion de datos
filtroData filtroData1, filtroData2, filtroData3;
filtroData todosLosFitrosData[] = {filtroData1, filtroData2, filtroData3}; // matriz de filtros
sensorData sdTemperatura, sdPH, sdConductividad, sdTurbidez, sdTDS;
sensorData todosLosSensoresData[] = {sdTemperatura, sdPH, sdConductividad, sdTurbidez, sdTDS};

mensaje gestorMensajes;
botones botonesHMI;     // crear instancia de los botones
bateriaUI bateriaUI;      // crea instancia para mostrar el porcentaje de bateria

// Timers de LVGL
lv_timer_t * timer;
lv_timer_t * timerConf;

//=====================================================================
//      Para el uso de archivos Json
//=====================================================================
// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
DynamicJsonDocument jsonBuffer(1024); // Crear instancia para los documentos JSON

//=====================================================================
//      Variables para recepcion de Json
//=====================================================================
String datoRecibido;
bool mensajeNuevo = false;

//=====================================================================
//      Definiciones de pines, variables y otros datos
//=====================================================================

// Datos para la conexion WiFi
//--------------------------------------------------------------------
String ssidSt     = preferences.getString("ssid", "KONOHA");              //"KONOHA";        // char*
String passwordSt = preferences.getString("password", "familiars58");     //"familiars58";  // char*

char ssid[40];      //[ssidSt.length() + 1]; 
char password[40];  //[passwordSt.length() + 1];

void recuperarContasenaWiFi(){
  strcpy(ssid, ssidSt.c_str());
  strcpy(password, passwordSt.c_str());
}

const char* APssid = "WiFi-Replicator-Julio";
const char* APpassword = "familiars58";

// Archivo para almacenar los datos de calibracion (aun falta sistema de calibracion)
//--------------------------------------------------------------------
#define CALIBRATION_FILE "/calibrationData3" // archivo donde se guardan lo datos de calibracion dentro de sniffs


// Pines de conexion del microcontrolador y el expansor de puertas (MCP)
//--------------------------------------------------------------------
#define botones 36   // antiguo, no usar
#define analogoX 39
#define analogoY 34
#define fotocelda 35
//#define botonAnalogo 34   // No tiene en este modelo
#define bateria 32
#define vibrador 33
#define ledPantalla 17

///////////////////////////////
// Pines para I2C:
#define I2C_SDA 21
#define I2C_SCL 22

///////////////////////////////
// Pines de los MCP:
#define led_amarillo_MCP 0

///////////////////////////////
// Serial con ESP32 secundaria:
#define RX_ESP 14
#define TX_ESP 12

///////////////////////////////
// Chip select para la SD:
#define SD_CS 5

///////////////////////////////
// Conexion del amplificador I2S:
#define BCLK_Ampl 27
#define LRC_Ampl 26
#define DIN_Ampl 25

// Para los botones
//-----------------------------
#define pinDeLosBotones 36
#define pinTransistor 33
uint8_t tipoBotonesDisp = 1;  // "0" para dispositivo tipo 2 y "1" para el HMI (en el futuro se acivaria el joystick)
//int limitesDeLect[] = {100,3900,4095,2700,3000,1600,2000,600,1000};  // limite de no presionado, limte min y max de cada boton
int limitesDeLect[] = {100,4095,3900,3000,2700,2000,1600,1000,600};  // limite de no presionado, limte min y max de cada boton
int limitesDeLectJoy[] = {2300,1500,2300,1500};   // limiteXup, limiteXdown, limiteYup, limiteYdown


// variables del sistema booleanas
//--------------------------------------------------------------------
bool actualizarHora = false;
bool errorEnHora = false;
uint16_t opcionSeleccionada;  // para registrar la opcion seleccionada de la lista de sensores "dd"

// variables del sistema booleanas (para configuracion)
//--------------------------------------------------------------------

// Variable para el buffer del serial bluetooth
//--------------------------------------------------------------------

// Variables para la bateria
//--------------------------------------------------------------------
