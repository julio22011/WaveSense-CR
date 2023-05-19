
/* ***********************************************************************************************
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
ArchivoPrincipal
  Este es el acrchivo principal del programa, a partir del cual se compila el firmware.
  Este es para el ESP32 principal del dispositivo.
Notas:
  -Video Tutorial para LVGL 8: https://youtu.be/IPCvQ4o_WP8
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*********************************************************************************************** */
#include "lvgl.h" // para evitar error con ui.h
// Otras partes del codigo:
#include "ui.h"               // archivo de la ui
#include "MyDisplaySetup.h"   // posee las configuraciones para la pantalla


// Partes de LVGL trasladadas
lv_obj_t * label; // etiqueta donde se registra lectura
static lv_obj_t * meter;
lv_meter_indicator_t * indic;

// Librerias y variables generales
#include "variablesYlibrerias.h"
#include "cabeceraRTOS.h"     // Archivo para la gestion de las tareas
#include "ExpansorPuertasInit.h"


// Ejemplos LVGL
#include "graficoEjemplo.h"
#include "screenLVGLmedidores.h"


// Events de LVGL
#include "eventsLVGL.h"


void setup()
{
   Serial.begin(115200);

   setupPantalla();     // inicia la pantalla
   setupMCP();          // inicia MCP23017

   ui_init(); // iniciar interfaz
   agregarIconos(); // agrega los iconos faltantes


  // Iniciar tareas generales
   //iniciarVibracion(1000);
   iniciarBotones(1000);


   // para pruebas
   activarMouseBLE = true;
   //iniciarMouseBLE(5000);
   iniciarUART_ESP32_2(5000); 
   
   //lv_example_chart_2();
   lv_example_chart_5();
}

void loop()
{
   lv_timer_handler(); /* let the GUI do its work */
   vTaskDelay( pdMS_TO_TICKS(5) );
}


///////////////////////////////////////////
// funcion para agregar los iconos de la ui
void agregarIconos(){
  lv_label_set_text(ui_Label17, LV_SYMBOL_CLOSE);    //"S\n"
  lv_label_set_text(ui_Label15, LV_SYMBOL_REFRESH);  //"R\n"
  lv_label_set_text(ui_Label14, LV_SYMBOL_POWER);    //"P\n"

  lv_label_set_text(ui_Label3, LV_SYMBOL_SETTINGS);  //"A"
  lv_label_set_text(ui_Label4, LV_SYMBOL_POWER);     //"P"

  // Bateria
  lv_label_set_text(ui_Label18, LV_SYMBOL_BATTERY_3);        // "bat"> FULL, 3, 2, 1, EMPTY
}
