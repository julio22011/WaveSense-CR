
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

bool adsYaInicializado = false; // evita que se inicialicen mas de una vez los ads
void setupADS(){
  if(!adsYaInicializado){
    if (!ads1.begin(ADS1_ADDRESS)) {Serial.println("Failed to initialize ADS1.");}
    //if (!ads2.begin(ADS2_ADDRESS)) {Serial.println("Failed to initialize ADS2.");}  // ADS2 esta deshabilitado
    adsYaInicializado = true;
  }
}

// Objetos: instancia a OneWire y DallasTemperature
OneWire oneWireObjeto(pin_Temp);                // Crea conexion OneWire con el pin
DallasTemperature sensorDS18B20(&oneWireObjeto);
void setup18B20(){
  sensorDS18B20.begin();
}


// Funciones de interrupcion para el caudalimetro
//************************************************************************
volatile int cuentaCuadal = 0;              // para registrar los pulsos del cuadalimetro. Volatile hace que la variable este en ram

void IRAM_ATTR ISR_Cuadal() {   // con IRAM_ATTR se hace que la fun corra en la memoria ram
  cuentaCuadal++;
}

