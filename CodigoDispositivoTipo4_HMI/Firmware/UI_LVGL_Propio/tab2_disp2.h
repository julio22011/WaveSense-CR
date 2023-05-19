/***************************************************************************************************
 * En este archivo se crea el contenido del tab2 del dispositivo tipo 2.

***************************************************************************************************/


// Funcion de evento de la lista desplegable
static void event_handler_ddF(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        //char buf[32];
        //lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        //printf("Option: %s\n", buf);
        opcionSeleccionada = lv_dropdown_get_selected(obj);
    }
}

// Objetos dentro del tab
//-------------------------------------------------------------------------------------------------

// Menu desplegable de seleccion de filtro
void lv_example_dropdown_Filtros(lv_obj_t * cont)
{
    /*Create a normal drop down list*/
    ddF = lv_dropdown_create(cont);
    //String opcionesTexto = "";   // donde se van a guardar las opciones de la lista
    uint8_t numeroFiltros =  gestorMensajes.numeroFiltros;
    lv_dropdown_clear_options(ddF);

    // Agregar cada uno de los sensores a la lista     numeroSensores
    for (uint8_t i = 0; i<numeroFiltros; i++){
      char bufferParametro[10];
      sprintf(bufferParametro, "%i", gestorMensajes.filtrosAsociados[i].numeroDeFiltro); // para pasar de String a char*
      lv_dropdown_add_option(ddF, bufferParametro, i); // (dropdown, "New option", pos)
    }

    // lv_dropdown_set_options(dd, "Apple\nBanana\n" "Orange\n" "Cherry\n" "Grape\n" "Raspberry\n" "Melon\n" "Orange\n" "Lemon\n" "Nuts");
    lv_obj_align(ddF, LV_ALIGN_TOP_RIGHT, 0, -5);
    lv_obj_add_event_cb(ddF, event_handler_ddF, LV_EVENT_ALL, NULL);  // no se sabe si afecta la determinacion de la opcion seleccionada
}


// Lista de acciones
static lv_obj_t * list1;

static void event_handler_lista(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(list1, obj));
    }

    if(code == LV_EVENT_CLICKED){   //  && lv_list_get_btn_text(list1, obj) == "Hacer retrolavado"
      Serial.println("Hacer retrolavado");
      Serial2.println("Hacer retrolavado");  // temporal
    }
}

void lv_example_list_1(lv_obj_t * cont)
{
    /*Create a list*/
    list1 = lv_list_create(cont);
    lv_obj_set_size(list1, 155, 100);
    lv_obj_align_to(list1, cont, LV_ALIGN_TOP_LEFT, 0, 30); // alinear el boton
    //lv_obj_align(list1, LV_ALIGN_LEFT_MID, 0, 15);

    /*Add buttons to the list*/
    lv_obj_t * btn;

    lv_list_add_text(list1, "Acciones");
    btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, "Hacer retrolavado");
    lv_obj_add_event_cb(btn, event_handler_lista, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Ir a pos. de servicio");
    lv_obj_add_event_cb(btn, event_handler_lista, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list1, LV_SYMBOL_SAVE, "Save");
    lv_obj_add_event_cb(btn, event_handler_lista, LV_EVENT_CLICKED, NULL);

}

///////////////////////////
// Grafico

void lv_example_chart_2(lv_obj_t * cont)
{
    /*Create a chart*/
    chart2 = lv_chart_create(cont);       // lv_scr_act()
    lv_obj_set_size(chart2, 240, 150);
    //lv_obj_center(chart);
    lv_obj_align(chart2, LV_ALIGN_RIGHT_MID, 0, 15);
    lv_chart_set_type(chart2, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    /*Add two data series*/
    ser1_2 = lv_chart_add_series(chart2, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    ser2_2 = lv_chart_add_series(chart2, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);
}


// Funcion de creacion del tab
//-------------------------------------------------------------------------------------------------
void crearTab2(lv_obj_t * tab){
  // Label de instruccion
  lv_obj_t * label = lv_label_create(tab);
  lv_label_set_text(label, "Elegir filtro para ver sus condiciones:");

  // Crear la lista desplegable
  lv_example_dropdown_Filtros(tab);

  // Crear el grafico
  lv_example_chart_2(tab);

  //Crear lista de opciones
  lv_example_list_1(tab);

  // Etiquetas de estado
  lv_obj_t * labelFalloMotor = lv_label_create(tab);
  lv_obj_align(labelFalloMotor, LV_ALIGN_BOTTOM_LEFT, 0, 0);  
  lv_label_set_text_fmt(labelFalloMotor, "Estado del cabezal: %s", LV_SYMBOL_OK);

  lv_obj_t * labelFallaAgua = lv_label_create(tab);
  lv_obj_align_to(labelFallaAgua, labelFalloMotor, LV_ALIGN_OUT_TOP_LEFT, 0, 0);  
  lv_label_set_text_fmt(labelFallaAgua, "Estado del agua: %s", "?");

  lv_obj_t * labelEtapa = lv_label_create(tab);
  lv_obj_align_to(labelEtapa, labelFallaAgua, LV_ALIGN_OUT_TOP_LEFT, 0, 0);  
  lv_label_set_text_fmt(labelEtapa, "Etapa: %i", 0);


}




