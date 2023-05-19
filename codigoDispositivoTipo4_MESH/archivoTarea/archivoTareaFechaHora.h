
/*
 * Esta tarea se encarga de recuperar la hora de internet y actualizarla (mod para redes mesh)
*/

//#include <WiFi.h>                       // ya incluido
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
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    errorEnHora = true;
    return false;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  return true;
}

// Funcion de la tarea
void tareaFechaHora(void * parameters){

  while(WiFi.status() != WL_CONNECTED){
    vTaskDelay(5000);
  } // no hacer nada hasta que haya conexion con internet

  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);

  while(true){
    vTaskDelay(pdMS_TO_TICKS(5000));
    printLocalTime();
    actualizarHora = true; 
  }
  vTaskDelete(NULL);  // elimina la tarea
}





