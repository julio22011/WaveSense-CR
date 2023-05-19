

/*
 * En este archivo se copian los eventos que fueron programados desde SquareLine Studio
*/


void accionBotonPozo(lv_event_t * e)
{
	// Your code here
  lv_example_msgbox_1("Pozo", "Fuente de agua subterranea principal del acueducto.");
}


void abrirPantllaDispTipo2(lv_event_t * e)
{
	// Your code here
  //_ui_screen_change(screenMediciones, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
  //crearPantallaDeMediciones();
  //lv_scr_load_anim(screenMediciones, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false); // cambiar pantalla

  crearPantallaDeMediciones();
}

void abrirVentanaDeConfiguracion(lv_event_t * e)
{
  // Your code here
  //lv_example_menu_3();
  //lv_example_tabview_2();

  lv_example_menu_5_ajustes();
}

void abrirConfigWiFi(lv_event_t * e)
{
	// Your code here

  // Prueba ajustes WiFi
  buildPWMsgBox();
  makeKeyboard();
  buildSettings();
}


// Funcion de eventos pantalla principal
static void event_handler_general(lv_event_t * e)                           // handler al cumplirse un evento
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", (int)lv_obj_get_index(obj));  // registrar pulsacion

    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
      if(obj == ui_ButtonFFeMn){
        lv_example_msgbox_1("Filtro Fe/Mn", "Filtro encargado de remover el hierro y manganeso con resina filox.");
      }
      else if(obj == ui_ButtonPulido){
        lv_example_msgbox_1("Filtro de pulido", "Filtro encargado de remover las particulas.");
      }
      else if(obj == ui_ButtonAlmacenamiento){
        lv_example_msgbox_1("Tanque de almacenamiento", "Tanque de 300 m3.");
      }
      else if(obj == ui_ButtonTanqDist){
        lv_example_msgbox_1("Tanque de distribución", "Tanque de 200 m3.");
      }
      else if(obj == ui_ButtonPulidoFinal){
        lv_example_msgbox_1("Filtro de pulido", "Filtro encargado de remover las particulas.");
      }
      else if(obj == ui_ButtonCloro1){
        lv_example_msgbox_1("Inyeccion de cloro", "Permite la oxidacion de las sustancias de los lodos.");
      }
      else if(obj == ui_ButtonCloro2){
        lv_example_msgbox_1("Inyeccion de cloro", "Permite la coagulacion.");
      }
      else if(obj == ui_ImgButton2){
        lv_example_msgbox_1("Sistema de bombeo", "Bomba centrifuga.");
      }
      else if(obj == ui_ButtonAguaMuni){
        lv_example_msgbox_1("Agua de municipalidad", "Entrada del agua proveniente de la municipalidad.");
      }
      else if(obj == ui_ButtonDisp1B){
        lv_example_msgbox_1("Registrador de macromedidor", "Registra el volumen de agua de salida de la planta de tratamiento.");
      }
      else if(obj == ui_ButtonDisp1A){
        lv_example_msgbox_1("Registrador de macromedidor", "Registra el volumen de agua de importado de la municipalidad.");
      }
      else if(obj == ui_ButtonDisp3){
        lv_example_msgbox_1("Sistema de calidad del agua", "Dispositivo de monitoreo de la calidad del agua suministrada.");
        crearPantallaDeMediciones(); // provisional
      }
      else if(obj == ui_ButtonRedDist){
        lv_example_msgbox_1("Sistema de distribucion", "Sistema para distribuir el agua a los usuarios.");
      }
    }
      
} // fin de evento general





