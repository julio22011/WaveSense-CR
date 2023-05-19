
/*
 * Este es el archivo que contiene la funcion ui_mod_init(), para modificar el UI de SquareLine
*/

// Funcion que se ejecuta para anadir los elementos adicionales a la UI de LVGL
void ui_mod_init(){

  // Creacion de pantallas adicionales
  //crearPantallaDeMediciones();

  // Pantalla de bienvenida:
  lv_example_msgbox_1("Bienvenido", "A continuacion se muestra la interfaz del acueducto.");
  
  // Etiqueta de verficacion:  
  lv_labelDeJsonRecibidoFun(); // permite ver lectura de temp recibida (archivo labelDeJson.h)

  // Modificar etiquetas de EdgeLine:
  lv_label_set_text(ui_LabelBotonAjustes, LV_SYMBOL_SETTINGS);  //"A"
  lv_label_set_text(ui_LabelBotonMesh, LV_SYMBOL_WIFI);         //"M"

  // Agregar eventos a botones de interfaz pricipal
  lv_obj_add_event_cb(ui_ButtonFFeMn, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonPulido, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonAlmacenamiento, event_handler_general, LV_EVENT_CLICKED, NULL); 
  lv_obj_add_event_cb(ui_ButtonTanqDist, event_handler_general, LV_EVENT_CLICKED, NULL); 
  lv_obj_add_event_cb(ui_ButtonPulidoFinal, event_handler_general, LV_EVENT_CLICKED, NULL); 
  lv_obj_add_event_cb(ui_ButtonCloro1, event_handler_general, LV_EVENT_CLICKED, NULL); 
  lv_obj_add_event_cb(ui_ButtonCloro2, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ImgButton2, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonAguaMuni, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonDisp1B, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonDisp1A, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonDisp3, event_handler_general, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ButtonRedDist, event_handler_general, LV_EVENT_CLICKED, NULL);

}


// Funcion para actualizar la bateria
void actualizarBatUI(lv_timer_t * timer) {
  bateriaUI.actualizar();

  analogWrite(ledPantalla, analogRead(fotocelda)+50);
}


