/***************************************************************************************************
 * En este archivo se crea el contenido del tab4 del dispositivo tipo 2.
 * Tab de calibracion
***************************************************************************************************/

// Objetos dentro del tab

// Agregar los valores de calibracion guardados, en las cajas de texto
void actulizarTextoCalibSegunSensor(){
  
  float valoresCal[] = {gestorMensajes.sensoresAsociados[opcionSeleccionada].valorCalibracion,
                        gestorMensajes.sensoresAsociados[opcionSeleccionada].valorCalibracion2,
                        gestorMensajes.sensoresAsociados[opcionSeleccionada].valorCalibracion3};
  char buffer[10];
  for(int i = 0; i<3; i++){
    sprintf(buffer, "%.3f", valoresCal[i]);
    switch(i){
      case 0: lv_textarea_set_text(cajaTextoCal1, buffer); break;
      case 1: lv_textarea_set_text(cajaTextoCal2, buffer); break;
      case 2: lv_textarea_set_text(cajaTextoCal3, buffer); break;
    }
  }
}

void mostrarCajasDeCalibracion(lv_obj_t * cont){

  // Label para indicar la ecuacion:
  lv_obj_t * labelIndEc = lv_label_create(cont);
  lv_label_set_text(labelIndEc, "Ecuacion: ");
  lv_obj_align(labelIndEc, LV_ALIGN_LEFT_MID, 0, 10);

  labelEc = lv_label_create(cont);
  lv_label_set_text(labelEc, "La temperatura no tiene calibracion.");  // Ver events de tab1 para modificar las ecuaciones
  lv_obj_align_to(labelEc, labelIndEc, LV_ALIGN_OUT_RIGHT_MID, 10, 0);  // acomodar ecuacion a la derecha
  lv_label_set_long_mode(labelEc, LV_LABEL_LONG_SCROLL_CIRCULAR);   // configura la etiqueta para que si es muy largo, se mueva el texto
  lv_obj_set_width(labelEc, 330);

  //lv_obj_align_to(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);  // para alinear un indicador del datos

  // Cajas de texto para guardar los valores:
  cajaTextoCal1 = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoCal1, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoCal1, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoCal1, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoCal1, 7);
  lv_textarea_set_text(cajaTextoCal1, "");
  lv_obj_set_size(cajaTextoCal1, 80, 40);
  lv_obj_align(cajaTextoCal1, LV_ALIGN_LEFT_MID, 0, -30);
  lv_obj_t * labelA = lv_label_create(cont);
  lv_label_set_text(labelA, "A");
  lv_obj_align_to(labelA, cajaTextoCal1, LV_ALIGN_OUT_TOP_MID, 0, 0);  // para alinear un indicador del datos

  // Caja de texto del valor "B"
  cajaTextoCal2 = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoCal2, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoCal2, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoCal2, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoCal2, 7);
  lv_textarea_set_text(cajaTextoCal2, "");
  lv_obj_set_size(cajaTextoCal2, 80, 40);
  lv_obj_align(cajaTextoCal2, LV_ALIGN_LEFT_MID, 100, -30);
  lv_obj_t * labelB = lv_label_create(cont);
  lv_label_set_text(labelB, "B");
  lv_obj_align_to(labelB, cajaTextoCal2, LV_ALIGN_OUT_TOP_MID, 0, 0);  // para alinear un indicador del datos

  // Caja de texto del valor "C"
  cajaTextoCal3 = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoCal3, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoCal3, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoCal3, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoCal3, 7);
  lv_textarea_set_text(cajaTextoCal3, "");
  lv_obj_set_size(cajaTextoCal3, 80, 40);
  lv_obj_align(cajaTextoCal3, LV_ALIGN_LEFT_MID, 200, -30);
  lv_obj_t * labelC = lv_label_create(cont);
  lv_label_set_text(labelC, "C");
  lv_obj_align_to(labelC, cajaTextoCal3, LV_ALIGN_OUT_TOP_MID, 0, 0);  // para alinear un indicador del datos

  // Mostrar los valores de calibracion guardados
  actulizarTextoCalibSegunSensor();

  // Boton para efectuar la calibracion
  botonEnviar = lv_btn_create(cont);
  lv_obj_t * labalBtn = lv_label_create(botonEnviar); // anadirle etiqueta al boton
  lv_label_set_text(labalBtn, "Enviar y guardar cambios");
  lv_obj_center(labalBtn);
  lv_obj_align_to(botonEnviar, cont, LV_ALIGN_BOTTOM_RIGHT, 0, 0); // alinear el boton


  // Configurar un teclado
  kb = lv_keyboard_create(lv_scr_act());  //lv_scr_act()  //cont
  lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 3);  // -50
  lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
  lv_keyboard_set_textarea(kb, cajaTextoCal1);
  lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); // ocultar el teclado
}


// Funcion de creacion del tab
void crearTab4(lv_obj_t * tab){
  //
  // Lo mismo que en el tab1
  lv_obj_t * label = lv_label_create(tab);
  lv_label_set_text(label, "Elegir el sensor desea calibrar:");
  lv_example_dropdown_1(tab);         // mostrar lista para la seleccion del menu

  // Cajas
  mostrarCajasDeCalibracion(tab);

}


