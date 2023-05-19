
/* 
En este archivo se configuran las cajas que envian mensajes

*/

// Incluir el archivo de creacion de objetos si no se ha incluido antes
#if !defined(incluidoCreacionDeObjetos)
#define incluidoCreacionDeObjetos
#include "creacionDeObjetos.h"
#endif

// Funcio
static void event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
}

void lv_example_msgbox_1(const char* titulo, const char* texto, bool estiloCarga = false)
{
    if(estiloCarga){
      static const char * btns1[] = {""};   // static const (cambiado porque varia segun condicion)
      mbox1 = lv_msgbox_create(NULL, titulo, texto, btns1, false);         //"Bienvenido"  "A continuacion se muestra la interfaz del acueducto."
    } 
    else {
      static const char * btns2[] = {"Aceptar", "Cerrar", ""};  // static const
      mbox1 = lv_msgbox_create(NULL, titulo, texto, btns2, true);         //"Bienvenido"  "A continuacion se muestra la interfaz del acueducto."
    }
    
    lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);

    if(estiloCarga){     // agregar un spinner de carga
      /*Create a spinner*/
      //-lv_obj_t * textoEspacio = lv_label_create(mbox1);
      //-lv_label_set_text(textoEspacio, "              ");                   // Texto para dejar un espacio
      lv_obj_t * textoEspera = lv_label_create(mbox1);
      lv_label_set_recolor(textoEspera, true);                // habilitar el re-color
      lv_label_set_text(textoEspera, "#ff0000 *Enviando#            ");  // Se utilizo comandos para cambiar el color del texto a rojo
      //-lv_obj_align_to(textoEspera, textoEspacio, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
      //lv_obj_align(textoEspera, LV_ALIGN_RIGHT_MID, 100, 60);  // alineado
      static lv_style_t style_textoEspera;
      lv_style_init(&style_textoEspera);
      lv_style_set_text_font(&style_textoEspera, &lv_font_montserrat_20);
      lv_obj_add_style(textoEspera, &style_textoEspera, 0);

      lv_obj_t * spinner = lv_spinner_create(mbox1, 1000, 60);  // lv_scr_act()
      lv_obj_set_size(spinner, 40, 40);
      lv_obj_align_to(spinner, textoEspera, LV_ALIGN_OUT_RIGHT_MID, 100, 0);  // poner el spinner a la par del texto
    }
    
}


