// Opciones de depuracion
//---------------------------------------
//#define debugProtocoloJulio


// Incluir las librerias de terceros
//----------------------------------------
#include <ArduinoJson.h>


// Definir los comandos del HMI
//----------------------------------------
const char* commandsHMI[] = {
    // Realizar búsqueda de redes WiFi
    //--------------------------------
    "WiFiSearch",             // 1
    // Actualizar las credenciales de la red WiFi
    //--------------------------------
    "WiFiCredentials",        // 3
    // Solicitar la fecha
    //--------------------------------
    "Date",                   // 5
    // Solicitar los nodos que se encuentran conectados
    //--------------------------------
    "MeshNodesConnected",     // 8
    // Actualizar los datos de calibración de sensor/sensores
    //--------------------------------
    "SensorCalibration ",     // 10
    // Reiniciar el microcontrolador de la red
    //--------------------------------
    "Restart",                // 13
    // Actualizar las credenciales de la plataforma online (email y contraseña)
    //--------------------------------
    "PlatformCredentials",    // 16
    // Recepción de mensaje proveniente de la plataforma online (por ejemplo, la app)
    //--------------------------------
    "dataRecOk",              // 19
    "dataRecError",           // 20
    // Informar que han cambiado las conexiones de la red
    //--------------------------------
    "msgConnRecOk",           // 22
    "msgConnRecError",        // 23
    // Cambiar email de alarmas
    //--------------------------------
    "AlarmEmail",             // 24
    // Actualizar límites de las alarmas
    //--------------------------------
    "AlarmLimits",            // 27
    // Informar de alarma activada – silenciar buzzer
    //--------------------------------
    "msgAlarmRecOk",          // 31
    "msgAlarmRecError",       // 32
    "SilentAlarmBuzzer",      // 33
    // Actualizar horario/horarios de retrolavado de filtros
    //--------------------------------
    "FilterSchedule",         // 35
    // Configurar dispositivo tipo 1
    //--------------------------------
    "ConfigDispType1",        // 38
    // Configurar dispositivo tipo 2 y 3
    //--------------------------------
    "ConfigDispType23",       // 41
    // Nuevo dato de dispositivo de la red
    //--------------------------------
    "newDataOk",              // 45
    "newDataError",           // 46
    // Reiniciar el microcontrolador del HMI
    //--------------------------------
    "restartOk",              // 48
    "restartError",           // 49
    // Iniciar modo OTA en HMI (???) (hay que encontrar forma de enviar actualización sin WiFi)
    //--------------------------------
    "activateOTAOk ",         // -?
    "activateOTAError",       // -?
};


// Definir los comandos de la red
//----------------------------------------
const char* commandsNet[] = {
    "WifiList",               // 2
    "newWiFiCredOk",          // 4
    "timestamp",              // 6
    "noTimeError",            // 7
    "nodeList",               // 9
    "calibOk",                // 11
    "caliError",              // 12
    "restartOk",              // 14
    "restartError",           // 15
    "newPlatformCredOk",      // 17
    "MsgPlatform",            // 18
    "ConnectionsChanged",     // 21
    "emailUpdated",           // 25
    "emailUpdateError",       // 26
    "alarmLimUdated",         // 28
    "alarmLimError",          // 29
    "AlarmGotActivated",      // 30
    "silentAlarmBuzOk",       // 34
    "newFilterScheduleOk",    // 36
    "newFilterScheduleError", // 37
    "newConfig1Ok",           // 39
    "newConfig1Error",        // 40
    "newConfig23Ok",          // 42
    "newConfig23Error",       // 43
    "NewData",                // 44
    "Restart",                // 47
    "ActivateOTA",            // _?
};

/* ----------------------------------------------*/

// Types: para seleccionar el comportamiento del dispositivo (HMI o red)
#define asHMI 1
#define asNet 2

DynamicJsonDocument doc(1024); // documento dinamico para almacenar los Json

/* Clase para definir el protocolo de comunicacion entre el HMI y la red */
class protocoloJulio{

    private:

    // Variables privadas
    //--------------------------
    int8_t type; //  asHMI/asNet
    int commandsHMINumber = sizeof(commandsHMI)/sizeof(char*);
    int commandsNetNumber = sizeof(commandsNet)/sizeof(char*);
    JsonObject obj = doc.to<JsonObject>();

    public:

    // Variables publicas
    //--------------------------
    //

    //StaticJsonDocument<1024> doc; // documento estatico para almacenar los Json
    // Lo anterior se cambio por un documento dinamico que esta fuera de la clase

    // Constructor de la clase
    //----------------------------
    protocoloJulio(int8_t _type){
        type = _type; // define si es HMI o Red
    }

    // Funciones
    //-------------------------
    JsonObject reciveJson(String msgJson);
    int findCommandHMINumber(char* command);
    int findCommandNetNumber(char* command);

    int identifyCommandNumber(String msgJson);
};


// Funciones
//------------------------------------------------

// Identificar comando que envia el HMI
int protocoloJulio::findCommandHMINumber(char* command){
    for(int i=0; i<commandsHMINumber; i++){
        if(commandsHMI[i] == command){
            return i;
        }
    }
    Serial.println("Error al identificar numero de comando");
    return -1;  // error debido a que no se encontro el comando en la lista
}

// Identificar comando que envia la red
int protocoloJulio::findCommandNetNumber(char* command){
    for(int i=0; i<commandsNetNumber; i++){
        if(commandsNet[i] == command){
            return i;
        }
    }
    Serial.println("Error al identificar numero de comando");
    return -1;  // error debido a que no se encontro el comando en la lista
}

// Toma el string que se recibe desde uart y lo mete en el documento json, luego retorna un objeto json
JsonObject protocoloJulio::reciveJson(String msgJson){
    DeserializationError error = deserializeJson(doc, msgJson);
    if(error) Serial.println("Error al deserializar JSON");
    obj = doc.as<JsonObject>();
    #ifdef debugProtocoloJulio
      Serial.print("Mensajes deserializado: ");
      Serial.println(msgJson);
    #endif
    Serial.println(doc["julio"].as<String>());
    return obj;
}

// Funciones que usan otras funciones
//---------------------------------------------------

// Recibir mensaje json e identificar el numero de mensaje que le corresponde 
int protocoloJulio::identifyCommandNumber(String msgJson){
    JsonObject object = reciveJson(msgJson);
    if(type == asHMI)      return findCommandHMINumber(object["command"]);
    else if(type == asNet) return findCommandNetNumber(object["command"]);
    
    Serial.println("Error al identificar el tipo de dispositivo");
    return -2; // Indica error debido a asHMI o asNet
}


