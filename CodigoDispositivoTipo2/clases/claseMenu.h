/* En este archivo se crea la clase que permite crear objetos de tipo menu para la ui
 * de la pantalla OLED
*/

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif


#if !defined(claseMenuIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseMenuIncluida

// Crear una estrucura para almacenar los datos de cada menu que se muestra en pantalla
class menu{
  // Estructura que almacena los datos de un menu

  public:
  // Variables
  int numMenu;
  String titulo = "Indefinido";
  int numOpc;                        // cantidad de opciones
  String *opciones = NULL;           // el maximo de opciones por menu sera 10, aunque se puede modificasr
  int opcionSelecionada = 0;         // opcion que se encuentra selecionada 

  //Funciones
  bool configurarMenu(int nMenu, int nOpc, String title, String *opc, int opcionSelec);
  bool imprimirOpcionesEnSerial();
  bool aumentarOpcionSelecionada(int nuevaOpcion);
  bool dismimuirOpcionSelecionada(int nuevaOpcion);
};


// Funcion para definir parametros iniciales de un menu
bool menu::configurarMenu(int nMenu, int nOpc, String title, String *opc, int opcionSelec = 0){
  numMenu = nMenu;
  titulo = title;
  numOpc = nOpc;
  opcionSelecionada = opcionSelec;

  // Lo siguiete guarda las opciones del menu
  opciones = new String[numOpc];
  for (int i = 0; i < numOpc; i++)
  {
    opciones[i] = opc[i];
  }
  return 1;
}

// Funcion para enviar por el serial las opciones del menu
bool menu::imprimirOpcionesEnSerial(){
  //int limite = (sizeof(opciones)/sizeof(opciones[0])); // determinar la cantidad de elementos
  for (int i = 0; i < numOpc; i++)
  {
    Serial.println(opciones[i]);
  }
  return 1;
}

// Funcion para aumentar el numero de opcion que se encuentra seleccionada del menu
bool menu::aumentarOpcionSelecionada(int aumento){
  if ((opcionSelecionada+aumento) < 6 && (opcionSelecionada+aumento) < numOpc){
    opcionSelecionada += aumento;
    return 1;
  } else if ((opcionSelecionada+aumento) == (numOpc)){
    opcionSelecionada = 0;
    return 1;
  }
  return 0;
}

// Funcion para dismunuir el numero de opcion que se encuentra seleccionada del menu
bool menu::dismimuirOpcionSelecionada(int disminucion){
  // Aumentar en una posicion si es posible
  if ((opcionSelecionada-disminucion) >= 0){
    opcionSelecionada -= disminucion;
    return 1;
  } else if ((opcionSelecionada-disminucion) == -1){
    opcionSelecionada = numOpc - 1;
    return 1;
  }
  return 0;
}

#endif // fin del if
