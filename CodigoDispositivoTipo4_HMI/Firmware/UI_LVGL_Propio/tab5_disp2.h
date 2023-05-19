#include "pgmspace.h"
#include "stdio.h"
/***************************************************************************************************
 * En este archivo se crea el contenido del tab5 del dispositivo tipo 2.

***************************************************************************************************/

// Objetos dentro del tab
//-------------------------------------------------------------------------------------------------


void lv_crear_menu_alarmas(lv_obj_t * cont){
  //
  lv_obj_t * menuAlarmas = lv_menu_create(cont);  //lv_scr_act() da error al volverlo a abrir
  lv_obj_set_size(menuAlarmas, 400, 160);
  lv_obj_align(menuAlarmas, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t * section;

    /*Create sub pages*/
    //lv_obj_t * sub_mechanics_page = lv_menu_page_create(menuAlarmas, NULL);
    //lv_obj_set_style_pad_hor(sub_mechanics_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    //lv_menu_separator_create(sub_mechanics_page);
    //section = lv_menu_section_create(sub_mechanics_page);

    //lv_obj_t * labelPrueba = lv_label_create(section);
    //lv_label_set_text(labelPrueba, "Hola");

    //create_sliderJulio(section, LV_SYMBOL_SETTINGS, "Limite rojo maximo", 0, 150, 120);
    //create_sliderJulio(section, LV_SYMBOL_SETTINGS, "Limite amarillo maximo", 0, 150, 50);
    //create_sliderJulio(section, LV_SYMBOL_SETTINGS, "Limite amarillo minimo", 0, 150, 80);

}


// Slider para desplazar los valores
//*****************************************
static void slider_event_cb(lv_event_t * e);

void actualizarSliderSegunSensor(){
  // Poner los valores actuales segun el sensor seleccionado
  //-----------------------------------------------------------
  lv_slider_set_range(slider, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[0], gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[5]);      // maximos y minimos 
  lv_slider_set_range(sliderVerde, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[0], gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[5]); // maximos y minimos
  
  lv_slider_set_value(slider, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[4], LV_ANIM_OFF);  // amarillo maximo
  lv_slider_set_left_value(slider, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[1], LV_ANIM_OFF);  // amarillo minimo
  lv_slider_set_value(slider, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[4], LV_ANIM_OFF);  // amarillo maximo       // se repite para corregir error de rango
  
  lv_slider_set_value(sliderVerde, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[3], LV_ANIM_OFF);  // verde maximo
  lv_slider_set_left_value(sliderVerde, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[2], LV_ANIM_OFF);  // verde minimo
  lv_slider_set_value(sliderVerde, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[3], LV_ANIM_OFF);  // verde maximo       // se repite para corregir error de rango
}

/*
float convertCharToFloat(unsigned char c='9'){
  float f=(float)(c-'0');//by explicit casting
  float fc=c-'0';//compiler implicitly convert char into float.
}
*/


void actualizarSliderSegunCajas(){
  // Poner los valores de las cajas
  //---------------------------------------------------------
  
  // Guardar valores de las cajas
  /*
  for(int i=0; i<6; i++){
    gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[i] = 0;
  }
  */
  
  // Actualizar con los datos almacenados
  //actualizarSliderSegunSensor();

  // Lo anterior esta dando error
  //-------------------
  /*  
  lv_slider_set_range(slider, 0, 200);      // maximos y minimos 
  lv_slider_set_range(sliderVerde, 0, 200); // maximos y minimos
  
  lv_slider_set_value(slider, 150, LV_ANIM_OFF);  // amarillo maximo
  lv_slider_set_left_value(slider, 50, LV_ANIM_OFF);  // amarillo minimo
  lv_slider_set_value(slider, 150, LV_ANIM_OFF);  // amarillo maximo         // se repite para corregir error de rango
  
  lv_slider_set_value(sliderVerde, 100, LV_ANIM_OFF);  // verde maximo
  lv_slider_set_left_value(sliderVerde, 60, LV_ANIM_OFF);  // verde minimo
  lv_slider_set_value(sliderVerde, 100, LV_ANIM_OFF);  // verde maximo       // se repite para corregir error de rango
  */
  // Lo anterior tambien esta dando error
  //-------------------

  Serial.println("Cambio de cajas");

  //gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[0] = atof(lv_textarea_get_text(cajaTextoMin));   //lv_textarea_get_text(cajaTextoMin)
  //gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[1] = atof(lv_textarea_get_text(cajaTextoMinRojo));
  //gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[2] = atof(lv_textarea_get_text(cajaTextoMinAma));
  //gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[3] = atof(lv_textarea_get_text(cajaTextoMaxAma));
  //gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[4] = atof(lv_textarea_get_text(cajaTextoMaxRojo));
  //gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[5] = atof(lv_textarea_get_text(cajaTextoMax));

}

/**
 * Show the current value when the slider is pressed by extending the drawer
 *
 */
void lv_example_slider_3(lv_obj_t * cont)
{
    /*Create a slider in the center of the display*/
    slider = lv_slider_create(cont);          //lv_scr_act()
    //lv_obj_center(slider);
    lv_obj_align(slider, LV_ALIGN_TOP_MID, 0, 45);  // 40 antiguo

    lv_slider_set_mode(slider, LV_SLIDER_MODE_RANGE);
    lv_slider_set_value(slider, 190.0, LV_ANIM_OFF);
    lv_slider_set_left_value(slider, 10.0, LV_ANIM_OFF);

    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_ALL, NULL);       // agregar el evento
    lv_obj_refresh_ext_draw_size(slider);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_ADV_HITTEST);

    lv_slider_set_range(slider, 0.0, 200.0);   // min , max
    
    static lv_style_t style_indicatorAma;
    lv_style_init(&style_indicatorAma);
    //lv_style_set_bg_opa(&style_indicator, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indicatorAma, lv_palette_main(LV_PALETTE_YELLOW));
    //lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);
    //lv_style_set_transition(&style_indicator, &transition_dsc);

    lv_obj_add_style(slider, &style_indicatorAma, LV_PART_INDICATOR);  // LV_PART_INDICATOR   //LV_PART_MAIN | LV_STATE_DEFAULT (para la parte de abajo)

    //static lv_style_t style_main; // estilo rojo
    //lv_style_init(&style_main);
    //lv_style_set_bg_opa(&style_main, LV_OPA_COVER);
    //lv_style_set_bg_color(&style_main, lv_color_hex3(0xbbb));
    //lv_style_set_radius(&style_main, LV_RADIUS_CIRCLE);
    //lv_style_set_pad_ver(&style_main, -2); /*Makes the indicator larger*/

    //lv_obj_add_style(slider, &style_main, LV_PART_MAIN);

    //--------------------------------

    sliderVerde = lv_slider_create(cont);          //lv_scr_act()
    lv_obj_center(sliderVerde);
    lv_obj_align(sliderVerde, LV_ALIGN_TOP_MID, 0, 45);

    lv_slider_set_mode(sliderVerde, LV_SLIDER_MODE_RANGE);
    lv_slider_set_value(sliderVerde, 166.0, LV_ANIM_OFF);
    lv_slider_set_left_value(sliderVerde, 29.0, LV_ANIM_OFF);

    lv_slider_set_range(sliderVerde, 0.0, 200.0);   // min , max
    lv_obj_add_event_cb(sliderVerde, slider_event_cb, LV_EVENT_ALL, NULL);  // agregar el evento
    
    static lv_style_t style_indicatorVerde;
    lv_style_set_bg_color(&style_indicatorVerde, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_pad_ver(&style_indicatorVerde, -2); /*Makes the indicator larger*/
    lv_obj_add_style(sliderVerde, &style_indicatorVerde, LV_PART_INDICATOR); 

    static lv_style_t style_bg_rojo;
    //lv_style_set_bg_opa(&style_bg_rojo, LV_OPA_COVER);
    lv_style_set_bg_color(&style_bg_rojo, lv_palette_main(LV_PALETTE_RED));
    lv_obj_add_style(sliderVerde, &style_bg_rojo, LV_PART_MAIN | LV_STATE_DEFAULT); 
    lv_obj_add_style(slider, &style_bg_rojo, LV_PART_MAIN | LV_STATE_DEFAULT); 

    static lv_style_t style_knob;  // para el selector
    lv_style_set_bg_opa(&style_knob, 0);    // para ocultar el knob
    lv_obj_add_style(slider, &style_knob, LV_PART_KNOB); 
    lv_obj_add_style(sliderVerde, &style_knob, LV_PART_KNOB); 

    //lv_obj_add_event_cb(sliderVerde, slider_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(sliderVerde);
    lv_obj_add_flag(sliderVerde, LV_OBJ_FLAG_ADV_HITTEST);

    // Actualizar el estado del slider
    //------------------------------------
    actualizarSliderSegunSensor();
}

static void slider_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);


    if(code == LV_EVENT_PRESSING  && obj == slider) {
      // Cambiar los valores de las cajas:
      //----------
      char buf1[6];
      char buf2[6];
      sprintf(buf1, "%.2f", (float)lv_slider_get_left_value(obj));
      sprintf(buf2, "%.2f", (float)lv_slider_get_value(obj));
      //lv_snprintf(buf1, sizeof(buf1), "%.2f", (float)lv_slider_get_left_value(obj) );
      //lv_snprintf(buf2, sizeof(buf2), "%.2f", (float)lv_slider_get_value(obj) );
            
      lv_textarea_set_text(cajaTextoMinRojo, buf1);
      lv_textarea_set_text(cajaTextoMaxRojo, buf2);
      //----------
    }
    else if (code == LV_EVENT_PRESSING  && obj == sliderVerde) {
      // Cambiar los valores de las cajas:
      //-----------
      char buf1[6];
      char buf2[6];
      sprintf(buf1, "%.2f", (float)lv_slider_get_left_value(obj));
      sprintf(buf2, "%.2f", (float)lv_slider_get_value(obj));
      //lv_snprintf(buf1, sizeof(buf1), "%.2f", (float)lv_slider_get_left_value(obj) );
      //lv_snprintf(buf2, sizeof(buf2), "%.2f", (float)lv_slider_get_value(obj) );
            
      lv_textarea_set_text(cajaTextoMinAma, buf1);
      lv_textarea_set_text(cajaTextoMaxAma, buf2);
      //---------------
    }

    /*Provide some extra space for the value*/
    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_event_set_ext_draw_size(e, 50);
    }
    else if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
        if(dsc->part == LV_PART_INDICATOR && obj == slider) {
            char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d - %d", (int)lv_slider_get_left_value(obj), (int)lv_slider_get_value(obj));

            lv_point_t label_size;
            lv_txt_get_size(&label_size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, 0);
            lv_area_t label_area;
            label_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - label_size.x / 2;
            label_area.x2 = label_area.x1 + label_size.x;
            label_area.y2 = dsc->draw_area->y1 - 1; //-10
            label_area.y1 = label_area.y2 - label_size.y;

            lv_draw_label_dsc_t label_draw_dsc;
            lv_draw_label_dsc_init(&label_draw_dsc);
            label_draw_dsc.color = lv_color_hex3(0xFF0);  // 0x888
            lv_draw_label(dsc->draw_ctx, &label_draw_dsc, &label_area, buf, NULL);
        }
        else if(dsc->part == LV_PART_INDICATOR && obj == sliderVerde) {
            char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d - %d", (int)lv_slider_get_left_value(obj), (int)lv_slider_get_value(obj));
                               
            lv_point_t label_size;
            lv_txt_get_size(&label_size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, 0);
            lv_area_t label_area;
            label_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - label_size.x / 2;
            label_area.x2 = label_area.x1 + label_size.x;
            label_area.y2 = dsc->draw_area->y1 + 28; //-10
            label_area.y1 = label_area.y2 - label_size.y;

            lv_draw_label_dsc_t label_draw_dsc;
            lv_draw_label_dsc_init(&label_draw_dsc);
            label_draw_dsc.color = lv_color_hex3(0x0F0);  // 0x888
            lv_draw_label(dsc->draw_ctx, &label_draw_dsc, &label_area, buf, NULL);
        }
    }
}

// cajas de texto

// El evento es el mismo del tab4 para mostrar el teclado (falta actualizar slider segun las cajas y los datos previos)
void cajasDeTexto(lv_obj_t * cont){
  cajaTextoMin = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoMin, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoMin, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoMin, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoMin, 7);
  lv_textarea_set_text(cajaTextoMin, "");
  lv_obj_set_size(cajaTextoMin, 65, 40);
  lv_obj_align(cajaTextoMin, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_t * labelMin = lv_label_create(cont);
  lv_label_set_text(labelMin, "Min");
  lv_obj_align_to(labelMin, cajaTextoMin, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);  // para alinear un indicador del datos

  cajaTextoMinRojo = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoMinRojo, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoMinRojo, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoMinRojo, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoMinRojo, 7);
  lv_textarea_set_text(cajaTextoMinRojo, "");
  lv_obj_set_size(cajaTextoMinRojo, 65, 40);
  lv_obj_align_to(cajaTextoMinRojo, cajaTextoMin, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_t * labelMinRojo = lv_label_create(cont);
  lv_label_set_text(labelMinRojo, "Amin");
  lv_obj_align_to(labelMinRojo, cajaTextoMinRojo, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);  // para alinear un indicador del datos

  cajaTextoMinAma = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoMinAma, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoMinAma, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoMinAma, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoMinAma, 7);
  lv_textarea_set_text(cajaTextoMinAma, "");
  lv_obj_set_size(cajaTextoMinAma, 65, 40);
  lv_obj_align_to(cajaTextoMinAma, cajaTextoMinRojo, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_t * labelMinAma = lv_label_create(cont);
  lv_label_set_text(labelMinAma, "Vmin");
  lv_obj_align_to(labelMinAma, cajaTextoMinAma, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);  // para alinear un indicador del datos
  
  cajaTextoMaxAma = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoMaxAma, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoMaxAma, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoMaxAma, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoMaxAma, 7);
  lv_textarea_set_text(cajaTextoMaxAma, "");
  lv_obj_set_size(cajaTextoMaxAma, 65, 40);
  lv_obj_align_to(cajaTextoMaxAma, cajaTextoMinAma, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_t * labelMaxAma = lv_label_create(cont);
  lv_label_set_text(labelMaxAma, "Vmax");
  lv_obj_align_to(labelMaxAma, cajaTextoMaxAma, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);  // para alinear un indicador del datos

  cajaTextoMaxRojo = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoMaxRojo, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoMaxRojo, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoMaxRojo, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoMaxRojo, 7);
  lv_textarea_set_text(cajaTextoMaxRojo, "");
  lv_obj_set_size(cajaTextoMaxRojo, 65, 40);
  lv_obj_align_to(cajaTextoMaxRojo, cajaTextoMaxAma, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_t * labelMaxRojo = lv_label_create(cont);
  lv_label_set_text(labelMaxRojo, "Amax");
  lv_obj_align_to(labelMaxRojo, cajaTextoMaxRojo, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);  // para alinear un indicador del datos

  cajaTextoMax = lv_textarea_create(cont);
  lv_obj_add_event_cb(cajaTextoMax, cajaTextoCal1_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(cajaTextoMax, cajaTextoCal1_event_cb, LV_EVENT_CLICKED, NULL);
  lv_textarea_set_accepted_chars(cajaTextoMax, "0123456789.-");
  lv_textarea_set_max_length(cajaTextoMax, 7);
  lv_textarea_set_text(cajaTextoMax, "");
  lv_obj_set_size(cajaTextoMax, 65, 40);
  lv_obj_align_to(cajaTextoMax, cajaTextoMaxRojo, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
  lv_obj_t * labelMax = lv_label_create(cont);
  lv_label_set_text(labelMax, "Max");
  lv_obj_align_to(labelMax, cajaTextoMax, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);  // para alinear un indicador del datos

  // Agregar los texto guardados
  actulizarTextoLimitesSegunSensor();
  
  // Boton para efectuar la configuracion
  botonEnviar = lv_btn_create(cont);
  lv_obj_t * labalBtnEnviar = lv_label_create(botonEnviar); // anadirle etiqueta al boton
  lv_label_set_text(labalBtnEnviar, "Enviar y guardar cambios");
  lv_obj_center(labalBtnEnviar);
  lv_obj_align_to(botonEnviar, cont, LV_ALIGN_BOTTOM_RIGHT, 0, 0); // alinear el boton

  // Boton de informacion es
  // En este panel se establecen los rangos de alarma para cada sensor. La zona verde es el rango permitido,
  //la amarilla es la zona de riesgo y la zona roja es una condicion critica.
  botonInfo = lv_btn_create(cont);  // el event está en pantallaMediciones.h
  lv_obj_t * labalBtnInfo = lv_label_create(botonInfo); // anadirle etiqueta al boton
  lv_label_set_text(labalBtnInfo, LV_SYMBOL_WARNING);
  lv_obj_center(labalBtnInfo);
  lv_obj_set_style_bg_color(botonInfo, lv_palette_lighten(LV_PALETTE_GREEN, 2), 0);
  lv_obj_align_to(botonInfo, cont, LV_ALIGN_BOTTOM_LEFT, 0, 0); // alinear el boton
}

void actulizarTextoLimitesSegunSensor(){
  // Agregar los texto guardados
  char buffer[10];
  for(int i = 0; i<6; i++){
    sprintf(buffer, "%.1f", gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[i]);
    switch(i){
      case 0: lv_textarea_set_text(cajaTextoMin, buffer); break;
      case 1: lv_textarea_set_text(cajaTextoMinRojo, buffer); break;
      case 2: lv_textarea_set_text(cajaTextoMinAma, buffer); break;
      case 3: lv_textarea_set_text(cajaTextoMaxAma, buffer); break;
      case 4: lv_textarea_set_text(cajaTextoMaxRojo, buffer); break;
      case 5: lv_textarea_set_text(cajaTextoMax, buffer); break;
    }
    
  }
}

// Funcion de creacion del tab
void crearTab5(lv_obj_t * tab){
  // Mostrar selector del sensor
  lv_obj_t * label = lv_label_create(tab);
  lv_label_set_text(label, "Elegir sensor para ver las mediciones:");
  lv_example_dropdown_1(tab);         // mostrar lista para la seleccion del menu

  //Mostrar menu
  //lv_crear_menu_alarmas(tab);

  // Mostrar slider
  lv_example_slider_3(tab);

  // Cajas de texto
  cajasDeTexto(tab);

}