// Credenciales Proyecto Firebase
#define FIREBASE_HOST "https://wavesense-aef60.firebaseio.com"
#define FIREBASE_AUTH "i4e0s4wXhIsW1kuYP2wBcv2j96mkeUYiU7W9kx0I"

/////////////////////////////////////////////////////////

// Firebase Data object
FirebaseData firebaseData;


#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials
#define WIFI_SSID "WIFI_AP"
#define WIFI_PASSWORD "WIFI_PASSWORD"
*/

/* 2. Define the API Key */
#define API_KEY "AIzaSyBbhFDTW-dZYuI3aQzSxDN9BZK0JH1Db_Y"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://wavesense-aef60.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "wavesensesensores@gmail.com" //julio220115838@gmail.com
#define USER_PASSWORD "sensores2022" //gato335838

FirebaseAuth auth;
FirebaseConfig config;

void firebaseSetup() {
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    //Or use legacy authenticate method
    //config.database_url = DATABASE_URL;
    //config.signer.tokens.legacy_token = "i4e0s4wXhIsW1kuYP2wBcv2j96mkeUYiU7W9kx0I";

    //To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);
}

////////////////////////////////////////////////////////////////
///************************************************************
//////////////////////////////////////////////////////////////////


// Rutas y datos del sensor, estas indican donde se guardan los datos en firebse
String idsensor = "/WaveSenseEsp32-v1-" + String(WiFi.macAddress()); // define la identificación del sensor
// ruta del pH
String nodopH = "/lecturaspH";
// ruta de la temperatura
String nodoTurb = "/lecturasTurbidez";
// ruta de la presion
String nodoPresion = "/lecturasPresion";
// ruta de l caudal
String nodoCaudal = "/lecturasCaudal";

//Valores de prueba
float pH = 12;
float turbidez = 0.2;
float presion = 0.103;
float caudal = 203.3; 

// Datos del dispositivo
const int versiondelcodigo = 1;
String tipodeplaca = "TTGO.tcall.esp32"; // indica el tipo de placa. Informacion de esta placa https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800
bool activarOTA = false;  // posteriormente permitira activar la actualizaciones via ota mediante el codigo en ActualizacionOTA.h (funcionalidad extra)

// variables booleanas
bool conectadoWifi = false; // guarda el estado de la coneccion wifi
bool iterar = true; // inicia el envio de datos de los sensores
bool enviado = false; // indica si se han enviado datos a firebase
bool enviadoSMS = false; // registra si ya se ha enviado un SMS


void enviarInfoDelSensor(){   // función para guardar en Firebase la información del dispositivo
  bool error = false;
  // Enviar a firebase los informacion del sensor
  error = Firebase.RTDB.setInt(&firebaseData, "/Sensores" + idsensor + "/Informacion/Version del codigo", versiondelcodigo);
  error = Firebase.RTDB.setString(&firebaseData, "/Sensores" + idsensor + "/Informacion/Tipo de placa", tipodeplaca);
  error = Firebase.RTDB.setBool(&firebaseData, "/Sensores" + idsensor + "/Informacion/estadoOTA", activarOTA);
  //error = Firebase.RTDB.setInt(&firebaseData, "/Sensores" + idsensor + "/Informacion/ipLocal", WiFi.localIP());

  Serial.println();
  //Serial.printf("Firebase> %s", error ? "Sen ha enviado la información del sensor al servidor." : firebaseData.errorReason().c_str());
}


void enviarDatosDeSensores(){  // función para registrar los datos de los sensores en Firebase
  // push de datos (push es una manera de registrar nuevos valores en la base de datos, float es para registrar valores con coma)
  //Firebase.RTDB.pushFloat(&firebaseData, F("/Sensores"), pH);
  
  Firebase.RTDB.pushFloat(&firebaseData, "/Sensores" + idsensor + nodopH, pH); 
  Firebase.RTDB.pushFloat(&firebaseData, "/Sensores" + idsensor + nodoTurb, turbidez);
  Firebase.RTDB.pushFloat(&firebaseData, "/Sensores" + idsensor + nodoPresion, presion);
  Firebase.RTDB.pushFloat(&firebaseData, "/Sensores" + idsensor + nodoCaudal, caudal);
  Serial.println();
  Serial.println("Actualización de los sensores enviada al servidor exitosamente.");
}





/*
void enviarUbicacionAFirebase(){ // esta función obtiene la ubicación sin necesidad de GPS mediante una API de Google y la guarda en Firebase
  WifiLocation location(googleApiKey); // crea una localizacion
  //Localizacion Wifi
  location_t loc = location.getGeoFromWiFi(); // obtiene la localizacion
  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  Serial.println("Latitude: " + String(loc.lat, 7));
  Serial.println("Longitude: " + String(loc.lon, 7));
  Serial.println("Accuracy: " + String(loc.accuracy));

  if (loc.accuracy < 300){
    // registrar ubicacion
    delay(100);
    Firebase.setFloat(firebaseData, "/Sensores" + idsensor + "/Ubicacion/latitud", loc.lat);
    delay(100);
    Firebase.setFloat(firebaseData, "/Sensores" + idsensor + "/Ubicacion/longitud", loc.lon);
    delay(100);
    Firebase.setFloat(firebaseData, "/Sensores" + idsensor + "/Ubicacion/precision", loc.accuracy);
    delay(100);
    Serial.println();
    Serial.println("Ubicación registrada en el servidor.");
  }
  else {
    Serial.println();
    Serial.println("Precisión deficiente. Se mantiene la ubicación anterior en el servidor.");
  }
}
*/