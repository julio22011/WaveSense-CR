//**************************************************
//  En este archivo contine lo requerido para controlar 
//  la los convertidores de analogico a digital por I2C.
//**************************************************

//=====================================================================
//           Parametros generales de los chips
//=====================================================================

#define ADS1_ADDRESS 0x48
//#define ADS2_ADDRESS 0x48 // direccion aun por definir

//=====================================================================
//           Funciones de configuracion
//=====================================================================

// Inicializacion de los ADCs
void setupAnalogToDigitalConverter(){
  //Wire.begin(I2C_SDA, I2C_SCL); // configurar pines personalizados de I2C
  if (!ads.begin(ADS1_ADDRESS)) {
    Serial.println("Failed to initialize ADS1.");
    //while (1);
  }
//  if (!ads2.begin(ADS2_ADDRESS)) {
//    Serial.println("Failed to initialize ADS1.");
//    //while (1);
//  }

}

//=====================================================================
//           Funciones de lectura
//=====================================================================

void ADChacerMediciones() {
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);
}
