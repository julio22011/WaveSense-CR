/* ***********************************************************************************************
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
ArchivoPrincipal
  Este es el acrchivo principal del programa, a partir del cual se compila el firmware.
  Este es para el ESP32 de los sensores.
Notas:
  -V
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*********************************************************************************************** */

// Librerias
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_ADS1X15.h>
#include <analogWrite.h>

#include <esp_now.h>
#include <WiFi.h>  // original de esp32


// Variables para almacenar voltajes de los sensores:
int16_t adc0, adc1, adc2, adc3;
double volts0, volts1, volts2, volts3;

#include "funcionesGSM.h"
#include "WebOTA.h"
#include "Logo2.h"
#include "cabeceraRTOS_S.h"

#define I2C_SDA 22
#define I2C_SCL 21


/*
int i2c_master_port = 0;
i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = I2C_SDA,         // select GPIO specific to your project
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_io_num = I2C_SCL,         // select GPIO specific to your project
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = I2C_MASTER_FREQ_HZ,  // select frequency specific to your project
    // .clk_flags = 0,          //!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here.
};
*/
/////////////////////////////////////////////////////
//#define pinConductividad 32
//#define pinpH 27
#define LED_PIN 0     // MCP23XXX pin LED is attached to
#define pinBateria 32
#define pinBotones 36

bool intercambio = true;

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
Adafruit_MCP23X17 mcp;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);

  //esp_err_ti2c_set_pin(i2c_port_ti2c_num, I2C_SDA, I2C_SCL, true, true, I2C_MODE_MASTER);

  // Inicializacion del ADC
  if (!ads.begin(0x48)) {
    Serial.println("Failed to initialize ADS.");
    //while (1);
  }
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  configDePines();
  analogWrite(16,50);

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  mcp.digitalWrite(8, LOW);
  mcp.digitalWrite(9, LOW);
  mcp.digitalWrite(10, LOW);
  
  //
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,8);
  display.println(F("Conexion WiFi a:"));
  display.println(F("KONOHA..."));
  display.display();
  //iniciarOTA();  // desactivado para evitar problemas con ESP-now
  
  iniciarESPNOW(5000); // inicia la tarea de ESP-Now para enviar datos de los sensores

  /* Lo aiguiente prueba el gsm
  display.clearDisplay();
  display.println(F("Configurando GSM"));
  display.display();
  setupModemGSM();
  enviarMensajeGSM("Prueba de mensaje");
  */

  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  /*
  testdrawline();      // Draw many lines

  testdrawrect();      // Draw rectangles (outlines)

  testfillrect();      // Draw rectangles (filled)

  testdrawcircle();    // Draw circles (outlines)

  testfillcircle();    // Draw circles (filled)

  testdrawroundrect(); // Draw rounded rectangles (outlines)

  testfillroundrect(); // Draw rounded rectangles (filled)

  testdrawtriangle();  // Draw triangles (outlines)

  testfilltriangle();  // Draw triangles (filled)

  testdrawchar();      // Draw characters of the default font

  testdrawstyles();    // Draw 'stylized' characters

  testscrolltext();    // Draw scrolling text

  testdrawbitmap();    // Draw a small bitmap image

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
  */
}

void loop() {
  //ADChacerMediciones();
  medicionesPantalla1();
  delay(200);
  pruebaDeLedsMCP();
  //cicloPruebaMCP();

  int lecturaBotones = analogRead(pinBotones);
  if (lecturaBotones > 3500){
    medicionesPantalla2();
    delay(3000);
  }
  if (lecturaBotones > 200){
    intercambio = !intercambio;
    delay(3000);
  }
  Serial.println(lecturaBotones);
  controlMosfet();
}

void configDePines(){

  //pinMode(pinConductividad, INPUT);
  //pinMode(pinpH, INPUT);
  pinMode(pinBateria, INPUT);
  pinMode(pinBotones, INPUT);
  pinMode(16, OUTPUT);


  // MCP23017
  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C(0x20)) {      // )x20 e la dirreccion
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }
  // configure pin for output
  mcp.pinMode(LED_PIN, OUTPUT);

  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);

  mcp.digitalWrite(8, HIGH);
  mcp.digitalWrite(9, HIGH);
  mcp.digitalWrite(10, HIGH);
}

void controlMosfet(){
  analogWrite(16,200);
  delay(500);
  analogWrite(16,50);
  delay(800);
}

//int16_t adc0, adc1, adc2, adc3;
//double volts0, volts1, volts2, volts3;
void ADChacerMediciones() {
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  //Serial.println(volts2);
/*
  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");
*/
}

void pruebaDeLedsMCP(){
  ////
  mcp.digitalWrite(9, HIGH);
  delay(100);
  mcp.digitalWrite(9, LOW);
  delay(800);
}

void cicloPruebaMCP(){
  for(int i = 200; i>0; i--){
    mcp.digitalWrite(LED_PIN, HIGH);
    delay(4);
    //delayMicroseconds(10);
    mcp.digitalWrite(LED_PIN, LOW);
    delay(4);
    //delayMicroseconds(10);
  }
}


#include <Fonts/FreeSerif9pt7b.h> // para agregar tipos de fuentes
void medicionesPantalla1(){
  display.clearDisplay();

  if(intercambio){
    //display.setFont(&FreeSerif9pt7b);
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,8);             // Start at top-left corner
    display.println(F("Turbidez:"));
    //**
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.print(volts0); //medicionTurbidez()
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.println(F(" volts")); // NTU
    //**********************************************************************
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.println(); // espacio
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    /////////////////////
    display.println(F("pH:"));
    //**
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.print(volts2); //medicionpH()
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.println(F(" volts"));
  } else {
    //display.setFont(&FreeSerif9pt7b);
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,8);             // Start at top-left corner
    display.println(F("Conductividad:"));
    //**
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.print(volts1);
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.println(F(" volts"));
    //******************************************************************************
    display.println(); // espacio
    display.setTextSize(1); 
    display.println(F("Presion:"));
    //**
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.print(volts3);
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.println(F(" volts"));
  }

//////////////
  display.display();
  //delay(500);
}

void medicionesPantalla2(){
  display.clearDisplay();

  //display.setFont(&FreeSerif9pt7b);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,8);             // Start at top-left corner
  display.println(F("Bateria:"));
  //**
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  float voltBateria = analogRead(pinBateria)*(3.3/4096)*2;
  display.print(voltBateria);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.println(F(" Volts"));
  /////////////////
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.println(); // espacio
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.println(F("Porcentje:"));
  //**
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  float porcentajeBateria = (1-((4.2-voltBateria)/1.2))*100;
  display.println(porcentajeBateria);

//////////////
  display.display();
  //delay(500);
}


// variables necesarias
unsigned long int avgValue;  // Variable para almacenar el valor promedio del sensor de pH
float b;
float buf[10],temp;            // buffer temporal del pH
float valorCalibracionPH = 0.18;

float medicionpH(){
  for(int i=0;i<10;i++)       // Obtiene 10 muestras para suavisar el resultado final del valor del pH
  {
    ADChacerMediciones(); 
    buf[i]= volts1;
    delay(10); // antes 10
  }
  for(int i=0;i<9;i++)        //ordene los valores registrados desde el más pequeño al mayor
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  float avgValue=0;
  for(int i=2;i<8;i++)                      // toma el promedio de los 6 valores del medio
    avgValue+=buf[i];

  // lecturas de pH
  float voltajePH = (float)avgValue*(3.4/4095)/6;  // divido entre 6 porque hace un promedio de 6 lecturas
  float lecturapH = 7 + (2.5-voltajePH)/valorCalibracionPH;
  return lecturapH;
}

double medicionTurbidez(){
   // lecturas de tubidez
  //double voltajeTurbidez = volts0*(3.3/4095); // determina el voltaje del sensor analógico
  double lecturaTurbidez = calc_NTU(volts0); // determina el valor en NTU mediante una función que retorna el resultado
  return lecturaTurbidez;
}

double calc_NTU(double volt) {  // función para calcular la tubidez del agua, debe ingresarse el valor de voltaje
  double NTU_val;
  NTU_val = -(1120.4*volt*volt)+(5742.3*volt)-4352.9; // ecuación que relaciona el voltaje del sensor con la tubidez NTU
  return NTU_val;
} //end calc_NTU

void testdrawline() {
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testfillrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    LogoWaveSense, LOGO_WIDTH, LOGO_HEIGHT, 1); //  logo_bmp
  display.display();
  delay(1000);
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}
