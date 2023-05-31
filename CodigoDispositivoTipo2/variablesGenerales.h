

/************************************************************************
Varibles generales para el dispostivo tipo 2 y tipo 3:
  En este archivo se definen algunas de las variables que requiere el
  dispostitivo para su funcionamiento y configuracion.
*************************************************************************/

#include "settings.h"  // ajustes del dispositivo 

//=====================================================================
//           Librerias
//=====================================================================
// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

// Incluir las librerias utilizadas
//-----------------------------
#include "painlessMesh.h"

// Incluir las clases requeridas
//-----------------------------
#include "clases/claseFiltros.h" // Clase para menejar los filtros
#include "clases/claseSensor.h"  // Clase para manejar sensores
#include "clases/claseUI_OLED.h" // ya incluye otras librarias requeridas


//=====================================================================
//           Variables de trabajo
//=====================================================================
DynamicJsonDocument jsonBufferTh(1024); // Crear instancia para los documentos JSON


//=====================================================================
//           Objetos:  Crear los objetos del programa
//=====================================================================

// Para la red mesh:
Scheduler userScheduler; // Para la controlar las tareas
painlessMesh  mesh;

// Para los filtros:
filtro filtro1, filtro2, filtro3; // crear objetos tipo filtro

filtro todosLosFiltros[] = {filtro1, filtro2, filtro3};  // crea un array de filtros
int cantidadDeFiltros = sizeof(todosLosFiltros)/sizeof(filtro);

// Para los sensores
sensor sTemperatura, sPH, sConductividad, sTurbidez, sTDS, sPresion, sCaudal;
sensor todosLosSensores[] = {sTemperatura, sPH, sConductividad, sTurbidez, sTDS, sPresion, sCaudal}; // crear vector con todos los sensores
int cantidadDeSensores = sizeof(todosLosSensores)/sizeof(sensor);

// Para la ui de la pantalla:
UI_OLED ui;          // crear objeto de ui
menu menuPrincipal;
menu menuSecundario;
menu menuModoConex;
botones botones;

//=====================================================================
//           FreeRTOS
//=====================================================================
bool aplicandoRetro = false;    // variable para evitar iniciar dos veces las misma tarea
bool yendoPosServicio = false;  // variable para evitar iniciar dos veces las misma tarea


//=====================================================================
//      Archivos adicionales del programa
//=====================================================================

// Incluir otros archivos del codigo que manipulan los objetos
//-----------------------------
#include "multitareaFreeRTOS.h"
#include "funcionesDeRedMesh.h"

#include "libreriasCreadas/firebaseServices.h"
