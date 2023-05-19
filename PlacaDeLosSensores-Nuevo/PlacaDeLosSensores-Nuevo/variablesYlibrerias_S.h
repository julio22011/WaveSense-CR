
//**************************************************
//  En este archivo se incorporan las librerias requeridas
//  y se crean la mayor parte de las variables globales del
//  codigo.
//**************************************************

//=====================================================================
//           Librerias utilizadas
//=====================================================================

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_ADS1X15.h>
#include <analogWrite.h>

#include <esp_now.h>
#include <WiFi.h>  // original de esp32

//=====================================================================
//           Clases desarrolladas
//=====================================================================

#include "clases/claseFiltros.h" // Clase para el menejo de los filtros
#include "clases/claseUI_OLED.h" // clase para la UI de la pantalla OLED

//=====================================================================
//           Definicion de pines
//=====================================================================
// Pines de I2C
//-----------------------------
#define I2C_SDA 22
#define I2C_SCL 21

// Pines de sensores digitales
//----------------------------
#define pinCaudalimetro   1    // caudalimetro
#define pinSensorTemp     1    // s. de temperatura

// Pines de sensores en los ADC
//----------------------------
#define pinTurbidez A0       // Sensor de turbidez
#define pinConductividad A1  // Sensor de conductividad
#define pinPH A2             // Sensor de pH
#define pinPresion A3        // Sensor de presion
#define pinVibracion B0      // Sensor de vibracion

// Pines para funciones especiales
//----------------------------
#define LED_PIN 0     // MCP23XXX pin LED is attached to
#define pinBateria 32
#define pinBotones 36


//=====================================================================
//           Variables globales
//=====================================================================

// Creacion de objetos para pantalla y ADCs
//---------------------------
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
Adafruit_MCP23X17 mcp;

// Variables para almacenar voltajes de los sensores:
//---------------------------
int16_t adc0, adc1, adc2, adc3;
double volts0, volts1, volts2, volts3;

// Variables para detectar botones
//---------------------------
int lecturaBotones = 0;
int8_t botonPresionado = 0; // posibles valores 1,2,3,4 en el mismo orden de los botones. 0 para ningun boton

// Valores limite para distinguir entre cada boton:
const int blim1 = 3900; // inferior 1
const int blim2 = 4095; // superior 1
const int blim3 = 2700; // inferior 2
const int blim4 = 3000; // superior 2
const int blim5 = 1600; // inferior 3
const int blim6 = 2000; // superior 3
const int blim7 = 600;  // inferior 4
const int blim8 = 1000; // superior 4


//=====================================================================
//           Inclusion de otros archivos
//=====================================================================
// Inclusion de archivos principales del codigo:
#include "pantallaOLED.h"
#include "analogToDigitalConverter.h"
#include "cabeceraRTOS_S.h"
#include "ampliadoresDePuertas.h"


// Otros archivos especiales
//#include "funcionesGSM.h"
//#include "WebOTA.h"
//#include "Logo2.h"
