
void procesoDeInicioDePantalla (void);
static void lv_ex_textarea_2(void); // posiblemente seria necesario otro archivos con estos

//#include "../interfaz_LVGL/imagenes_de_prueba_LVGL.c" // imagenes de prueba para usarlas con LVGL
//#include "../interfaz_LVGL/IMGoperativa.c" // imagenes de prueba para usarlas con LVGL
/*
#include "../interfaz_LVGL/estilos_lvgl.h" // aqui se crean los estilos de LVGL
#include "../interfaz_LVGL/creacion_objetos_lvgl.h" // aqui se crean los objetos de LVGL
#include "../interfaz_LVGL/handlers_lvgl.h" // aqui estan los handles, que son los que ejecutan acciones
#include "../interfaz_LVGL/elementos_interfaz_ui.h" // aqui estan las fuciones de configuracion de los elementos que se mostraran en pantalla
#include "../interfaz_LVGL/funciones_fundamentales_lvgl.h" // aqui estan las funciones y elementos fundamentales que permiten que funcion LVGL
*/

void tareaLVGL(void * parameter) {
/*
  #if iniciarDesdeLVGL 
    procesoDeInicioDePantalla(); // Esta parte ya la hace la tarea de la pantalla, habilitar solo si esa tarea no se inicia
  #endif
  procesoDeInicioDeLVGL(); // ejecuta el proceso para iniciar la interfaz grafica
  estilosLVGL(); // invoca los estilos del archivo estilos_lvgl.h

  lv_CargarPantalla_screenMain();

  //ejemploDePantalla();
  //lv_ex_cont_1(); // ejemplo de contenedor
  //lv_ex_chart_2(); // ejemplo de grafico
  //lv_ex_gauge_1(); // ejempolo de gauge
  //lv_ex_slider_prueba(sliderPrueba); // ejemplo de slider
  //lv_ex_roller_1(); // ejemplo de roller

  //lv_ex_textarea_2(); // muestra teclado y texto

  // El siguiente bucle mantiene activo a LVGL
  int i = 100;
  uint32_t ticks;
  int8_t cuentaGauge = 6; // permite desactivar gauge tras 6 cuentas
  while(true){
    lv_task_handler(); // mantiene activo LVGL

    /* // Lo siguiente es para hacer mover las agujas del gauge
    ticks = lv_tick_get();
    while(lv_tick_elaps(ticks) < 2); // funciona como delay en animaciones

    //Para hacer mover el gauge
    if (cuentaGauge>0) {
      i-=1;
      if(i==0) {i=100; cuentaGauge -= 1;} // cuando llega a 0, lo reinicia a 100 y resta 1 a la cuenta
      lv_gauge_set_value(gauge1, 0, i);
    }
    */
    
  } // fin del bucle infinito

  vTaskDelete(NULL); // elimina la tarea en caso de que se salga del ciclo infinito

*/
} // fin de la tarea

