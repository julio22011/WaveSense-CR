
/* En este archivo se crea la clase que permitira manejar los 4 botones
 * del dispositivo.
*/

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

  // Boton derecha:
  int limiteSupDer;
  int limiteInfDer;
  // Boton abajo:
  int limiteSupAba;
  int limiteInfAba;
  // Boton arriba:
  int limiteSupArr;
  int limiteInfArr;
  // Boton izquierda:
  int limiteSupIzq;
  int limiteInfIzq;

  // Funciones
  //*************************
  bool iniciar(int pin, uint8_t tipo, int *limitesDeLectura);
  char botonPresionado();

};

// Ingresa a la configuracion los limites de lectura
bool botones::iniciar(int pin = 36, uint8_t tipo = 0, int *limitesDeLectura = NULL){  // limites: no boton, e inferior y superior de 1,2,3 y4

  pinBotones = pin;   // Indica pin donde estan conectados los botones
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

  return true;
}


char botones::botonPresionado(){
  //
  lecturaBotones = analogRead(pinBotones);   // Almacena la lectura analogica de los botones
  char botonPress;                           // Almacena el boton presionado

  if (lecturaBotones > lmiteNoBoton){
    if (tipoBotones == 0){
      if (lecturaBotones>limiteInfIzq && lecturaBotones<limiteSupIzq)       botonPress = '1';
      else if (lecturaBotones>limiteInfDer && lecturaBotones<limiteSupDer)  botonPress = '2';
      else if (lecturaBotones>limiteInfArr && lecturaBotones<limiteSupArr)  botonPress = '3';
      else if (lecturaBotones>limiteInfAba && lecturaBotones<limiteSupAba)  botonPress = '4';
    } else if (tipoBotones == 1) {
      if (lecturaBotones>limiteInfIzq && lecturaBotones<limiteSupIzq)       botonPress = 'i';
      else if (lecturaBotones>limiteInfDer && lecturaBotones<limiteSupDer)  botonPress = 'd';
      else if (lecturaBotones>limiteInfArr && lecturaBotones<limiteSupArr)  botonPress = 'A';
      else if (lecturaBotones>limiteInfAba && lecturaBotones<limiteSupAba)  botonPress = 'a';
    }
    return botonPress;
  }
  return ' '; // retorna vacio si no se presiona nignun boton
}



















