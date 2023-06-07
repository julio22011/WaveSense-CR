
/* En este archivo se definen las caracteristicas que tiene un objeto de
 * de clase sensor. Permite trabajar con los sensores de temperatura,
 * conductividad, turbidez.
*/


#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif


#if !defined(claseSensorIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseSensorIncluida

// Nombre numerico para cada tipo de sensor
#define sensorTemp          1
#define sensorPH            2
#define sensorConductividad 3
#define sensorTurbidez      4
#define sensorTDS           5
#define sensorPres          6
#define sensorCaudal        7

//*****************************************************************************************************************
#include "requeridoPorClaseSensor.h"
#include "painlessMesh.h"             // para obtener el ID del nodo

class sensor{
  private:

  // Variables privadas
  int lecturaDigital = -1;
  float corriente = -1;              // si es -1, es un sensor que no utiliza corriente
  
  // Crear objeto json para los mensajes
  JsonObject mensaje = jsonBuffer.to<JsonObject>();

  public:

  // Variables
  int ID_Dispositivo;
  uint8_t tipoDeSensor;              // Permite saber que tipo de sensor es
  String parametro;                  // Ejemplo, turbidez
  bool usaADC;
  float voltaje = -1;                // si es -1, es un sensor que no utiliza voltaje
  float lectura = -1;
  int valorMaximoADC = 65535;        // 4095 para ADC de 12 bit
  float voltajeMaximoADC = 5.0;      // Voltaje al que corresponde la mayor lectura del ADC
  int pinDeConexion;
  float valorCalibracion = 0;        // almacena el valor que permite calibrar el sensor
  float valorCalibracion2 = 0;
  float valorCalibracion3 = 0;
  float temperatura;
  bool errorEnTemperatura = false;

  long int milisAntesQ;              // para registrar el tiempo t1                               
  long int millisDespQ;              // para registrar el tiempo t2  deltaT = t2-t1 ====> Densidad de pulsos = (cuentaCaudal/deltaT)

  uint8_t index18b20 = 0;            // Indice del sensor de 18b20, util cuando son varios sensores iguales

  float limites[6];  // min, minrojo, minamarillo, maxamarillo, maxrojo, max

  // Objetos: instancia a las clases OneWire y DallasTemperature
  //OneWire oneWireObjeto(4);
  //DallasTemperature *sensorDS18B20(); //&oneWireObjeto

  // Objetos: Instancias de los ADCs
  Adafruit_ADS1115 *ads;  /* Version de 16-bit */

  // Objeto para guardar los datos de configuracion:
  Preferences preferences;  // para guardar datos en la memoria NVR

  // Funciones
  bool inicializar(int id, String param, uint8_t tipoDeSens, int pinDeConex, bool ADC, Adafruit_ADS1115 *adsUti);
  bool definirValoresCalibracion(float valCalibracion, float valCalibracion2,float valCalibracion3);         // cambiado por guardar calibracion
  bool cambiarValorMaximoADC(int valorNuevo);
  bool cambiarVoltajeMaximoADC(float valorNuevo);
  int devolverLecturaDigital();
  float devolverVoltaje();
  float devolverCorriente();           // para sensores de 4-20 mA
  float devolverParametroFisico();
  String devolverUnidadesFisicas();
  JsonObject obtenerArchivoJson();

  bool guardarLimites(float a, float b, float c, float d, float e, float f);
  bool guardarCalibracion(float a, float b, float c);
  bool actualizarDatosPorJsonCal(DynamicJsonDocument objetoJson);
  bool actualizarDatosPorJsonLim(DynamicJsonDocument objetoJson);

  // Funciones de calculo
  float square(float x);
  float calcularPH();
  float calcularConductividad();
  float calcularTurbidez();
  float calcularTDS();
  float calcularPresion();
  float calcularCaudal();
  float determinarTemperatura();

}; // fin de la clase


// Funciones de la calse
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Funcion para inicializar el sensor
bool sensor::inicializar(int id, String param,uint8_t tipoDeSens, int pinDeConex, bool ADC, Adafruit_ADS1115 *adsUti = NULL){  // Funcion de inicio. Permite indicar un valor inicial de calibracion (opcional)
  ID_Dispositivo = id;
  parametro = param;
  tipoDeSensor = tipoDeSens;
  pinDeConexion = pinDeConex;
  usaADC = ADC;

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
      valorCalibracion =  preferences.getFloat("valorCalibracion", 7.5);   // Valor de factor K en L/min
      valorCalibracion2 = preferences.getFloat("valorCalibracion2", 0);    //  
      valorCalibracion3 = preferences.getFloat("valorCalibracion3", 0);    //
      limites[0] = preferences.getFloat("limites0", 0.0);  limites[1] =  preferences.getFloat("limites1", 0.0);
      limites[2] = preferences.getFloat("limites2", 0.0); limites[3] =  preferences.getFloat("limites3", 3.0); 
      limites[4] = preferences.getFloat("limites4", 5.0); limites[5] =  preferences.getFloat("limites5", 1100.0);
      break;
    default: return 0;
  }

  if(tipoDeSensor == sensorTemp){
    // Iniciar el bus OneWire del sensor de temperatura
    setup18B20();
  } else if(tipoDeSensor == sensorCaudal){
    // Configurar interrupciones del caudalimetro
    pinMode(pinDeConex, INPUT);
    attachInterrupt(pinDeConex, ISR_Cuadal, RISING);   // digitalPinToInterrupt(pinDeConex)
    milisAntesQ = millis();
    // detachInterrupt(GPIOPin); // para quitar una interrupcion
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

// Funcion para almacenar los nuevos limites en la momoria permanente (idea: usar en funcion de actualizar datos por Json)
bool sensor::guardarLimites(float a, float b, float c, float d, float e, float f){

  // Guardar datos en NVS:
  preferences.putFloat("limites0", a); preferences.putFloat("limites1", b);
  preferences.putFloat("limites2", c); preferences.putFloat("limites3", d); 
  preferences.putFloat("limites4", e); preferences.putFloat("limites5", f);
  Serial.println("Datos de limites guardados correctamente.");
  
  // Actualizar datos de la clase:
  limites[0] = a; limites[1] =  b;
  limites[2] = c; limites[3] =  d; 
  limites[4] = e; limites[5] =  f;

  return true;
}

// Funcion para almacenar los nuevos valores de calibracion en la momoria permanente
bool sensor::guardarCalibracion(float a, float b, float c){
  
  // Guardar datos en NVS:
  preferences.putFloat("valorCalibracion",  a);
  preferences.putFloat("valorCalibracion2", b);
  preferences.putFloat("valorCalibracion3", c);
  Serial.println("Datos de calibracion guardados correctamente.");
  
  // Actualizar datos de la clase:
  valorCalibracion  = a;
  valorCalibracion2 = b;
  valorCalibracion3 = c;

  return true;
}


bool sensor::cambiarValorMaximoADC(int valorNuevo){
  valorMaximoADC = valorNuevo;
  return 1;
}

int sensor::devolverLecturaDigital(){
  // Dependiendo del tipo de sensor, se devuelve un valor

  if(usaADC){
    // Determinar las lectura por medio de los ADC externos
    lecturaDigital = ads->readADC_SingleEnded(pinDeConexion);
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

      // Falta agregar caudalimetro
      case sensorPres:
        lecturaDigital = analogRead(pinDeConexion);
        break;
      case sensorCaudal:
        lecturaDigital = 12;  // agregar funcion para recuperar caudal mediante los pulsos    // analogRead(pinDeConexion);
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
    return ads->computeVolts(devolverLecturaDigital());               // Usa la libreria para convertir la lectura digital a un valor de voltaje
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
        lectura = determinarTemperatura();
        return lectura;
        break;
      case sensorPH:
        lectura = calcularPH();
        return lectura;
        break;
      case sensorConductividad:
        lectura = calcularConductividad();
        return lectura;
        break;
      case sensorTurbidez:
        lectura = calcularTurbidez();
        return lectura;
        break;
      case sensorTDS:
        lectura = calcularTDS();
        return lectura;
        break;

      // Nuevos sensores
      case sensorPres:
        lectura = calcularPresion();
        return lectura;
        break;
      case sensorCaudal:
        lectura = calcularCaudal();
        return lectura;
        break;
      default: return -1;  // retorna un -1 como indicativo de error
    }
}

String sensor::devolverUnidadesFisicas(){
  // Permite indicar las unidades en que estan los parametros fisico
  switch (tipoDeSensor) {
      case sensorTemp:
        return "C";
        break;
      case sensorPH:
        return "(0-14)";  // Not units
        break;
      case sensorConductividad:
        return "uS/cm";
        break;
      case sensorTurbidez:
        return "NTU";
        break;
      case sensorTDS:
        return "PPM";  // ppm = mg/L
        break;

      // Nuevos sensores
      case sensorPres:
        return "kPa";
        break;
      case sensorCaudal:
        return "L/min";
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
  // 7 + (valorCalibracion-devolverVoltaje())/valorCalibracion2;   // Ecuacion de calculo:  //7 + (2.5-voltajePH)/valorCalibracionPH
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  determinarTemperatura();
  return  valorCalibracion + (valorCalibracion2 - voltaje)/valorCalibracion3;  // ecuacion = A + (B-volt)/C
}

float sensor::calcularConductividad(){  
  // Funcion que devuelve el valor de conductividad
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  determinarTemperatura();
  if (temperatura == 0) temperatura = 25.0;  // si se desconoce la temperatura, se define como 25

  float compensationCoefficient = 1.0 + 0.02*(temperatura-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  float compensationVolatge = voltaje/compensationCoefficient;  //temperature compensation
  float conductividad = (valorCalibracion*compensationVolatge*compensationVolatge*compensationVolatge - valorCalibracion2*compensationVolatge*compensationVolatge + valorCalibracion3*compensationVolatge);  // sin 1000 da en uS/cm      /1000; // mS/cm
  return conductividad;   // Ecuacion de calculo, ver https://www.lenntech.com/applications/ultrapure/conductivity/water-conductivity.htm  o https://randomnerdtutorials.com/arduino-tds-water-quality-sensor/
}

float sensor::calcularTurbidez(){
  // Funcion que devuelve el valor de turbidez
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  // ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
  float ntu = valorCalibracion*voltaje + valorCalibracion2;  // similar a map con ecuacion lineal
  //if(ntu < 0) return 0; // retorna 0 si el valor es negativo
  return ntu;

  //return valorCalibracion*square(voltaje+1.3)+valorCalibracion2*(voltaje+1.3)+valorCalibracion3;   // Ecuacion de calculo, ver https://ecuarobot.com/2021/03/24/medicion-de-la-turbidez-del-agua-para-determinar-la-calidad-del-agua-mediante-arduino-y-el-sensor-de-turbidez/
}                                                                                                 

float sensor::calcularTDS(){    // ppm = mg/L
  // Estima los PPM de la solucion sensor la conductividad
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  determinarTemperatura();
  if (temperatura == 0) temperatura = 25.0;  // si se desconoce la temperatura, se define como 25

  float compensationCoefficient = 1.0 + 0.02*(temperatura-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  float compensationVolatge = voltaje/compensationCoefficient;  //temperature compensation
  float tdsValue=(valorCalibracion*compensationVolatge*compensationVolatge*compensationVolatge - valorCalibracion2*compensationVolatge*compensationVolatge + valorCalibracion3*compensationVolatge)*0.5; //convert voltage value to tds value
  return tdsValue; // Ecuacion de calculo, ver https://wiki.keyestudio.com/KS0429_keyestudio_TDS_Meter_V1.0 0 de Adafruit: https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244?gclid=Cj0KCQjwyOuYBhCGARIsAIdGQRMgMxuTeanS11vlUkTR3qVN1pbd9SH3OY62YQM74d27H5HHReZX5bsaAg-xEALw_wcB
}

float sensor::calcularPresion(){
  // Funcion que devuelve el valor de la presion
  voltaje = devolverVoltaje();
  corriente = devolverCorriente();
  float presion = valorCalibracion*voltaje + valorCalibracion2;  // similar a map con ecuacion lineal
  return presion;

  //return valorCalibracion*square(voltaje+1.3)+valorCalibracion2*(voltaje+1.3)+valorCalibracion3;   // Ecuacion de calculo, ver https://ecuarobot.com/2021/03/24/medicion-de-la-turbidez-del-agua-para-determinar-la-calidad-del-agua-mediante-arduino-y-el-sensor-de-turbidez/
}

float sensor::calcularCaudal(){
  // Funcion que devuelve el valor de caudal
  millisDespQ = millis();
  float dp = (cuentaCuadal*1000)/(millisDespQ-milisAntesQ);       // dp = N. pulsos/deltaT
  float caudal = valorCalibracion*dp + valorCalibracion2;  // similar a map con ecuacion lineal

  #if defined(depSensorCaudal)
    Serial.printf("El caudal es: %f. Pulsos: %i \n", caudal, cuentaCuadal);
  #endif
  
  // Resetear valores
  cuentaCuadal = 0;
  milisAntesQ = millis();

  return caudal;
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

////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------

// Funciones para procesar los archivos tipo Json
JsonObject sensor::obtenerArchivoJson(){
  // Esta funcion permite generar un archivo Json con todos los datos del sensor
  mensaje["ID"] =                 ID_Dispositivo;         //1475025633;                              // (falta indicar ID)
  mensaje["topic"] =              "sensor";
  mensaje["tipoDeSensor"] =       tipoDeSensor;
  mensaje["lecturaDigital"] =     devolverLecturaDigital();
  mensaje["voltaje"] =            devolverVoltaje();
  mensaje["corriente"] =          devolverCorriente();
  mensaje["usaADC"] =             usaADC;
  mensaje["voltajeMaximoADC"] =   voltajeMaximoADC;
  mensaje["pinDeConexion"] =      pinDeConexion;
  mensaje["valorCalibracion"] =   valorCalibracion;
  mensaje["valorCalibracion2"] =  valorCalibracion2;
  mensaje["valorCalibracion3"] =  valorCalibracion3;
  mensaje["temperatura"] =        determinarTemperatura(); 
  mensaje["errorEnTemperatura"] = errorEnTemperatura;
  mensaje["lecturaFisica"] =      devolverParametroFisico();
  mensaje["unidades"] =           devolverUnidadesFisicas();

  return mensaje; // devuelve el archivo json con la informacion
}

// Esta funcion permite cambiar los datos del objeto sensor al recibir el archivo Json por mesh (calibracion)
bool sensor::actualizarDatosPorJsonCal(DynamicJsonDocument objetoJson){
  tipoDeSensor =       objetoJson["tipoDeSensor"];
  usaADC =             objetoJson["usaADC"];
  voltajeMaximoADC =   objetoJson["voltajeMaximoADC"];
  pinDeConexion =      objetoJson["pinDeConexion"];
  valorCalibracion =   objetoJson["valorCalibracion"];
  valorCalibracion2 =  objetoJson["valorCalibracion2"];
  valorCalibracion3 =  objetoJson["valorCalibracion3"];
  errorEnTemperatura = objetoJson["errorEnTemperatura"];

  return 1; // Retorna 1 al finalizar
}

// Esta funcion permite cambiar los datos del objeto sensor al recibir el archivo Json por mesh (limites)
 bool sensor::actualizarDatosPorJsonLim(DynamicJsonDocument objetoJson){
    return guardarLimites(
      objetoJson["limites0"],   //float a, 
      objetoJson["limites1"],   //float b, 
      objetoJson["limites2"],   //float c, 
      objetoJson["limites3"],   //float d, 
      objetoJson["limites4"],   //float e, 
      objetoJson["limites5"] ); //float f  
    
    //return 1;
 }

/* Da problemas, mejor usar en el ino
// Funcion que permite obtener el chip ID del ESP32
// #include <ESP32.h>
int sensor::getChipID() {
  uint8_t chip_id[6];
  ESP.getEfuseMac(chip_id);

  char buffer[13];
  sprintf(buffer, "%02X%02X%02X%02X%02X%02X", chip_id[0], chip_id[1], chip_id[2], chip_id[3], chip_id[4], chip_id[5]);
  int chip_id_int = strtol(buffer, NULL, 16);

  Serial.println("ID del chip en formato entero: " + String(chip_id_int));

  return chip_id_int;
}
*/

#endif // finaliza if