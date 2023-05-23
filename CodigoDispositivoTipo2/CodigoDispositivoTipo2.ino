/**********************************************************************************
Codigo de programcion para los dispositivos de tipo 2 y 3.
***********************************************************************************/

// Archivo de configuracion
#include "variablesGenerales.h"

// Incluir las librerias utilizadas
//-----------------------------
#include "painlessMesh.h"

// Incluir las clases requeridas
//-----------------------------
#include "clases/claseFiltros.h" // Clase para menejar los filtros
#include "clases/claseSensor.h"  // Clase para manejar sensores
#include "clases/claseUI_OLED.h" // ya incluye otras librarias requeridas

// Crear los objetos del programa
//-----------------------------

// Para la red mesh:
Scheduler userScheduler; // Para la controlar las tareas
painlessMesh  mesh;

// Para los filtros:
filtro filtro1, filtro2, filtro3; // crear objetos tipo filtro

filtro todosLosFiltros[] = {filtro1, filtro2, filtro3};  // crea un array de filtros
int cantidadDeFiltros = sizeof(todosLosFiltros)/sizeof(filtro);

// Para los sensores
sensor sTemperatura, sPH, sConductividad, sTurbidez, sTDS, sPresion;
sensor todosLosSensores[] = {sTemperatura, sPH, sConductividad, sTurbidez, sTDS, sPresion}; // crear vector con todos los sensores
int cantidadDeSensores = sizeof(todosLosSensores)/sizeof(sensor);

// Para la ui de la pantalla:
UI_OLED ui;          // crear objeto de ui
menu menuPrincipal;
menu menuSecundario;
botones botones;

// Incluir otros archivos del codigo que manipulan los objetos
//-----------------------------
#include "multitareaFreeRTOS.h"
#include "funcionesDeRedMesh.h"

long int millisAntes = millis();  // varaible para guardar el tiempo en un momento de

void setup() {
  Serial.begin(115200); // inicia el puerto serial a 115200 baudios

  // Prueba de motor conectado al transistor
  pinMode(pinTransistor, OUTPUT);
  digitalWrite(pinTransistor, LOW);

  // Inicializacion de objetos
  setupRedMesh();        // configura la red mesh
  crearUI();             // Configura la ui de la pantalla (debe ejecutarse en otra tarea por aparte de la red mesh)
  setupDeSensores();     // configura los sensores

  // Prueba de buzzer
  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, HIGH);
  vTaskDelay(pdMS_TO_TICKS(200));
  digitalWrite(pinBuzzer, LOW);

  // Agregar al gestor de tareas la tarea de retrolavados
  userScheduler.addTask( taskEjecucionDeRetrolavadoInterno);     // agregar al gestor la tarea que ejecuta los retrolavados
  //taskEjecucionDeRetrolavado.enable();                  // comenzar a ejecutar la tarea

  iniciarUI(3000);
  //iniciarTareaMesh(16000);
  iniciarTareaEnviarDatos(8000); // (da error iniciar si no se pone bastante memoria)
}

void loop() {
  mesh.update(); // mantiene activa la red mesh
  //ui.update();
  //mostrarEstadoDeRetroEnUI();
}

// Configura los filtros
void setupFiltros(){
  
  // Filtro 1
  todosLosFiltros[0].caracteristicas(1,f1_1,f1_2,rele1_1, pinBuzzer);
  if (!todosLosFiltros[0].inicializar(true)){                     // Enviar true como parametro para activar la logica negativa en los reles
    Serial.println("Error al iniciar el filtro 1");
  }

  // Filtro 2
  todosLosFiltros[1].caracteristicas(2,f2_1,f2_2,rele1_2, pinBuzzer);
  if (!todosLosFiltros[1].inicializar(true)){                     // Enviar true como parametro para activar la logica negativa en los reles
    Serial.println("Error al iniciar el filtro 2");
  }

  // Filtro 3
  todosLosFiltros[2].caracteristicas(3,f3_1,f3_2,rele2_1, pinBuzzer);
  if (!todosLosFiltros[2].inicializar(true)){                     // Enviar true como parametro para activar la logica negativa en los reles
    Serial.println("Error al iniciar el filtro 3");
  }
}


// Crea la ui que se mustra en la pantalla
void crearUI(){
  // Asociar la pantalla a la UI y inicializar:
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  ui.asociarPantalla(display);
  ui.setupPantallaOled(I2C_SDA, I2C_SCL); // iniciar la ui junto con la pantalla

  // Hacer menu principal:
  String titulosMenuPrincipal[] = {
    "Hacer retrolavado",
    "Ir a pos. servicio",
    "Mediciones sensores",
    "Apagar alarma",
    "Apagar red mesh",
    "Configuraciones"};

  // Determinar la cantidad de elementos:
  int numDeOpciones = (sizeof(titulosMenuPrincipal)/sizeof(titulosMenuPrincipal[0]));

  // Configurar el menu:
  menuPrincipal.configurarMenu(0, numDeOpciones, "Menu Principal", titulosMenuPrincipal);
  //menuPrincipal.imprimirOpcionesEnSerial(); // para depuracion

  // Para los menus secundarios:
  String titulosMenuSecundario[] = {
    "Reinicio",
    "Tipo de conexion",
    "Mostrar voltajes",
    "Informacion"};
  int numDeOpcionesSec = (sizeof(titulosMenuSecundario)/sizeof(titulosMenuSecundario[0])); // determinar la cantidad de elementos
  menuSecundario.configurarMenu(1, numDeOpcionesSec, "Menu 2", titulosMenuSecundario);
  //menuSecundario.imprimirOpcionesEnSerial();  // funcion de depuracion

  // Asociar los menus creados a la ui:
  menu todosLosMenus[] = {menuPrincipal,menuSecundario}; // Vector de los menus
  ui.asociarMenu(2, todosLosMenus);
  //ui.imprimirTitulosDeMenusSerial(); // funcion de depuracion

  // Configurar botones:
  botones.iniciar(pinDeLosBotones, tipoBotonesDisp, limitesDeLect, pinTransistor); // int pin = 36, uint8_t tipo = 0, int *limitesDeLectura = NULL
  ui.asociarBotones(botones);

  // Mostrar menu:
  //ui.mostrarMenuEnOLED(menuPrincipal);  // para probar, se debe cambiar por ui.update(); en la tarea que la ejecuta
  ui.mostrarMensaje("Bienvenido");        // Prueba de enviar un mensaje
  vTaskDelay(pdMS_TO_TICKS(1000));        // Esperar para no borrar el mensaje y poder verlo
}

void setupDeSensores(){
  // Inciar los sensores:
  IDdelDispositivo = mesh.getNodeId();                                                                       // obtener el chipid
  todosLosSensores[0].inicializar(IDdelDispositivo, "Temp", sensorTemp, pin_Temp, false);                    // false, no utiliza ADC
  todosLosSensores[1].inicializar(IDdelDispositivo, "pH", sensorPH, pinADC_pH, true, &ads1);
  todosLosSensores[2].inicializar(IDdelDispositivo, "Cond", sensorConductividad, pinADC_Cond, true, &ads1);
  todosLosSensores[3].inicializar(IDdelDispositivo, "Turb", sensorTurbidez, pinADC_Turb, true, &ads1);
  todosLosSensores[4].inicializar(IDdelDispositivo, "TDS", sensorTDS, pinADC_TDS, true, &ads1);              // usa el mismo sensor de conductividad
  
  todosLosSensores[5].inicializar(IDdelDispositivo, "Pres", sensorPres, pinADC_Pres, true, &ads1);           // Sensor de presion
}

bool callBackEjecutarAccionExterna(int menuActual, int opcionActual){
  //ui.menuActual = 1;
  //ui.cambioPendiente = true; // le indica al ui que se ha hecho un cambio, no es necesario si se presiona un boton
  if(menuActual == 0 && opcionActual == 5){
    ui.menuActual = 1;
  }
  else if(menuActual == 0 && opcionActual == 0){  // opcion: "Hacer retrolavado"
    todosLosFiltros[0].horarioInt[3] = 10;  // configurar tiempo de retrolavado (segundos)
    todosLosFiltros[0].horarioInt[4] = 7;   // configurar tiempo de succion y enjuague (segundos)
    if(!aplicandoRetro) iniciarTareaEjecucionDeRetrolavadoInterno(2000); // tarea de freRTOS
    //taskEjecucionDeRetrolavadoInterno.enable();
    //filtro1.aplicarRetrolavado(5,3); // para probar
  }
  else if(menuActual == 0 && opcionActual == 1){  // opcion: "Ir a pos. de servicio"
    if(!yendoPosServicio) iniciarTareaIrPosServicio(2000);  // inicia tarea de ir a pos. de servicio
  }
  else if(menuActual == 0 && opcionActual == 2){  // Opcion: "mediciones sensores"
    int cantSensores = sizeof(todosLosSensores)/sizeof(sensor); // Determina cuantos sensores son, -1 para ignorar el de TDS
    while(botones.botonPresionado() != '4'){
      // Mostrar constantemente las lecturas hasta que se presione el boton 4
      ui.mostrarLecturasSensores(todosLosSensores, cantSensores);
      vTaskDelay(pdMS_TO_TICKS(400)); // esperar un poco para no saturar la tarea
    }
  }
  else if(menuActual == 0 && opcionActual == 3){  // menu 1, opcion 4
    digitalWrite(pinBuzzer, LOW);
  }
  else if(menuActual == 1 && opcionActual == 0){  // menu 2, opcion 1
    ESP.restart();
  }
  else if(menuActual == 1 && opcionActual == 1){  // menu 2, opcion 2
    int cantSensores = sizeof(todosLosSensores)/sizeof(sensor); // Determina cuantos sensores son
    while(botones.botonPresionado() != '4'){
      for(int i = 0; i < cantSensores; i++){
        Serial.print(todosLosSensores[i].parametro + ":");
        Serial.print(todosLosSensores[i].voltaje);
        Serial.print(" ");
      }
      Serial.println();

      ui.mostrarVoltajesSensores(todosLosSensores, cantSensores); // muestra en la pantalla los voltajes
      vTaskDelay(pdMS_TO_TICKS(2000)); // esperar un poco para no saturar la tarea
    }
  }
}
