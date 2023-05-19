// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project


#include "ui.h"

/*
void cambiarSensor(lv_event_t * e)
{
	// Your code here
 ser->points[3] = 800;
 lv_chart_refresh(ui_Chart3);
}
*/
void actualizarMenuDesplegado(lv_event_t * e)
{
	// Your code here
  switch(lv_roller_get_selected(ui_Roller2)){
    case 0:
      lv_obj_clear_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelSonido, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantalla, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantallaOTA, LV_OBJ_FLAG_HIDDEN);
      break;
    case 1:
      lv_obj_add_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelSonido, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantalla, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantallaOTA, LV_OBJ_FLAG_HIDDEN);
      break;
    case 2:
      lv_obj_add_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_PanelSonido, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantalla, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantallaOTA, LV_OBJ_FLAG_HIDDEN);
      break;
    case 3:
      lv_obj_add_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelSonido, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_PanelPantalla, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantallaOTA, LV_OBJ_FLAG_HIDDEN);
      break;
    case 4:
      lv_obj_add_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelSonido, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelPantalla, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_PanelPantallaOTA, LV_OBJ_FLAG_HIDDEN);
      break;
  }
}

/*
void hacerReinicio(lv_event_t * e)
{
	// Your code here
  //ESP.restart();
  //iniciarMouseBLE(5000); // solo para pruebas
}
*/


/*
void cambirPinDeMCP(lv_event_t * e)
{
	// Your code here

 // cambiar el estado segun el valor seleionado
 for (int i = 0; i<7 ; i++){
  if(i == lv_roller_get_selected(ui_Roller3)){
    // poner high
    mcp.digitalWrite(i, HIGH);
  }else{
    // poner low
    mcp.digitalWrite(i, LOW);
  }
 }
} // fin
*/

/*
void recorridoDeLEDS(lv_event_t * e)
{
	// Your code here
}
*/

/*
void prenderAudBlue(lv_event_t * e)
{
	// Your code here
}
*/

/*
void activaFuncionalidad(lv_event_t * e)
{
	// Your code here
}
*/

/*
void mostrarMenuMedidores(lv_event_t * e)
{
	// Your code here
 lv_example_menu_3();
}
*/
