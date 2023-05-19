//*******************************************************
//  Este es el archivo principal del dispositivo que contiene
//  las placas para obtener las lecturas de los sensores
//*******************************************************

// Incluir el archivo general:
#include "variablesYlibrerias_S.h"


void setup() {
  Serial.begin(115200); // Iniciar comunicacion serial por usb

  // Realizar configuraciones
  //----------------------------------
  Wire.begin(I2C_SDA, I2C_SCL);       // configurar pines personalizados de I2C
  configDePines();                    // Configura pines del microcontrolador
  setupPantallaOled();                // Configura la pantalla
  setupAnalogToDigitalConverter();    // Configura los ADCs
  setupDeAmpliadoresDePuertas();

  //Iniciar tareas basicas
  //----------------------------------
  iniciarBotones(1024); // Tarea que detecta las pulsaciones en los botones
  iniciarUI(2048);      // Tarea que muestra la interfaz de la pantalla

  //Iniciar otras tareas
  //----------------------------------


  //Iniar tareas para pruebas
  //----------------------------------
  iniciarESPNOW(8192); // temporal
}


void loop() {
  // Vacio al usar multitasking
}


//=====================================================================
//           Funciones generales de configuracion del ESP32
//=====================================================================
void configDePines(){
  //pinMode(16, OUTPUT);
  pinMode(pinBateria, INPUT);
  pinMode(pinBotones, INPUT);
}
