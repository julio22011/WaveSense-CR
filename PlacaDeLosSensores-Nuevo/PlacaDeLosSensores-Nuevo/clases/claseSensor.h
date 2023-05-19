
/* En este archivo se definen las caracteristicas que tiene un objeto de
 * de clase sensor. Permite trabajar con los sensores de temperatura,
 * conductividad, turbidez.
*/

// Nombre para cada tipo de sensor
#define sensorTemp 1
#define sensorPH 2
#define sensorConductividad 3
#define sensorTurbidez 4
#define sensorTDS 5

// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
DynamicJsonDocument jsonBuffer(1024); // Crear instancia para los documentos JSON

// Direcciones y libreria de los ADC
#include <Adafruit_ADS1X15.h>
#define ADS1_ADDRESS 0x48
//#define ADS2_ADDRESS 0x48 // direccion aun por definir

// Librerias externas para el sensor de temperatura 18b20 de Dallas
#include <OneWire.h>
#include <DallasTemperature.h>

// Funciones externas
// *********************
Adafruit_ADS1115 ads1;  // Objeto del ADC1
Adafruit_ADS1115 ads2;  // Objeto del ADC2
void setupADS(){
  if (!ads1.begin(ADS1_ADDRESS)) {Serial.println("Failed to initialize ADS1.");}
}

// Objetos: instancia a OneWire y DallasTemperature
OneWire oneWireObjeto(pin_Temp);                // Crea conexion OneWire con el pin
DallasTemperature sensorDS18B20(&oneWireObjeto);
void setup18B20(){
  sensorDS18B20.begin();
}


//*****************************************************************************************************************
class sensor{
  private:

  // Variables privadas
  int lecturaDigital = -1;
  float voltaje = -1;                // si es -1, es un sensor que no utiliza voltaje
  float corriente = -1;              // si es -1, es un sensor que no utiliza corriente
  
  // Crear objeto json para los mensajes
  JsonObject mensaje = jsonBuffer.to<JsonObject>();

  public:

  // Variables
  uint8_t tipoDeSensor;              // Permite saber que tipo de sensor es
  bool usaADC;
  int valorMaximoADC = 65535;        // 4095 para ADC de 12 bit
  float voltajeMaximoADC = 5.0;      // Voltaje al que corresponde la mayor lectura del ADC
  int pinDeConexion;
  float valorCalibracion = 0;        // almacena el valor que permite calibrar el sensor
  float valorCalibracion2 = 0;
  float valorCalibracion3 = 0;
  float temperatura;
  bool errorEnTemperatura = false;

  uint8_t index18b20 = 0;            // Indice del sensor de 18b20, util cuando son varios sensores iguales

  // Objetos: instancia a las clases OneWire y DallasTemperature
  //OneWire oneWireObjeto(4);
  //DallasTemperature *sensorDS18B20(); //&oneWireObjeto

  // Objetos: Instancias de los ADCs
  Adafruit_ADS1115 *ads;  /* Version de 16-bit */

  // Funciones
  bool inicializar(uint8_t tipoDeSens, int pinDeConex, bool ADC, Adafruit_ADS1115 *adsUti);
  bool definirValoresCalibracion(float valCalibracion, float valCalibracion2,float valCalibracion3);
  bool cambiarValorMaximoADC(int valorNuevo);
  bool cambiarVoltajeMaximoADC(float valorNuevo);
  int devolverLecturaDigital();
  float devolverVoltaje();
  float devolverCorriente();         // para sensores de 4-20 mA
  float devolverParametroFisico();
  String devolverUnidadesFisicas();
  JsonObject obtenerArchivoJson();
  bool actualizarDatosPorJson(JsonObject objetoJson);

  // Funciones de calculo
  float square(float x);
  float calcularPH();
  float calcularConductividad();
  float calcularTurbidez();
  float calcularTDS();
  float determinarTemperatura();

}; // fin de la clase


// Funciones de la calse
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Funcion para inicializar el sensor
bool sensor::inicializar(uint8_t tipoDeSens, int pinDeConex, bool ADC, Adafruit_ADS1115 *adsUti = NULL){  // Funcion de inicio. Permite indicar un valor inicial de calibracion (opcional)
  tipoDeSensor = tipoDeSens;
  pinDeConexion = pinDeConex;
  usaADC = ADC;

  // Configurar valor de calibracion inicial
  switch (tipoDeSensor) {
    case sensorTemp:
      // No requiere calibracion
      break;
    case sensorPH:
      valorCalibracion = 73.07;
      break;
    case sensorConductividad:
      valorCalibracion = 0;    //************************ Falta definir
      break;
    case sensorTurbidez:
      valorCalibracion = -1120.4;    // ver https://how2electronics.com/diy-turbidity-meter-using-turbidity-sensor-arduino/ ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
      valorCalibracion2 = 5742.3;
      valorCalibracion3 = -4353.8;
      break;
    case sensorTDS:
      valorCalibracion = 0; //*************************  falta definir
    default: return 0;
  }

  if(tipoDeSensor == sensorTemp){
    // Iniciar el bus OneWire del sensor de temperatura
    setup18B20();
  }

  if (usaADC){
    // Iniciar ADC
    voltajeMaximoADC = 5.0;   // Indica que este ADC es de 5 voltios
    ads = adsUti;
    setupADS();               // Ejecuta automaticamente funcion que inicia el ADC
  } else{
    voltajeMaximoADC = 3.3;
    valorMaximoADC = 4095; // Si no se usa el ADC se asigna los ADCs de 12 bit del ESP32
  }
  return 1; // Retornar true una vez se completo la inicializacion
}

bool sensor::cambiarVoltajeMaximoADC(float valorNuevo){
  voltajeMaximoADC = valorNuevo;
  return 1; // retorna verdadero
}

bool sensor::definirValoresCalibracion(float valCalibracion = 0, float valCalibracion2 = 0,float valCalibracion3 = 0){
  // Esta funcion permite calibrar los sensores
  valorCalibracion = valCalibracion;
  valorCalibracion2 = valCalibracion2;
  valorCalibracion3 = valCalibracion3;
}

bool sensor::cambiarValorMaximoADC(int valorNuevo){
  valorMaximoADC = valorNuevo;
  return 1;
}

int sensor::devolverLecturaDigital(){
  // Dependiendo del tipo de sensor, se devuelve un valor

  if(usaADC){
    // Determinar las lectura por medio de los ADC externos
    lecturaDigital = ads->readADC_SingleEnded(pinDeConexion); // El valor del adc es en 16 bit, por eso se debe convertir a entero
    return lecturaDigital;
  } else if(!usaADC){
    // Determinar valor por medio los ADC internos del ESP32
    switch (tipoDeSensor) {
      case sensorTemp:
        lecturaDigital = determinarTemperatura();
        break;
      case sensorPH:
        lecturaDigital = analogRead(pinDeConexion);
        break;
      case sensorConductividad:
        lecturaDigital = analogRead(pinDeConexion);
        break;
      case sensorTurbidez:
        lecturaDigital = analogRead(pinDeConexion);
        break;
      case sensorTDS:
        lecturaDigital = analogRead(pinDeConexion);
        break;
      default: return -1;  // retorna un -1 como indicativo de error
    }
    return lecturaDigital;  // retorna el valor correspondiente
  }
  return -1; // si no entra al if retorna un -1 como indicativo de error
}

float sensor::devolverVoltaje(){
  // Devuelve el valor de voltaje medido
  if (tipoDeSensor == sensorTemp) return 0;                           // Retorna 0 ya que este tipo de sensor no usa voltaje
  if(usaADC){
    return ads->computeVolts(devolverLecturaDigital());
  } else{
    return (voltajeMaximoADC/valorMaximoADC)*devolverLecturaDigital();  // Calcula el valor de voltaje para lo sensores analogicos de voltaje
  }
}

float sensor::devolverCorriente(){
  // Retorna un valor equivalente en mA de las lecturas
  if (tipoDeSensor == sensorTemp) return 0;                           // Retorna 0 ya que este tipo de sensor no usa corriente
  return 4+devolverLecturaDigital()*(4-20);                           
}

float sensor::devolverParametroFisico(){
  // Devuelve el parametro fisico en las unidades correspondientes
  switch (tipoDeSensor) {
      case sensorTemp:
        return determinarTemperatura();
        break;
      case sensorPH:
        return calcularPH();
        break;
      case sensorConductividad:
        return calcularConductividad();
        break;
      case sensorTurbidez:
        return calcularTurbidez();
        break;
      case sensorTDS:
        return calcularTDS();
      default: return -1;  // retorna un -1 como indicativo de error
    }
}

String sensor::devolverUnidadesFisicas(){
  // Permite indicar las unidades en que estan los parametros fisico
  switch (tipoDeSensor) {
      case sensorTemp:
        return "°C";
        break;
      case sensorPH:
        return "(0-14)";  // Not units
        break;
      case sensorConductividad:
        return "uS/m";
        break;
      case sensorTurbidez:
        return "NTU";
        break;
      case sensorTDS:
        return "PPM";
        break;
      default: return "ErrorUnits";  // retorna un -1 como indicativo de error
    }
}

// Funciones de calculo de la clase
//************************************************************************


// Funcion general que permite calcular numero al cuadrado
float sensor::square(float x){
  return x*x;
}

/////////////
float sensor::calcularPH(){
  // Funcion que devuelve el valor del pH
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  determinarTemperatura();
  return ( valorMaximoADC-devolverLecturaDigital() )/valorCalibracion;   // Ecuacion de calculo (1023 - analogRead(pHpin)) / 73.07
}

float sensor::calcularConductividad(){
  // Funcion que devuelve el valor de conductividad
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  determinarTemperatura();
  return 2*1;   // Ecuacion de calculo, ver https://randomnerdtutorials.com/arduino-tds-water-quality-sensor/
}

float sensor::calcularTurbidez(){
  // Funcion que devuelve el valor de turbidez
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  // ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
  return valorCalibracion*square(voltaje)+valorCalibracion2*voltaje+valorCalibracion3;   // Ecuacion de calculo
}

float sensor::calcularTDS(){
  // Estima los PPM de la solucion sensor la conductividad
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  determinarTemperatura();
  return 2*1; // Ecuacion de calculo, ver https://wiki.keyestudio.com/KS0429_keyestudio_TDS_Meter_V1.0
}

float sensor::determinarTemperatura(){
  if (!errorEnTemperatura){
    sensorDS18B20.requestTemperatures();
    temperatura = sensorDS18B20.getTempCByIndex(index18b20);
    if (temperatura == -127.0){
      temperatura = 25.0;  // si da una temperatura mal, devuelve 25 
      errorEnTemperatura = true; // desactiva la medicion de temperatura y activa variable de error
    }
  } // fin de if
  return temperatura;
}

//////////////////////////////////////////
// Funciones para procesar los archivos tipo Json
JsonObject sensor::obtenerArchivoJson(){
  // Esta funcion permite generar un archivo Json con todos los datos del sensor
  mensaje["topic"] = "sensor";
  mensaje["tipoDeSensor"] = tipoDeSensor;
  mensaje["lecturaDigital"] = devolverLecturaDigital();
  mensaje["voltaje"] = devolverVoltaje();
  mensaje["corriente"] = devolverCorriente();
  mensaje["UsaADC"] = usaADC;                           // pegunta y respuesta
  mensaje["VoltajeMaximoADC"] = voltajeMaximoADC;
  mensaje["pinDeConexion"] = pinDeConexion;
  mensaje["valorCalibracion"] = valorCalibracion;
  mensaje["valorCalibracion2"] = valorCalibracion2;
  mensaje["valorCalibracion3"] = valorCalibracion3; 
  mensaje["temperatura"] = determinarTemperatura(); 
  mensaje["errorEnTemperatura"] = errorEnTemperatura;   // pegunta y respuesta
  mensaje["lecturaFisica"] = devolverParametroFisico();
  mensaje["Unidades"] = devolverUnidadesFisicas();

  return mensaje; // devuel el archivo json con la informacion
}


bool sensor::actualizarDatosPorJson(JsonObject objetoJson){
  // Esta funcion permite cambiar los datos del objeto sensor al recibir el archivo Json por mesh
  tipoDeSensor = objetoJson["tipoDeSensor"];
  usaADC = objetoJson["usaADC"];
  voltajeMaximoADC = objetoJson["voltajeMaximoADC"];
  pinDeConexion = objetoJson["pinDeConexion"];
  valorCalibracion = objetoJson["valorCalibracion"];
  valorCalibracion2 = objetoJson["valorCalibracion2"];
  valorCalibracion3 = objetoJson["valorCalibracion3"];
  errorEnTemperatura = objetoJson["errorEnTemperatura"];

  return 1; // Retorna 1 al finalizar
}

