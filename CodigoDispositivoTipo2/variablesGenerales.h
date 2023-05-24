

/************************************************************************
Varibles generales para el dispostivo tipo 2 y tipo 3:
  En este archivo se definen algunas de las variables que requiere el
  dispostitivo para su funcionamiento y configuracion.
*************************************************************************/

#include "settings.h"  // ajustes del dispositivo 


//=====================================================================
//           Variables de trabajo
//=====================================================================



//=====================================================================
//           FreeRTOS
//=====================================================================
bool aplicandoRetro = false;    // variable para evitar iniciar dos veces las misma tarea
bool yendoPosServicio = false;  // variable para evitar iniciar dos veces las misma tarea
