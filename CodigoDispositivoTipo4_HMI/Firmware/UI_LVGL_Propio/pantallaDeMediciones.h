

//----------------------------------------

static void event_handler(lv_event_t * e)                           // handler al cumplirse un evento
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", (int)lv_obj_get_index(obj));  // registrar pulsacion

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
      lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); // ocultar el teclado

      if(obj == btnTabviewIzq){
        // lv_tabview_get_tab_act(tabview)  indica el tab activo comenzando por 0
        lv_tabview_set_act(tabview, lv_tabview_get_tab_act(tabview) - 1, LV_ANIM_OFF);
      }
      else if(obj == btnTabviewDer){
        // lv_tabview_get_tab_act(tabview)  indica el tab activo comenzando por 0
        lv_tabview_set_act(tabview, lv_tabview_get_tab_act(tabview) + 1, LV_ANIM_OFF);
      }
    }

    if(code == LV_EVENT_VALUE_CHANGED) {
      // Para evitar error y sincronizar todos los dd
      lv_dropdown_set_selected(dd, opcionSeleccionada);
    }
}

static void event_handlerBtnCerrar(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        //lv_obj_set_hidden(win, true);  // no funciona
        //lv_obj_add_flag(win, LV_OBJ_FLAG_HIDDEN);      // da error al volver a abrir la ventana varias veces
        lv_obj_del(win);  // elimina la ventana
    }
}

// Declaracion inicial de funciones
void actualizarSliderSegunCajas();   // funcion en el archivo tab5_disp2.h

// Callback de cajas de valores
static void cajaTextoCal1_event_cb(lv_event_t * e)
{
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_target(e);
    const char * txt = (const char*)lv_textarea_get_text(ta);

    /*
    if(txt[0] >= '0' && txt[0] <= '9' &&
       txt[1] >= '0' && txt[1] <= '9' &&
       txt[2] != ':') {
        lv_textarea_set_cursor_pos(ta, 2);
        lv_textarea_add_char(ta, ':');
    }
    */

    // Para mostrar el teclado
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
      lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN); // ocultar el teclado
      lv_keyboard_set_textarea(kb, ta); // pone a escribir el teclado en la cja de texto correspondiente
    }
    else if(code == LV_EVENT_VALUE_CHANGED) { 
      // Evento para mover automaticamente los sliders al modificar las cajas de texto
      if(ta == cajaTextoMin || ta == cajaTextoMinRojo){
        actualizarSliderSegunCajas();
      }
      
    }
}


/////////////////
// Tabview

static inline void scroll_begin_event(lv_event_t * e)
{
    /*Disable the scroll animations. Triggered when a tab button is clicked */
    if(lv_event_get_code(e) == LV_EVENT_SCROLL_BEGIN) {
        lv_anim_t * a = (lv_anim_t *)lv_event_get_param(e);
        if(a) a->time = 0;
    }
}

// Incluir archivos donde se encuentra el contenido de los tabs
#include "tab1_disp2.h" // Tab1
#include "tab2_disp2.h" // Tab2
#include "tab3_disp2.h" // Tab3
#include "tab4_disp2.h" // Tab4
#include "tab5_disp2.h" // Tab5

void lv_example_tabview_2(lv_obj_t * cont)
{
    /*Create a Tab view object*/
    tabview = lv_tabview_create(cont, LV_DIR_TOP, 30);  //lv_scr_act()
    //lv_obj_set_size(tabview, 470, 280);               // queda mal

    lv_obj_add_event_cb(lv_tabview_get_content(tabview), scroll_begin_event, LV_EVENT_SCROLL_BEGIN, NULL);

    lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);


    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Sensores");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Filtros");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Horarios");
    lv_obj_t * tab4 = lv_tabview_add_tab(tabview, "Calibracion");
    lv_obj_t * tab5 = lv_tabview_add_tab(tabview, "Alarmas");

    // Evento para ocultar el teclado
    lv_obj_add_event_cb(tabview, event_handler, LV_EVENT_VALUE_CHANGED, NULL);   // LV_EVENT_VALUE_CHANGED, LV_EVENT_CLICKED
    lv_obj_add_event_cb(tab1, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(tab2, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(tab3, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(tab4, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(tab5, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_set_style_bg_color(tab2, lv_color_make(0, 100, 150), 0);  // lv_color_make(red, green, blue) max por color: 255. O por ejemplo: lv_palette_lighten(LV_PALETTE_AMBER), 3)
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    /*Add content to the tabs*/
    crearTab1(tab1); 
    crearTab2(tab2);
    crearTab3(tab3); 
    crearTab4(tab4);
    crearTab5(tab5);    

    // Ejemplo de anadir objetos a los tab
    //lv_obj_t * labelEj = lv_label_create(tab2);
    //lv_label_set_text(labelEj, "Second tab");

    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}

/////////////////
// Window

void lv_example_win_1(void)
{
    win = lv_win_create(lv_scr_act(), 30);
    
    btnTabviewIzq = lv_win_add_btn(win, LV_SYMBOL_LEFT, 40);
    lv_obj_add_event_cb(btnTabviewIzq, event_handler, LV_EVENT_CLICKED, NULL);

    lv_win_add_title(win, "Panel de control de dipositivo 2");

    btnTabviewDer = lv_win_add_btn(win, LV_SYMBOL_RIGHT, 40);
    lv_obj_add_event_cb(btnTabviewDer, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 60);
    lv_obj_add_event_cb(btn, event_handlerBtnCerrar, LV_EVENT_CLICKED, NULL);

    lv_obj_t * cont = lv_win_get_content(win);

    /*Content can be added here*/
    lv_example_tabview_2(cont);   // meter en la ventana el tabview
}

///////////////////////
int cuentaConf = 0;
// Funcion que se repite hasta recibir la confirmacion de recibido o completar el tiempo limite (Posible error: falta resetear varible cuenta al tener exito)
void envioDeDatos(lv_timer_t * timer) {
  // static int cuenta = 0;  // si se usa static, la varible no se vuelve 0 al reiniciar la funcion
  if(cuentaConf < 20){
    // Usar el gestor de mensajes para convertir el json generado por la clase sensoresData a string:
    String msg = gestorMensajes.convertirJsonEnString( gestorMensajes.sensoresAsociados[opcionSeleccionada].genJsonParaActualizacionDatosLim(), true); // Con true se envia por serial automaticamente

    Serial.print("Intentento de envio. Msg: ");  // de prueba
    Serial.println(msg);  // de prueba
    cuentaConf += 1;
  }
  else{
    if(cuentaConf != 22){
      lv_msgbox_close(mbox1); // cerrar msgbox anterior
      lv_example_msgbox_1("Error", "Time out. Se ha alcanzado el maximo de intentos para enviar los nuevos ajustes."); // mostrar mensaje de intentos maximo alcanzados
    }
    cuentaConf = 0; // resetea la cuenta> necesario al usar variables estaticas
    lv_timer_del(timer);  // Terminar tarea(timer)
  }
}


// Funcion de eventos pantallaDeMediciones
static void event_handler_funciones(lv_event_t * e)                           // handler al cumplirse un evento
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", (int)lv_obj_get_index(obj));  // registrar pulsacion

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {

      // Boton enviar
      if(obj == botonEnviar){
        Serial.println("Enviar");

        // Guardar datos
        //-----------------------------------
        // Toma los valores de las cajas de texto y los conviente a float:
        float valorA = atof(lv_textarea_get_text(cajaTextoMin));     float valorB = atof(lv_textarea_get_text(cajaTextoMinRojo));
        float valorC = atof(lv_textarea_get_text(cajaTextoMinAma));  float valorD = atof(lv_textarea_get_text(cajaTextoMaxAma));
        float valorE = atof(lv_textarea_get_text(cajaTextoMaxRojo)); float valorF = atof(lv_textarea_get_text(cajaTextoMax));
        gestorMensajes.sensoresAsociados[opcionSeleccionada].guardarLimites(valorA,valorB,valorC,valorD,valorE,valorF);   // guarda los datos

        actualizarSliderSegunSensor();  // modifica la posicion del slider segun el sensor seleccionado y los datos actualizados
        actualizarHMIGeneral(dd);         // Actualiza la HMI en general

        // Hacer aparecer caja de texto
        //------------------------------------
        lv_example_msgbox_1("Envio de datos","Datos guardados localmente. Esperando confirmacion de recibido...", true);  // const char* titulo, const char* texto

        // Generar json
        //------------------------------------
        //... (ver si se puede usar la clase mensajes)
        timerConf = lv_timer_create(envioDeDatos, 1000, NULL);  // NULL, &user_data
        //Serial2.println("Enviar"); // temporal, cambiar string por el json generado
      }
      else if(obj == botonInfo){
        Serial.println("Info");

        // Caja de texto
        lv_example_msgbox_1("Informacion","En este panel se establecen los rangos de alarma para cada sensor."
        "La zona verde es el rango permitido, la amarilla es la zona de riesgo y la zona roja es una condicion critica.", false);  // const char* titulo, const char* texto

      }

    } // fin if code
}

////////////////////////////////////////////////////////////////////////////////
//*****************************************************************************
void crearPantallaDeMediciones(){
  //lv_example_meter_1(); // crear medidor gauge
  //lv_obj_add_event_cb(obj, drag_event_handler, LV_EVENT_PRESSING, NULL);
  lv_example_win_1();

  // Callback de botones
  lv_obj_add_event_cb(botonEnviar, event_handler_funciones, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(botonInfo, event_handler_funciones, LV_EVENT_CLICKED, NULL);  
}
