/************************************************************************************************
 * Esta clase permite guardar los datos que se reciben de cada sensor
 *
************************************************************************************************/

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif

#if !defined(claseSensorDataIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseSensorDataIncluida

// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

// Nombre para cada tipo de sensor
#define sensorTemp          1
#define sensorPH            2
#define sensorConductividad 3
#define sensorTurbidez      4
#define sensorTDS           5
#define sensorPres          6
#define sensorCaudal        7

DynamicJsonDocument jsonBufferSen(1024); // Crear instancia para los documentos JSON

class sensorData{

  private:

  public:

  // Variables privadas en la clase original
  int lecturaDigital;
  float voltaje;                // si es -1, es un sensor que no utiliza voltaje
  float corriente;              // si es -1, es un sensor que no utiliza corriente

  // Variables
  uint8_t tipoDeSensor;              // Permite saber que tipo de sensor es
  String parametro;                  // Ejemplo, turbidez
  bool usaADC;
  int valorMaximoADC;        // 4095 para ADC de 12 bit
  float voltajeMaximoADC;      // Voltaje al que corresponde la mayor lectura del ADC
  int pinDeConexion;
  float valorCalibracion;        // almacena el valor que permite calibrar el sensor
  float valorCalibracion2;
  float valorCalibracion3;
  float temperatura;
  bool errorEnTemperatura = false;

  //Nuevos
  int ID = 1475025633;  // provisional, ID del dispositivo de sensores tipo 2
  String topic;
  String unidades;
  float lecturaFisica;
  JsonObject objetoJson = jsonBufferSen.to<JsonObject>();
  float limites[6];  // min, minrojo, minamarillo, maxamarillo, maxrojo, max

  Preferences preferences;  // para guardar datos en la memoria NVR

  // Funciones
  bool inicializar(String param, uint8_t tipoDeSens);
  bool guardarDatosRecibidosDeJson(JsonObject jsonDoc);
  JsonObject genJsonParaActualizacionDatosCal();
  JsonObject genJsonParaActualizacionDatosLim();

  bool guardarLimites(float a, float b, float c, float d, float e, float f);
  bool guardarCalibracion(float a, float b, float c);

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// Funcion para inicializar el sensor
bool sensorData::inicializar(String param, uint8_t tipoDeSens){  // Funcion de inicio. Permite indicar un valor inicial de calibracion (opcional)
  parametro = param;
  tipoDeSensor = tipoDeSens;
  preferences.begin("sensor" + tipoDeSens);  // crear archivo para almacenar los datos de configuracion

  // Configurar valor de calibracion iniciales
  switch (tipoDeSensor) {
    case sensorTemp:
      // No requiere calibracion
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 10.0);
      limites[2] = preferences.getFloat("limites2", 15.0); limites[3] =  preferences.getFloat("limites3", 40.0); 
      limites[4] = preferences.getFloat("limites4", 45.0); limites[5] =  preferences.getFloat("limites5", 50.0);
      break;
    case sensorPH:
      valorCalibracion =  preferences.getFloat("valorCalibracion", 7);    //7;       
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", 2.554);    //2.554;
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", 0.18);    //0.18;
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 5.5);
      limites[2] = preferences.getFloat("limites2", 6.0); limites[3] =  preferences.getFloat("limites3", 8.0); 
      limites[4] = preferences.getFloat("limites4", 8.5); limites[5] =  preferences.getFloat("limites5", 14.0);
      break;
    case sensorConductividad:
      valorCalibracion =  preferences.getFloat("valorCalibracion", 133.42);        // 133.42;
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", 255.86);   // 255.86;
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", 857.39);   // 857.39;
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 5.0);
      limites[2] = preferences.getFloat("limites2", 10.0); limites[3] =  preferences.getFloat("limites3", 80.0); 
      limites[4] = preferences.getFloat("limites4", 90.0); limites[5] =  preferences.getFloat("limites5", 100.0);
      break;
    case sensorTurbidez:
      valorCalibracion =  preferences.getFloat("valorCalibracion", -(1000/2.75) );  // -(1000/2.75);    // ver https://how2electronics.com/diy-turbidity-meter-using-turbidity-sensor-arduino/ ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", 1199);          //1199; // 1000
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", -4156.8);       //-4156.8;       //-4353.8;
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 0.0);
      limites[2] = preferences.getFloat("limites2", 0.0); limites[3] =  preferences.getFloat("limites3", 1.0); 
      limites[4] = preferences.getFloat("limites4", 5.0); limites[5] =  preferences.getFloat("limites5", 1100.0);
      break;
    case sensorTDS:
      valorCalibracion =  preferences.getFloat("valorCalibracion", 133.42);    //133.42;
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", 255.86);   //255.86;
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", 857.39);   //857.39;
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 0.0);
      limites[2] = preferences.getFloat("limites2", 0.0); limites[3] =  preferences.getFloat("limites3", 3.0); 
      limites[4] = preferences.getFloat("limites4", 5.0); limites[5] =  preferences.getFloat("limites5", 1100.0);
      break;

    // Hay que arreglar los datos del caudalimetro
    case sensorPres:
      valorCalibracion =  preferences.getFloat("valorCalibracion", 300);
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", -150);
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", 0);
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 0.0);
      limites[2] = preferences.getFloat("limites2", 0.0); limites[3] =  preferences.getFloat("limites3", 500); 
      limites[4] = preferences.getFloat("limites4", 1000); limites[5] =  preferences.getFloat("limites5", 1200);
      break;
    case sensorCaudal:
      valorCalibracion =  preferences.getFloat("valorCalibracion", 133.42);    //133.42;
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", 255.86);   //255.86;
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", 857.39);   //857.39;
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 0.0);
      limites[2] = preferences.getFloat("limites2", 0.0); limites[3] =  preferences.getFloat("limites3", 3.0); 
      limites[4] = preferences.getFloat("limites4", 5.0); limites[5] =  preferences.getFloat("limites5", 1100.0);
      break;
    default: return 0;
  }

  return 1; // Retornar true una vez se completo la inicializacion
}

// Funcion para almacenar los datos que se recibieron del archivo Json (sin uso aun)
bool sensorData::guardarDatosRecibidosDeJson(JsonObject jsonDoc){
  ID =                    jsonDoc["ID"];                                // (falta indicar ID)
  topic =    (const char*)jsonDoc["topic"];
  tipoDeSensor =          jsonDoc["tipoDeSensor"];
  lecturaDigital =        jsonDoc["lecturaDigital"];
  voltaje =               jsonDoc["voltaje"];
  corriente =             jsonDoc["corriente"];
  usaADC =                jsonDoc["usaADC"];
  voltajeMaximoADC =      jsonDoc["voltajeMaximoADC"];
  pinDeConexion =         jsonDoc["pinDeConexion"];
  valorCalibracion =      jsonDoc["valorCalibracion"];
  valorCalibracion2 =     jsonDoc["valorCalibracion2"];
  valorCalibracion3 =     jsonDoc["valorCalibracion3"]; 
  temperatura =           jsonDoc["temperatura"];
  errorEnTemperatura =    jsonDoc["errorEnTemperatura"];
  lecturaFisica =         jsonDoc["lecturaFisica"];
  unidades = (const char*)jsonDoc["unidades"];              // (const char*) permite que compile cuando es string, ver: https://arduinojson.org/v6/error/ambiguous-overload-for-operator-equal/ 

  return true;
}

// Funcion para generar el json que permita actualizar los datos en los dipositivo 2 y 3 (calibracion)
JsonObject sensorData::genJsonParaActualizacionDatosCal(){
  objetoJson["ID"] =                  ID;
  objetoJson["topic"] =               "Calib";            // El topico indica que es para calibracion
  objetoJson["tipoDeSensor"] =        tipoDeSensor;
  objetoJson["usaADC"] =              usaADC;
  objetoJson["voltajeMaximoADC"] =    voltajeMaximoADC;
  objetoJson["pinDeConexion"] =       pinDeConexion;
  objetoJson["valorCalibracion"] =    valorCalibracion;
  objetoJson["valorCalibracion2"] =   valorCalibracion2;
  objetoJson["valorCalibracion3"] =   valorCalibracion3;
  objetoJson["errorEnTemperatura"] =  errorEnTemperatura;

  return objetoJson; // Retorna el json resultante al finalizar
}

// Funcion para generar el json que permita actualizar los datos en los dipositivo 2 y 3 (limites)
JsonObject sensorData::genJsonParaActualizacionDatosLim(){
  JsonObject json = jsonBufferSen.to<JsonObject>();  // crear objeto json para almacenar datos

  json["ID"] =                  ID;
  json["topic"] =               "limit";            // El topico indica que es para definir limites
  json["tipoDeSensor"] =        tipoDeSensor;

  json["limites0"] = limites[0];  json["limites1"] = limites[1];
  json["limites2"] = limites[2];  json["limites3"] = limites[3];   
  json["limites4"] = limites[4];  json["limites5"] = limites[5];    

  return json;
}

// Funcion para almacenar los nuevos limites en la momoria permanente
bool sensorData::guardarLimites(float a, float b, float c, float d, float e, float f){
  
  // Guardar datos en NVS:
  preferences.putFloat("limites0", a); preferences.putFloat("limites1", b);
  preferences.putFloat("limites2", c); preferences.putFloat("limites3", d); 
  preferences.putFloat("limites4", e); preferences.putFloat("limites5", f);

  // Actualizar datos de la clase:
  limites[0] = a; limites[1] =  b;
  limites[2] = c; limites[3] =  d; 
  limites[4] = e; limites[5] =  f;

  return true;
}

// Funcion para almacenar los nuevos valores de calibracion en la momoria permanente
bool sensorData::guardarCalibracion(float a, float b, float c){
  
  // Guardar datos en NVS:
  preferences.putFloat("valorCalibracion",  a);
  preferences.putFloat("valorCalibracion2", b);
  preferences.putFloat("valorCalibracion3", c);
  
  // Actualizar datos de la clase:
  valorCalibracion  = a;
  valorCalibracion2 = b;
  valorCalibracion3 = c;

  return true;
}


#endif // final del if



