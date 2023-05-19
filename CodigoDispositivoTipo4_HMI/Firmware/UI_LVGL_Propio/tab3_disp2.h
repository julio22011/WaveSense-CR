/***************************************************************************************************
 * En este archivo se crea el contenido del tab3 del dispositivo tipo 2.

***************************************************************************************************/

// Objetos dentro del tab

// Menu desplegable de seleccion de horario
void lv_example_dropdown_Filtros_Horario(lv_obj_t * cont)
{
    /*Create a normal drop down list*/
    ddFH = lv_dropdown_create(cont);

    //uint8_t numeroFiltros =  gestorMensajes.numeroFiltros;
    uint8_t numeroHorarios = 4;
    lv_dropdown_clear_options(ddFH);

    // Agregar cada uno de los sensores a la lista     numeroSensores
    for (uint8_t i = 0; i<numeroHorarios; i++){
      char bufferParametro[10];
      sprintf(bufferParametro, "Horario %i", i+1); // para pasar de String a char*
      lv_dropdown_add_option(ddFH, bufferParametro, i); // (dropdown, "New option", pos)
    }

    lv_obj_align_to(ddFH, labelActHorario, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_add_event_cb(ddFH, event_handler_ddF, LV_EVENT_ALL, NULL);  // no se sabe si afecta la determinacion de la opcion seleccionada
}


// Codigo de spindbox

static void event_handler_roller(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected value: %s", buf);
    }
}

/**
 * Roller with various alignments and larger text in the selected area
 */

#ifdef activarAnimacionDePruebaRoller
static void animPrueba(void * var, int v)
{
    lv_roller_set_selected( (lv_obj_t *)var, v, LV_ANIM_ON );  // rollerMin
}
#endif

void lv_example_roller_2(lv_obj_t * cont)
{
    /*A style to make the selected option larger*/
    static lv_style_t style_sel;
    lv_style_init(&style_sel);
    lv_style_set_text_font(&style_sel, &lv_font_montserrat_12);

    const char * optsHora = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23";
    const char * optsMin = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59";
    /*
    for(int i = 0; i<60 ; i++){
      if(i != 59)  sprintf(optsMin, "%p%i\n", optsMin, i);
      else sprintf(optsMin, "%p%i", optsMin, i);
    }
    */

    // Crear configuracion de los roller y las etiquetas
    labelActHorario = lv_checkbox_create(cont);
    lv_checkbox_set_text(labelActHorario, "Activar");   //Horario 1:
    lv_obj_align(labelActHorario, LV_ALIGN_TOP_LEFT, 15, 55);  //antes y=65

    // Poner el menu desplegable de seleccion de horario
    lv_example_dropdown_Filtros_Horario(cont);

    //lv_obj_t * rollerHora;  // trasladado
    //lv_obj_t * rollerMin;   // trasladado
    lv_obj_t * labelTem;    // label para clasificar cajas de tiempos

    /*A roller on the middle with center aligned text, and auto (default) width*/
    rollerHora = lv_roller_create(cont);
    lv_roller_set_options(rollerHora, optsHora, LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(rollerHora, 2);
    lv_obj_add_style(rollerHora, &style_sel, LV_PART_SELECTED);  // selecionar el estilo
    lv_obj_align_to(rollerHora, labelActHorario, LV_ALIGN_OUT_RIGHT_MID, 45, 20); // alinear el el roller de hora
    //lv_obj_align(rollerHora, LV_ALIGN_CENTER, 0, 0);  //-    
    lv_obj_add_event_cb(rollerHora, event_handler_roller, LV_EVENT_ALL, NULL);
    lv_roller_set_selected(rollerHora, 12, LV_ANIM_OFF);
    labelTem = lv_label_create(cont);
    lv_label_set_text(labelTem, "Hora");
    lv_obj_align_to(labelTem, rollerHora, LV_ALIGN_OUT_TOP_MID, 0, 0); // alinear

    /*A roller on the middle with center aligned text, and auto (default) width*/
    rollerMin = lv_roller_create(cont);
    lv_roller_set_options(rollerMin, optsMin, LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(rollerMin, 2);
    lv_obj_add_style(rollerMin, &style_sel, LV_PART_SELECTED);     // seleccionar el estilo
    lv_obj_align_to(rollerMin, rollerHora, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // alinear el el roller de min
    //lv_obj_align(rollerMin, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(rollerMin, event_handler_roller, LV_EVENT_ALL, NULL);
    lv_roller_set_selected(rollerMin, 0, LV_ANIM_OFF);
    labelTem = lv_label_create(cont);
    lv_label_set_text(labelTem, "Min");
    lv_obj_align_to(labelTem, rollerMin, LV_ALIGN_OUT_TOP_MID, 0, 0); // alinear

    //cb = lv_checkbox_create(lv_scr_act());
    //lv_checkbox_set_text(cb, "Apple");

    // agregar t1 y t2
    lv_obj_t * cajaTextoTempRetro = lv_textarea_create(cont);
    lv_obj_set_size(cajaTextoTempRetro, 60, 40);             // cambiar tamano a la caja de texto
    lv_obj_align_to(cajaTextoTempRetro, rollerMin, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // alinear
    labelTem = lv_label_create(cont);
    lv_label_set_text(labelTem, "T-retro");
    lv_obj_align_to(labelTem, cajaTextoTempRetro, LV_ALIGN_OUT_TOP_MID, 0, 0); // alinear
    lv_obj_add_event_cb(cajaTextoTempRetro, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);   // evento que permite efectuar cambios al modificar el texto
    lv_obj_add_event_cb(cajaTextoTempRetro, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * cajaTextoTempSucc = lv_textarea_create(cont);
    lv_obj_set_size(cajaTextoTempSucc, 60, 40);             // cambiar tamano a la caja de texto
    lv_obj_align_to(cajaTextoTempSucc, cajaTextoTempRetro, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // alinear
    labelTem = lv_label_create(cont);
    lv_label_set_text(labelTem, "T-enju");
    lv_obj_align_to(labelTem, cajaTextoTempSucc, LV_ALIGN_OUT_TOP_MID, 0, 0); // alinear
    lv_obj_add_event_cb(cajaTextoTempSucc, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);   // evento que permite efectuar cambios al modificar el texto
    lv_obj_add_event_cb(cajaTextoTempSucc, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);

    //...

    // Boton para efectuar la calibracion
    botonEnviar = lv_btn_create(cont);
    lv_obj_t * labalBtn = lv_label_create(botonEnviar); // anadirle etiqueta al boton
    lv_label_set_text(labalBtn, "Enviar y guardar cambios");
    lv_obj_center(labalBtn);
    lv_obj_align_to(botonEnviar, cont, LV_ALIGN_BOTTOM_RIGHT, 0, 0); // alinear el boton

    // Animacion de prueba
    #ifdef activarAnimacionDePruebaRoller
      lv_anim_t a;
      lv_anim_init(&a);
      lv_anim_set_exec_cb(&a, animPrueba); // indica la funcion que modifica los parametros
      lv_anim_set_var(&a, rollerMin);      // selecciona el objeto animado
      lv_anim_set_values(&a, 0, 30);      // indica el rango de valor que adquiere el parametro
      lv_anim_set_time(&a, 10000);
      lv_anim_set_path_cb(&a, lv_anim_path_ease_in);  // animacion lenta al inicio
      lv_anim_set_repeat_delay(&a, 100);
      lv_anim_set_playback_time(&a, 10000);
      lv_anim_set_playback_delay(&a, 100);
      lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
      lv_anim_start(&a);
    #endif
}


void lv_example_table_2(lv_obj_t * cont){
  //
}


// Funcion de creacion del tab
void crearTab3(lv_obj_t * tab){
  // Label de instruccion
  lv_obj_t * label = lv_label_create(tab);
  lv_label_set_text(label, "Elegir filtro para programar horarios:");

  // Crear equema de config. de horarios
  lv_example_roller_2(tab);
  
  // Crear la lista desplegable
  lv_example_dropdown_Filtros(tab);

}