
// En este archivo se incluyen las funciones para los eventos de LVGL


// crear otra serie de datps asociada al grafico
lv_chart_series_t * ser2;

void cambiarSensor(lv_event_t * e)
{
  // Your code here
  //ser->y_points[3] = 800;
  //lv_chart_set_value_by_id(ui_Chart3, ser, 800, 3);
  //lv_chart_set_update_mode(ui_Chart3, LV_CHART_UPDATE_MODE_SHIFT);
  //lv_chart_set_update_mode(ui_Chart3, LV_CHART_UPDATE_MODE_CIRCULAR);

    //ser2 = lv_chart_add_series(ui_Chart3, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);

  if(lv_roller_get_selected(ui_Roller1) == 2){
      for(int i = 0; i<=1000; i++){
        
        //ser2->y_points[i] = lv_rand(10, 20);
        //lv_chart_set_next_value(ui_Chart3, ser2, lv_rand(20, 50));
        ecg_sample[i]=lv_rand(20, 500);
      }
      //ecg_sample[100]=800;
      lv_chart_refresh(ui_Chart3); /*Required after direct set*/
  }

  // Correr tarea de grafica
  if(lv_roller_get_selected(ui_Roller1)== 3)iniciarGrafica(3000);
}
//----------------------------------
void cambirPinDeMCP(lv_event_t * e)
{
  // Your code here

 // cambiar el estado segun el valor seleionado
 for (int i = 0; i<=15 ; i++){
  if(i == lv_roller_get_selected(ui_Roller3)){
    // poner high
    mcp.digitalWrite(i, HIGH);
  }else{
    // poner low
    mcp.digitalWrite(i, LOW);
  }
 }
} // fin

//----------------------------------
void hacerReinicio(lv_event_t * e)
{
  // Your code here
  ESP.restart();
  //iniciarMouseBLE(5000); // solo para pruebas
}

//----------------------------------
void recorridoDeLEDS(lv_event_t * e)
{
  // Your code here
  iniciarPruebasMCP(1024);
}
//----------------------------------
void activaFuncionalidad(lv_event_t * e)
{
  // Your code here
  uint16_t seleccionado = lv_dropdown_get_selected(ui_Dropdown1);
  switch (seleccionado){
    case 0:
      iniciarPruebasMCP(1024);
      break;
    case 1:
      iniciarMouseBLE(5000);
      break;
    case 2:
      iniciarAudBlue(8000);
      break;
    case 3:
      activarServo = true;
      iniciarServo(3000);
      break;
  }
}
//----------------------------------
void mostrarMenuMedidores(lv_event_t * e)
{
  // Your code here
 lv_example_menu_3();
 setupESPNOW();   // configura la conexión de ESP-now
  
}
//----------------------------------


//----------------------------------
//----------------------------------
//----------------------------------
//----------------------------------
