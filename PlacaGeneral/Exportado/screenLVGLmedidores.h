/*
 * Este código permite dibujar una pantalla de LVGL donde se muestran los medidores de los sensores
 */

// Constructores de funciones
void lv_example_meter_1(lv_obj_t * cont); // reibe el contenedor donde 

lv_obj_t * menu;
lv_obj_t * cont;
//lv_obj_t * label; // trasladado

 void lv_example_menu_3(void)
{
    /*Crear objeto de menu*/
    menu = lv_menu_create(lv_scr_act());  // lv_scr_act() o NULL
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    /*Modify the header*/
    lv_obj_t * back_btn = lv_menu_get_main_header_back_btn(menu);
    lv_obj_t * back_btn_label = lv_label_create(back_btn);
    lv_label_set_text(back_btn_label, "Atras");

    lv_obj_t * cont;
    lv_obj_t * label;

    /*Create sub pages*/
    lv_obj_t * sub_1_page = lv_menu_page_create(menu, "1. Mediciones del sensor de turbidez");

    cont = lv_menu_cont_create(sub_1_page);
    //label = lv_label_create(cont);
    //lv_label_set_text(label, "Mediciones del sensor de turbidez");
    // funcion que muestra grafico:
    lv_example_meter_1(cont); // mostrar el medidor

    //----------------------------------------------------
    lv_obj_t * sub_2_page = lv_menu_page_create(menu, "2. Mediciones del sensor de conductividad");

    cont = lv_menu_cont_create(sub_2_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Hello, I am hiding here");
    
    //----------------------------------------------------
    lv_obj_t * sub_3_page = lv_menu_page_create(menu, "3. Mediciones del sensor de pH");

    cont = lv_menu_cont_create(sub_3_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Hello, I am hiding here");
    //----------------------------------------------------
    lv_obj_t * sub_4_page = lv_menu_page_create(menu, "4. Mediciones del sensor de presion");

    cont = lv_menu_cont_create(sub_4_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Hello, I am hiding here");
    //***********************************************************

    /*Create a main page*/
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Sensor de Turbidez");
    lv_menu_set_load_page_event(menu, cont, sub_1_page);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Sensor de conductividad");
    lv_menu_set_load_page_event(menu, cont, sub_2_page);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Sensor de pH");
    lv_menu_set_load_page_event(menu, cont, sub_3_page);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Sensor de presion");
    lv_menu_set_load_page_event(menu, cont, sub_4_page);

    lv_menu_set_page(menu, main_page);
}


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//static lv_obj_t * meter; // trasladado al ino
//lv_meter_indicator_t * indic; // trasladado al ino

static void set_value(lv_meter_indicator_t* indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}

/**
 * A simple meter
 */
void lv_example_meter_1(lv_obj_t * cont)
{
    meter = lv_meter_create(cont);  //lv_scr_act()
    lv_obj_center(meter);
    lv_obj_set_size(meter, 200, 200);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));  // GREY
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);
    lv_meter_set_scale_range(meter,scale,0,15,280,130); // Ajustar las escala del grafico (meter, escala, min, max, angulo, rotacion)

    //lv_meter_indicator_t * indic;

    /*Add a blue arc to the start*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 4);

    /*Make the tick lines blue at the start of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE),
                                     false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 3);

    ///
        /*Agregar arco amarillo al medio*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_meter_set_indicator_start_value(meter, indic, 3);
    lv_meter_set_indicator_end_value(meter, indic, 5);

    /*Make the tick lines blue at the start of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_YELLOW), lv_palette_main(LV_PALETTE_YELLOW),
                                     false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 3);
    lv_meter_set_indicator_end_value(meter, indic, 5);


    /*Add a red arc to the end*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 5);
    lv_meter_set_indicator_end_value(meter, indic, 15);

    /*Make the tick lines red at the end of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false,
                                     0);
    lv_meter_set_indicator_start_value(meter, indic, 5);
    lv_meter_set_indicator_end_value(meter, indic, 15);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

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
