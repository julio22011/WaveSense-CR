/* En este archivo se crea la clase que permite crear objetos de tipo menu para la ui
 * de la pantalla OLED
*/

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

