
/* En este archivo se encuentra la calse que permite
 * crear una interfaz de usuario en la pantalla OLED
*/

//=====================================================================
//           Parametros generales de la pantalla
//=====================================================================

// Definicion del tamaño de la pantalla:
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Parametros de la pantalla:
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//=====================================================================


#include "claseMenu.h" // se requiere la clase menu para que esta clase funcione
#include <Adafruit_SSD1306.h> // se requiere la clase de la pantalla

class UI_OLED {
  //
  private:

  public:
  
  // Varibles
  Adafruit_SSD1306 display; // permite almacenar la clase de la pantalla asociada
  uint16_t menuActual = 0;
  int numeroMenus = 0;                      // guarda la cantidad de menus existentes
  menu *menusGuardados = NULL;              // Puntero hacia los objetos de tipo menu

  // Funciones
  bool mostrarMenuEnOLED(menu menuPorMostrar);
  bool asociarPantalla(Adafruit_SSD1306 displayPorAsociar);
  bool asociarMenu(int numMenus, menu *menusPorAsociar);
  bool imprimirTitulosDeMenusSerial();
  bool setupPantallaOled(int I2C_SDA, int I2C_SCL);
  bool mostrarLecturasSensores(sensor *sensores); // String *nombreSensores, float * lecturas
  bool update();
};


// Funciones de la clase
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool UI_OLED::asociarMenu(int numMenus, menu *menusPorAsociar){
  // Permite agregar los menus al objeto
  numeroMenus = numMenus;
  menusGuardados = new menu[numMenus];
  for (int i = 0; i < numMenus; i++)
  {
    menusGuardados[i] = menusPorAsociar[i]; // asocia cada uno de los menus
  }
  return 1;
}

bool UI_OLED::asociarPantalla(Adafruit_SSD1306 displayPorAsociar){
  // Esta funcion vincula el UI con la pantalla OLED
  display = displayPorAsociar;
}

bool UI_OLED::imprimirTitulosDeMenusSerial(){
  for (int i = 0; i < numeroMenus; i++){
    Serial.println(menusGuardados[i].titulo);
  }
  return 1;
}

// Funcion para iniciar la pantalla
bool UI_OLED::setupPantallaOled(int I2C_SDA, int I2C_SCL){
  Wire.begin(I2C_SDA, I2C_SCL);  // iniciar I2C con los pines definidos
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    //for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  vTaskDelay(pdMS_TO_TICKS(2000)); // Pause for 2 seconds
  display.clearDisplay();
  
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
}


bool UI_OLED::mostrarMenuEnOLED(menu menuPorMostrar){
  // Funcion para desplagar un menu en la pantalla
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,8);
  display.println(menuPorMostrar.titulo); // mostrar el titulo
  display.setCursor(0,16);
  for (int i = 0; i < menuPorMostrar.numOpc; i++)
  {
    if(i==menuPorMostrar.opcionSelecionada){ // verifica cual es la opcion en pantalla y le pone una marca
      display.println("* " + menuPorMostrar.opciones[i]);
    } else{
      display.println("  " + menuPorMostrar.opciones[i]);
    }
  }
  display.display();
}

bool UI_OLED::mostrarLecturasSensores(sensor *sensores){ // String *nombreSensores, float * lecturas
  // Muestra las lecturas de los sensores 
  display.clearDisplay();             // Borra el buffer de la pantalla
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,8);

  int cantSensores = sizeof(sensores)/sizeof(sensor); // Determina cuantos sensores son
  for(int i = 0; i < 5; i++){
    display.println(sensores[0].devolverVoltaje());  // probando si devuelve valor
  }
  display.display();
}

bool UI_OLED::update(){
  //
  // if algo cambia, actualizar pantalla
}

