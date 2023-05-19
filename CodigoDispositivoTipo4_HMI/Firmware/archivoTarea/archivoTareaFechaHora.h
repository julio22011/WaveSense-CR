#include "freertos/projdefs.h"

/*
 * Esta tarea se encarga de recuperar la hora de internet y actualizarla
*/
#include <WiFi.h>
#include "time.h"  // libreria de tiempos

//const char* ssid       = "KONOHA";        // ya indicado
//const char* password   = "familiars58";

const int GMT = -6;                        // desplazamiento horario de Costa Rica
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = GMT*3600;
const int   daylightOffset_sec = 0;

struct tm timeinfo; // extructura de datos para la hora

bool printLocalTime()
{
  if(errorEnHora){        // verficar la conexion si da error
    while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(pdMS_TO_TICKS(500));
      Serial.print(".");
    }
    errorEnHora = false;  // borra el estado de error para intentar imprimir la hora
  }

  if(!getLocalTime(&timeinfo)){
    //Serial.println("Failed to obtain time");
    errorEnHora = true;
    //vTaskDelete(NULL);  // elimina la tarea
    return false;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  return true;
}

// Funcion de la tarea
void tareaFechaHora(void * parameters){

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(pdMS_TO_TICKS(500));
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  //WiFi.disconnect(true);                    // cambiado para OTA
  //WiFi.mode(WIFI_OFF);   // jul

  while(true){
    vTaskDelay(pdMS_TO_TICKS(5000));
    printLocalTime();
    actualizarHora = true; 
  }
  vTaskDelete(NULL);  // elimina la tarea
}





