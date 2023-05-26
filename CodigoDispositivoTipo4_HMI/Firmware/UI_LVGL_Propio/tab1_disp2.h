#include "pgmspace.h"
#include "stdint.h"
#include "lvgl.h"
/***************************************************************************************************
 * En este archivo se crea el contenido del tab1 del dispositivo tipo 2.

***************************************************************************************************/


//////////////////////////////////////////////////////////////////
//static lv_obj_t * meter;      // trasladado al ino
//lv_meter_indicator_t * indic; // trasladado al ino

///////////////////////
// Medidor
static void set_value(lv_meter_indicator_t* indic, float v)  //int32_t cambiado a float
{
    // Mover el medidor Gauge
    lv_meter_set_indicator_value(meter, indic, v);

    // Convertir valor int a char y ponerlo en la etiqueta
    char bufferValor[20];
    sprintf(bufferValor, "%f", v); // para pasar de float a char*    
    lv_label_set_text(labelMedida, bufferValor);

    // Cambiar grafico
    //ser2->y_points[3] = v;  // no funciona
}

// Funcion de eventos
static void event_handler_meter(lv_event_t * e)                           // handler al cumplirse un evento
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", (int)lv_obj_get_index(obj));  // registrar pulsacion

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_REFRESH) {
      //opcionSeleccionada = lv_dropdown_get_selected(dd); // registrar la opcion selecionada de la lista
      //Serial.println(opcionSeleccionada);  // para probar
      float lectura = gestorMensajes.sensoresAsociados[opcionSeleccionada].lecturaFisica;
      set_value(indic, lectura); // poner en el medidor el valor actual del sensor seleccionado

      // Grafico ------------------------------------------
      if(lectura > 50){
        lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, lectura+10);  // chart, eje, min, max
        //lv_chart_set_zoom_x(chart1, 100); // eliminar
        lv_meter_set_scale_range(meter,scale,0,lectura+10,280,130); // Ajustar las escala del grafico (meter, escala, min, max, angulo, rotacion)
      }
      lv_chart_set_next_value(chart1, ser1_1, lectura);
    }
}


void agregarArcosMeter(float limites[6], lv_meter_indicator_t * indicador);   // esto para evitar problemas al compilar, porque se usa en la siguiente funcion pero se define luego
void actualizarSliderSegunSensor();      // funcion definida en el tab5
void actulizarTextoLimitesSegunSensor(); // funcion definida en el tab5
void actulizarTextoCalibSegunSensor();   // funcion definida en el tab5

void actualizarHMIGeneral(lv_obj_t * obj){
          //char buf[32];
        //lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        //printf("Option: %s\n", buf);
 
        lv_chart_set_all_value(chart1, ser1_1, LV_CHART_POINT_NONE); // limpiar la grafica al cambiar de sensor
        lv_label_set_text(labelMedida, "Espere"); // limpiar ultimo valor del gauge

        opcionSeleccionada = lv_dropdown_get_selected(obj);
        // Nota: seria conveniente mover este switch a la clase sensoresData
        switch(opcionSeleccionada){ 
          case 0: lv_label_set_text(labelEc, "La temperatura no requiere calibracion."); 
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, "Celsius");
                  break;
          case 1: lv_label_set_text(labelEc, "pH = A + (B - voltaje)/C");         // 7 + (2.5-voltajePH)/valorCalibracionPH
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, " ");
                  break;
          case 2: lv_label_set_text(labelEc, "cond(uS/cm) = A(voltajeCor)^2 + B(voltajeCor) + C");
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, "uS/cm");
                  break;
          case 3: lv_label_set_text(labelEc, "Turb(NTU) = A(voltaje) + B");
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, "NTU");
                  break;
          case 4: lv_label_set_text(labelEc, "TDS(ppm) = 0.5(A(voltaje)^3 - B(voltaje)^2 + C(voltaje))");
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, "ppm");
                  break;
          case 5: lv_label_set_text(labelEc, "Pres(MPa) = A(voltaje) + B");
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, "MPa");
                  break;
          case 6: lv_label_set_text(labelEc, "Caud(m3/s) = A(voltaje) + B");
                  // Agregar cambios de grafica, unidades, etc
                  lv_label_set_text(labelUnidad, "m3/s");
          default: lv_label_set_text(labelEc, "Error. Sensor no registrado."); break;
        }
        lv_meter_set_scale_range(meter,scale,gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[0],gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[5],280,130); // Ajustar las escala del grafico (meter, escala, min, max, angulo, rotacion)
        lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[0], gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[5]);  // chart, eje, min, max

        lv_meter_indicator_t * indicador;
        agregarArcosMeter(gestorMensajes.sensoresAsociados[opcionSeleccionada].limites, indicador); // agrega los limites de color al gauge (meter)     // ** no funciona por el momento
        
        actualizarSliderSegunSensor();  // modifica la posicion del slider segun el sensor seleccionado
        actulizarTextoLimitesSegunSensor(); // actualiza el texto a los datos guardados segun el sensor seleccionado
        actulizarTextoCalibSegunSensor();    // Muestra los valores de calibracion guardados en las cajas de texto 
}

// Funcion de evento de la lista desplegable
static void event_handler_dd(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
      actualizarHMIGeneral(obj);
    }
}

/**
 * A simple meter
 */

void agregarArcosMeter(float limites[6], lv_meter_indicator_t * indicador){
  // Funcion para agregar los arcos de colores al medidor
  
    //lv_meter_indicator_t * indic;

    /*Add a red arc to the end*/
    //-----------------------------------------
    indicador = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indicador, limites[0]);
    lv_meter_set_indicator_end_value(meter, indicador, limites[5]);

    /*Make the tick lines red at the end of the scale*/
    indicador = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    
    lv_meter_set_indicator_start_value(meter, indicador, limites[0]);
    lv_meter_set_indicator_end_value(meter, indicador, limites[5]);

    /*Agregar arco amarillo al medio*/
    //-------------------------------------------
    indicador = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_meter_set_indicator_start_value(meter, indicador, limites[1]);
    lv_meter_set_indicator_end_value(meter, indicador, limites[4]);

    /*Make the tick lines yellow at the start of the scale*/
    indicador = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_YELLOW), lv_palette_main(LV_PALETTE_YELLOW),
                                     false, 0);
    lv_meter_set_indicator_start_value(meter, indicador, limites[1]);
    lv_meter_set_indicator_end_value(meter, indicador, limites[4]);


    /*Add a green arc to the start*/
    //-------------------------------------------
    indicador = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_meter_set_indicator_start_value(meter, indicador, limites[2]);
    lv_meter_set_indicator_end_value(meter, indicador, limites[3]);

    /*Make the tick lines blue at the start of the scale*/
    indicador = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_GREEN),
                                     false, 0);
    lv_meter_set_indicator_start_value(meter, indicador, limites[2]);
    lv_meter_set_indicator_end_value(meter, indicador, limites[3]);


}
void lv_example_meter_1(lv_obj_t * cont)     //lv_obj_t * cont
{
    meter = lv_meter_create(cont);  // screenMediciones
    //lv_obj_center(meter);
    lv_obj_align(meter, LV_ALIGN_LEFT_MID, -5, 15);
    lv_obj_set_size(meter, 160, 160);

    /*Add a scale first*/
    scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));  // GREY
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);
    lv_meter_set_scale_range(meter,scale,gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[0],gestorMensajes.sensoresAsociados[opcionSeleccionada].limites[5],280,130); // Ajustar las escala del grafico (meter, escala, min, max, angulo, rotacion)

    // agregar arco
    agregarArcosMeter(todosLosSensoresData[0].limites, indic); // agrega los limites de color (indic es una variable global)

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    // Anadir label para indicar valor
    labelMedida = lv_label_create(meter);
    lv_label_set_text(labelMedida, "0.0");
    lv_obj_align(labelMedida, LV_ALIGN_BOTTOM_MID, 0, 0);

    // Label de unidades
    labelUnidad = lv_label_create(meter);
    lv_label_set_text(labelUnidad, "Celsius");
    lv_obj_align(labelUnidad, LV_ALIGN_BOTTOM_MID, 0, 15);

    // Mostrar valor
    //set_value(indic, gestorMensajes.sensoresAsociados[2].temperatura); 
    set_value(indic, gestorMensajes.sensoresAsociados[lv_dropdown_get_selected(dd)].temperatura); // poner en el medidor el valor actual del sensor seleccionado
    lv_obj_add_event_cb(meter, event_handler_meter, LV_EVENT_REFRESH, NULL); // agregar el evento que permite la actualizacion de la medida

/*
    //Create an animation to set the value
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_var(&a, indic);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
*/
}

///////////////////////////
// Grafico

static lv_chart_cursor_t * cursor;

static void event_cb_chart1(lv_event_t * e)
{
    static int32_t last_id = -1;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        last_id = lv_chart_get_pressed_point(obj);
        if(last_id != LV_CHART_POINT_NONE) {
            lv_chart_set_cursor_point(obj, cursor, NULL, last_id);
        }
    }
    else if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
        if(!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_CURSOR)) return;
        if(dsc->p1 == NULL || dsc->p2 == NULL || dsc->p1->y != dsc->p2->y || last_id < 0) return;

        lv_coord_t * data_array = lv_chart_get_y_array(chart1, ser1_1);
        lv_coord_t v = data_array[last_id];
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "%d", v);

        lv_point_t size;
        lv_txt_get_size(&size, buf, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

        lv_area_t a;
        a.y2 = dsc->p1->y - 5;
        a.y1 = a.y2 - size.y - 10;
        a.x1 = dsc->p1->x + 10;
        a.x2 = a.x1 + size.x + 10;

        lv_draw_rect_dsc_t draw_rect_dsc;
        lv_draw_rect_dsc_init(&draw_rect_dsc);
        draw_rect_dsc.bg_color = lv_palette_main(LV_PALETTE_BLUE);
        draw_rect_dsc.radius = 3;

        lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);

        lv_draw_label_dsc_t draw_label_dsc;
        lv_draw_label_dsc_init(&draw_label_dsc);
        draw_label_dsc.color = lv_color_white();
        a.x1 += 5;
        a.x2 -= 5;
        a.y1 += 5;
        a.y2 -= 5;
        lv_draw_label(dsc->draw_ctx, &draw_label_dsc, &a, buf, NULL);
    }
}


void lv_example_chart_1(lv_obj_t * cont)
{
    /*Create a chart*/
    chart1 = lv_chart_create(cont);       // lv_scr_act()
    lv_obj_set_size(chart1, 220, 150);
    //lv_obj_center(chart);
    lv_obj_align(chart1, LV_ALIGN_RIGHT_MID, 0, 15);
    lv_chart_set_type(chart1, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    /*Add two data series*/
    ser1_1 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    ser2_1 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);

    // Ticks del grafico:
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_Y, 5, 2, 5, 3, true, 45);  //chart1, axis, major_len, minor_len, major_cnt, minor_cnt, label_en, draw_size
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_X, 5, 2, 5, 3, true, 30);  //chart1, axis, major_len, minor_len, major_cnt, minor_cnt, label_en, draw_size

    // Para el cursor:
    lv_obj_add_event_cb(chart1, event_cb_chart1, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(chart1);
    cursor = lv_chart_add_cursor(chart1, lv_palette_main(LV_PALETTE_BLUE), LV_DIR_LEFT | LV_DIR_BOTTOM);
    //lv_chart_set_zoom_x(chart1, 800);

    lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0.0, 50.0);  // para cambiar limites

/*
    //Set the next points on 'ser1'
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 0);
    lv_chart_set_next_value(chart, ser1, 30);
    lv_chart_set_next_value(chart, ser1, 70);
    lv_chart_set_next_value(chart, ser1, 90);

    //Directly set points on 'ser2'
    ser2->y_points[0] = 90;
    ser2->y_points[1] = 70;
    ser2->y_points[2] = 65;
    ser2->y_points[3] = 65;
    ser2->y_points[4] = 65;
    ser2->y_points[5] = 65;
    ser2->y_points[6] = 65;
    ser2->y_points[7] = 65;
    ser2->y_points[8] = 65;
    ser2->y_points[9] = 65;

    lv_chart_refresh(chart); //Required after direct set

*/
    //lv_obj_add_event_cb(chart1, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    //lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR);
    //lv_timer_create(add_data, 200, NULL);

    /*Create task for filling the Charts*/
	  //lv_task_create(chart_task, 100, LV_TASK_PRIO_LOW, NULL);   // ver https://forum.lvgl.io/t/multi-chart-in-single-window-using-littlevgl/1487/5

}

// Lista desplegable
void lv_example_dropdown_1(lv_obj_t * cont)
{

    /*Create a normal drop down list*/
    dd = lv_dropdown_create(cont);
    //String opcionesTexto = "";   // donde se van a guardar las opciones de la lista
    uint8_t numeroSensores =  gestorMensajes.numeroSensores;
    lv_dropdown_clear_options(dd);
    
    //lv_dropdown_set_options(dd, "Temp/n" "pH/n" "Cond/n" "Turb/n" "TDS"); // "Vacio"

    // Agregar cada uno de los sensores a la lista     numeroSensores
    for (uint8_t i = 0; i<numeroSensores; i++){
      char bufferParametro[10];
      sprintf(bufferParametro, "%s", gestorMensajes.sensoresAsociados[i].parametro); // para pasar de String a char*
      lv_dropdown_add_option(dd, bufferParametro, i); // (dropdown, "New option", pos)
    }

    // lv_dropdown_set_options(dd, "Apple\nBanana\n" "Orange\n" "Cherry\n" "Grape\n" "Raspberry\n" "Melon\n" "Orange\n" "Lemon\n" "Nuts");
    lv_obj_align(dd, LV_ALIGN_TOP_RIGHT, 0, -5);
    lv_obj_add_event_cb(dd, event_handler_dd, LV_EVENT_ALL, NULL);  // no se sabe si afecta la determinacion de la opcion seleccionada
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void crearTab1(lv_obj_t * tab){
  // Mostrar selector del sensor
  lv_obj_t * label = lv_label_create(tab);
  lv_label_set_text(label, "Elegir sensor para ver las mediciones:");
  lv_example_dropdown_1(tab);         // mostrar lista para la seleccion del menu
    
  lv_example_meter_1(tab);            // mostrar el gauge
  lv_example_chart_1(tab);    // mostrar el grafico
}

