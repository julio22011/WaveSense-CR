

//***************************************************************************************
// Librerias
//***************************************************************************************

#include <Arduino.h>
#if defined(ESP32) || defined(PICO_RP2040)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h> // Provide the token generation process info.
#include <addons/RTDBHelper.h>  // Provide the RTDB payload printing info and other helper functions.

//#include "time.h"  // libreria de tiempos
#include <ESP32Time.h>

//***************************************************************************************
// Datos de acceso
//***************************************************************************************

/* 1. Define the WiFi credentials */
#define WIFI_SSID "KONOHA2"
#define WIFI_PASSWORD "familiars58"

/* 2. Define the API Key */
#define API_KEY "AIzaSyBbhFDTW-dZYuI3aQzSxDN9BZK0JH1Db_Y"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://wavesense-aef60.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "prueba@gmail.com"
#define USER_PASSWORD "pruebaContra"

//***************************************************************************************
// Objetos y variables globales
//***************************************************************************************

FirebaseData fbdo; // Define Firebase Data object

FirebaseAuth auth;
FirebaseConfig config;

//struct tm timeinfo;          // extructura de datos para la hora
int timeZone = -6;
ESP32Time rtc(3600*timeZone);
bool gotTimestamp = false;
uint16_t timeAge = 0;       // permite asignarle una edad a la hora, para actualizar la hora del rtc cada cierto tiempo
uint16_t maxTimeAge = 500;  // edad maxima del tiempo del rtc (espezado en intentos de envio de datos)

//***************************************************************************************
// Funciones
//***************************************************************************************

// Funcion para hacer los procesos iniciales
void setupFirebaseRTDB(){
  
  //Serial.begin(115200); // iniciar el monitor serial

/* Comentado porque el while hace que no funcione la red mesh cuando no hay internet

  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    unsigned long ms = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
    Serial.println(); Serial.print("Connected with IP: "); Serial.println(WiFi.localIP()); Serial.println();
  }
*/
  
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  // For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void sendSettingsRTDB(String nodesJson){
  if (Firebase.ready()){
    FirebaseJson json;

    // Datos de configuracion
    String esp32id = "esp32-x"; // (provisional, hay que cambiarlo por el id asi: std::to_string(chipId))
    String ruta = "/deviceReadings/" + esp32id + "/settings";  // dirigir la ruta al apartado de ajustes
    json.set("connectedNodes",  (String)nodesJson); // datos de los nodo conectados al root

    // Enviar datos
    //Serial.printf("Enviando settings... %s\n", Firebase.RTDB.setString(&fbdo, ruta + "/connectedNodes", nodesJson.c_str()) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Enviando configuraciones a RTDB... %s\n", Firebase.RTDB.setJSON(&fbdo, ruta, &json) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());
  }
}

String esp32id = "esp32-x"; // es el ID del dispositivo (hay que cambiar la x por el id del chip o el mac)

// Funcion para enviar datos
void sendDataRTDB(String msg, String nodesJson){  // recibir dos vectores, uno con los nombres y otro con los valores

  if (Firebase.ready()){

    timeAge++; // incrementa la edad del tiempo. La edad es para que cada cierto tiempo se vuelva a solicitar el timestamp al servidor
    
    // Obtener el timestamp para ordenar la ruta y guardar hora en el rtc
    //----------------------------------------------
    if (!gotTimestamp && timeAge < maxTimeAge)Serial.printf("Set timestamp... %s\n", Firebase.RTDB.setTimestamp(&fbdo, "/deviceReadings/" + esp32id + "/lastTime/timestamp") ? "ok" : fbdo.errorReason().c_str());
    if (fbdo.httpCode() == FIREBASE_ERROR_HTTP_CODE_OK && !gotTimestamp && timeAge < maxTimeAge)
    {
      // Timestamp saved in millisecond, get its seconds from int value
      Serial.print("TIMESTAMP (Seconds): "); Serial.println(fbdo.to<int>());
      
      // Due to bugs in Serial.print in Arduino library, use printf to print double instead.
      printf("TIMESTAMP (milliSeconds): %lld\n", fbdo.to<uint64_t>());

      // Poner timestamp en el rtc del microcontrolador
      rtc.setTime(fbdo.to<int>());
      Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format
      //Serial.println(rtc.getDate());          //  (String) Sun, Jan 17 2021 
      //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
      gotTimestamp = true;    
      timeAge = 0; 
    }
    
    //-----------------------------------------------
    if (gotTimestamp){  // continua una vez se ha actualizado la hora

      // Generar la ruta con el timestamp
      //----------------------------------------------
      String rutaTime = rtc.getTime("/%Y/%B/%d/%H");                //utilizar la hora actualiza del rtc para construir la ruta "%A, %B %d %Y %H:%M:%S"
      String ruta = "/deviceReadings/" + esp32id + "/readings" + rutaTime;  // agregarle a la ruta el orden de la fecha
      
      String milisegundosStr;
      if     (rtc.getMillis()>99) milisegundosStr = String(rtc.getMillis());
      else if(rtc.getMillis()>9)  milisegundosStr = "0" + String(rtc.getMillis());  // permite agregar ceros faltantes
      else                        milisegundosStr = "00" + String(rtc.getMillis()); // permite agregar ceros faltantes
      
      String rutaTimestamp = "/" + String(rtc.getEpoch()) + milisegundosStr;        // para etiquetar datos con el timestamp del esp32

      // Enviar los datos
      //----------------------------------------------
      DeserializationError error = deserializeJson(jsonBufferTh, msg);
      JsonObject ultimoJsonRecibido = jsonBufferTh.as<JsonObject>();

      FirebaseJson json; // To set and push data with timestamp, requires the JSON data with .sv placeholder

      json.set("temp", (float) ultimoJsonRecibido["Temp"]);
      json.set("ph",   (float) ultimoJsonRecibido["pH"]); 
      json.set("cond", (float) ultimoJsonRecibido["Cond"]);
      json.set("tds",  (float) ultimoJsonRecibido["Turb"]);
      json.set("tds",  (float) ultimoJsonRecibido["TDS"]);
      
      // now we will set the timestamp value at Ts
      json.set("timeAt/.sv", "timestamp"); // .sv is the required place holder for sever value which currently supports only string "timestamp" as a value

      //---------
      // Datos de configuracion
      //ruta = "/deviceReadings/" + esp32id + "/settings";  // dirigir la ruta al apartado de ajustes
      //json.set("connectedNodes",  (String)nodesJson); // datos de los nodo conectados al root
      
      //---------------------------
      // Enviar los datos. Set data with timestamp
      Serial.printf("Set data with timestamp... %s\n", Firebase.RTDB.setJSON(&fbdo, ruta + rutaTimestamp, &json) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());

      // Push data with timestamp
      //Serial.printf("Push data with timestamp... %s\n", Firebase.RTDB.pushJSON(&fbdo, ruta, &json) ? "ok" : fbdo.errorReason().c_str());

    } // fin if-2

  } // fin if-1
   
} // fin fun


/* Ejemplo para enviar y recuperar datos
 *  
      FirebaseJson json; // To set and push data with timestamp, requires the JSON data with .sv placeholder

      json.set("Data", "Hello");
      // now we will set the timestamp value at Ts
      json.set("Ts/.sv", "timestamp"); // .sv is the required place holder for sever value which currently supports only string "timestamp" as a value

      // Set data with timestamp
      Serial.printf("Set data with timestamp... %s\n", Firebase.RTDB.setJSON(&fbdo, ruta, &json) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());

      // Push data with timestamp
      Serial.printf("Push data with timestamp... %s\n", Firebase.RTDB.pushJSON(&fbdo, ruta, &json) ? "ok" : fbdo.errorReason().c_str());

      // Get previous pushed data
      Serial.printf("Get previous pushed data... %s\n", Firebase.RTDB.getJSON(&fbdo, ruta + fbdo.pushName()) ? fbdo.to<FirebaseJson>().raw() : fbdo.errorReason().c_str());
 */
