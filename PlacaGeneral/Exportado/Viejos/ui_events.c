// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"

void cambiarSensor(lv_event_t * e)
{
	// Your code here

}

void actualizarMenuDesplegado(lv_event_t * e)
{
	// Your code here
  switch (lv_roller_get_selected(ui_Roller2)){
    case 0:
      lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      break;
    case 1:
      lv_obj_clear_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
      break;
  }
/*
  if(lv_roller_get_selected(ui_Roller2) == 0){
    lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
  } 
  else if(lv_roller_get_selected(ui_Roller2) == 1){
    lv_obj_clear_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_PanelWifi, LV_OBJ_FLAG_HIDDEN);
  }
*/
  
}
