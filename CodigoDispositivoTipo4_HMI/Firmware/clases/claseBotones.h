#include "esp32-hal-gpio.h"

/* En este archivo se crea la clase que permitira manejar los 4 botones
 * del dispositivo.
*/

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif


#if !defined(claseBotonesIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseBotonesIncluida

class botones{
  //
  private:
  uint8_t tipoBotones; // para indicar el tipo de botones, 0 para tipo 1,2,3,4 y  1 para derecha, abajo, arriba, izquierda

  public:
  // Variables
  //*************************
  int lecturaBotones;
  int lmiteNoBoton;
  int pinBotones;
  int pinMotorVibracion;
  bool activarVibracion = false;

  int pinAnalogX;
  int pinAnalogY;
  //int lmiteNoJoystick;// limitesDeLecturaJoy: lmiteNoJoystick, limiteXup, limiteXdown, limiteYup, limiteYdown
  int limiteXup;
  int limiteXdown;
  int limiteYup;
  int limiteYdown;

  // Boton derecha:
  int limiteSupDer; int limiteInfDer;
  // Boton abajo:
  int limiteSupAba; int limiteInfAba;
  // Boton arriba:
  int limiteSupArr; int limiteInfArr;
  // Boton izquierda:
  int limiteSupIzq; int limiteInfIzq;

  // Valores para el driver de mouse
  bool arribaPresionado = false;
  bool abajoPresionado = false;
  bool izquierdaPresionado = false;
  bool derechaPresionado = false;

  uint16_t posX = 50;
  uint16_t posY = 50;
  uint16_t resolutionX = 480;
  uint16_t resolutionY = 320;
  uint16_t velocidadMouse = 1;  // incremento de pixeles con que se desplaza el mouse

  // Funciones
  //*************************
  bool iniciar(int pinBtn, uint8_t tipo, int *limitesDeLectura, int pinMotorVib, int pinJoyX, int pinJoyY, int *limitesDeLecturaJoy);
  char botonPresionado();
  char joystickDirectionX();
  char joystickDirectionY();
};

// Ingresa a la configuracion los limites de lectura
bool botones::iniciar(int pinBtn = 36, uint8_t tipo = 0, int *limitesDeLectura = NULL, int pinMotorVib = NULL, int pinJoyX = 39, int pinJoyY = 34, int *limitesDeLecturaJoy = NULL){  // limites: no boton, e inferior y superior de 1,2,3 y4

  pinMode(pinBtn, INPUT); // poner el pin como entrada

  pinBotones = pinBtn;   // Indica pin donde estan conectados los botones
  tipoBotones = tipo; // Configura los botoenes segun su tipo                  // = {100,3900,4095,2700,3000,1600,2000,600,1000}

  // Cuando no esta presionado ningun boton:
  lmiteNoBoton = limitesDeLectura[0];
  
  // Boton derecha:
  limiteSupDer = limitesDeLectura[1];
  limiteInfDer = limitesDeLectura[2];
  // Boton abajo:
  limiteSupAba = limitesDeLectura[3];
  limiteInfAba = limitesDeLectura[4];
  // Boton arriba:
  limiteSupArr = limitesDeLectura[5];
  limiteInfArr = limitesDeLectura[6];
  // Boton izquierda:
  limiteSupIzq = limitesDeLectura[7];
  limiteInfIzq = limitesDeLectura[8];

  if(pinMotorVib != NULL){
    pinMotorVibracion = pinMotorVib;
    pinMode(pinMotorVibracion, OUTPUT);
    activarVibracion = true;
  }

  // Ajustar joystick si se definen los botones tipo 1
  if (tipo == 1){
    //lmiteNoJoystick = limitesDeLecturaJoy[0];   // limitesDeLecturaJoy: lmiteNoJoystick, limiteXup, limiteXdown, limiteYup, limiteYdown
    pinMode(pinJoyX, INPUT); // poner el pin como entrada
    pinMode(pinJoyY, INPUT); // poner el pin como entrada
    pinAnalogX = pinJoyX;    // guardar en la clase el pin
    pinAnalogY = pinJoyY;    // guardar en la clase el pin

    limiteXup =       limitesDeLecturaJoy[0]; 
    limiteXdown =     limitesDeLecturaJoy[1];
    limiteYup =       limitesDeLecturaJoy[2]; 
    limiteYdown =     limitesDeLecturaJoy[3]; 
  }

  return true;
}

// Funcion para detectar el boton presionado
char botones::botonPresionado(){
  
  lecturaBotones = analogRead(pinBotones);   // Almacena la lectura analogica de los botones
  char botonPress;                           // Almacena el boton presionado

  if (lecturaBotones > lmiteNoBoton){
    if (tipoBotones == 0){
      if (lecturaBotones>=limiteInfDer && lecturaBotones<=limiteSupDer)       {botonPress = '1';}
      else if (lecturaBotones>=limiteInfAba && lecturaBotones<=limiteSupAba)  {botonPress = '2';}
      else if (lecturaBotones>=limiteInfArr && lecturaBotones<=limiteSupArr)  {botonPress = '3';}
      else if (lecturaBotones>=limiteInfIzq && lecturaBotones<=limiteSupIzq)  {botonPress = '4';}
    } else if (tipoBotones == 1) {
      if (lecturaBotones>=limiteInfDer && lecturaBotones<=limiteSupDer)       {botonPress = 'd'; derechaPresionado = true;}
      else if (lecturaBotones>=limiteInfAba && lecturaBotones<=limiteSupAba)  {botonPress = 'a'; abajoPresionado = true;}
      else if (lecturaBotones>=limiteInfArr && lecturaBotones<=limiteSupArr)  {botonPress = 'A'; arribaPresionado = true;}
      else if (lecturaBotones>=limiteInfIzq && lecturaBotones<=limiteSupIzq)  {botonPress = 'i'; izquierdaPresionado = true;}
    }

    #if defined(depuracionBotones)
    Serial.print("Boton presionado: "); Serial.print(botonPress); Serial.print(" ");
    Serial.println(lecturaBotones); // para depuracion
    #endif

    if(activarVibracion) {                      
      digitalWrite(pinMotorVibracion, HIGH);
      vTaskDelay(pdMS_TO_TICKS(200));
      digitalWrite(pinMotorVibracion, LOW);
    }

    return botonPress;

  } else{
    arribaPresionado = false;
    abajoPresionado = false;
    izquierdaPresionado = false;
    derechaPresionado = false;
    return '0'; // retorna 0 si no se presiona nignun boton
  }
}

// Funcion para detectar la posicion del joystick cuando se selecciona los botones tipo 1
char botones::joystickDirectionX(){
  //
  int lecturaX = analogRead(pinAnalogX);   // Almacena la lectura analogica del eje X del joystick
  char directionX;                           // Almacena el boton presionado

  uint16_t velocidadMouseX;

  if(lecturaX >= limiteXup){
    directionX = 'd';
    velocidadMouseX = (5*(lecturaX)/4095)*velocidadMouse; // (ajustar la velocidad segun la lectura)
    posX += velocidadMouseX;
  } else if(lecturaX <= limiteXdown){
    directionX = 'i';
    velocidadMouseX = (5*(4095-lecturaX)/4095)*velocidadMouse; // (ajustar la velocidad segun la lectura)
    posX -= velocidadMouseX;
  } else {
    return '0';
  }

  #if defined(depuracionBotones)
    Serial.print("Direccion X del joystick: "); Serial.print(directionX); Serial.print(" ");
    Serial.println(lecturaX); // para depuracion
  #endif

  if(posX > resolutionX+50) posX = 0;  // para evitar que se salga de la pantalla
  else if(posX > resolutionX) posX = resolutionX;  // para evitar que se salga de la pantalla

  return directionX;
}

// Funcion para detectar la posicion del joystick cuando se selecciona los botones tipo 1
char botones::joystickDirectionY(){
  //
  int lecturaY = analogRead(pinAnalogY);   // Almacena la lectura analogica del eje X del joystick
  char directionY;                           // Almacena el boton presionado

  uint16_t velocidadMouseY;

  if(lecturaY >= limiteYup){
    directionY = 'a';
    velocidadMouseY = (5*(lecturaY)/4095)*velocidadMouse; // (ajustar la velocidad segun la lectura)
    posY += velocidadMouseY;
  } else if(lecturaY <= limiteYdown){
    directionY = 'A';
    velocidadMouseY = (5*(4095-lecturaY)/4095)*velocidadMouse; // (ajustar la velocidad segun la lectura)
    posY -= velocidadMouseY;
  } else {
    return '0';
  }

  #if defined(depuracionBotones)
    Serial.print("Direccion Y del joystick: "); Serial.print(directionY); Serial.print(" ");
    Serial.println(lecturaY); // para depuracion
  #endif

  if(posY > resolutionY+50) posY = 0;  // para evitar que se salga de la pantalla
  else if(posY > resolutionY) posY = resolutionY;  // para evitar que se salga de la pantalla

  return directionY;
}


#endif // finaliza el if


