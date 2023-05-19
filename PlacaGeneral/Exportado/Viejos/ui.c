// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Menu;
lv_obj_t * ui_Roller1;
lv_obj_t * ui_Button1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Chart3;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui_Button5;
lv_obj_t * ui_Label5;
lv_obj_t * ui_TextArea2;
lv_obj_t * ui_PanelNotificacion1;
lv_obj_t * ui_ButtonAjustes1;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Ajustes;
lv_obj_t * ui_PanelNotificacion;
lv_obj_t * ui_ButtonAjustes;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Label7;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Roller2;
lv_obj_t * ui_PanelWifi;
lv_obj_t * ui_panelActivacionWifi;
lv_obj_t * ui_Switch1;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Spinner1;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Slider1;
lv_obj_t * ui_Label16;
lv_obj_t * ui_PanelBluetooth;
lv_obj_t * ui_ButtonAtras;
lv_obj_t * ui_Label1;
lv_obj_t * ui_PanelMenuPower;
lv_obj_t * ui_ButtonApagar;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Label14;
lv_obj_t * ui_ButtonReiniciar;
lv_obj_t * ui_Label12;
lv_obj_t * ui_Label15;
lv_obj_t * ui_ButtonSalirPower;
lv_obj_t * ui_Label13;
lv_obj_t * ui_Label17;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_Menu(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
static void ui_event_Roller1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        cambiarSensor(e);
    }
}
static void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_RELEASED) {
        _ui_screen_change(ui_Ajustes, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_Button5(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_RELEASED) {
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    }
}
static void ui_event_TextArea2(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
static void ui_event_ButtonAjustes1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Ajustes, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 0);
    }
}
static void ui_event_ButtonAjustes(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_PanelMenuPower, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
static void ui_event_Roller2(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_RELEASED) {
        actualizarMenuDesplegado(e);
    }
}
static void ui_event_Switch1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_Label10, _UI_LABEL_PROPERTY_TEXT, "Activado");
        _ui_flag_modify(ui_Spinner1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_Label10, _UI_LABEL_PROPERTY_TEXT, "Desactivado");
        _ui_flag_modify(ui_Spinner1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
static void ui_event_ButtonAtras(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_RELEASED) {
        _ui_screen_change(ui_Menu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
static void ui_event_ButtonSalirPower(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_PanelMenuPower, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Menu_screen_init(void)
{

    // ui_Menu

    ui_Menu = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Menu, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Menu, ui_event_Menu, LV_EVENT_ALL, NULL);

    // ui_Roller1

    ui_Roller1 = lv_roller_create(ui_Menu);
    lv_roller_set_options(ui_Roller1, "pH\nTemperatura\nTurbidez", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_height(ui_Roller1, 100);
    lv_obj_set_width(ui_Roller1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Roller1, 160);
    lv_obj_set_y(ui_Roller1, 91);

    lv_obj_set_align(ui_Roller1, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_Roller1, ui_event_Roller1, LV_EVENT_ALL, NULL);

    // ui_Button1

    ui_Button1 = lv_btn_create(ui_Menu);

    lv_obj_set_width(ui_Button1, 137);
    lv_obj_set_height(ui_Button1, 50);

    lv_obj_set_x(ui_Button1, -150);
    lv_obj_set_y(ui_Button1, -30);

    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

    // ui_Label2

    ui_Label2 = lv_label_create(ui_Button1);

    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label2, 0);
    lv_obj_set_y(ui_Label2, 0);

    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label2, "Abrir pantalla 2");

    // ui_Chart3

    ui_Chart3 = lv_chart_create(ui_Menu);

    lv_obj_set_width(ui_Chart3, 180);
    lv_obj_set_height(ui_Chart3, 100);

    lv_obj_set_x(ui_Chart3, -123);
    lv_obj_set_y(ui_Chart3, 64);

    lv_obj_set_align(ui_Chart3, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_Chart3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chart3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Chart3, lv_color_hex(0x665F5F), LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Keyboard1

    ui_Keyboard1 = lv_keyboard_create(ui_Menu);

    lv_obj_set_width(ui_Keyboard1, 457);
    lv_obj_set_height(ui_Keyboard1, 120);

    lv_obj_set_x(ui_Keyboard1, 3);
    lv_obj_set_y(ui_Keyboard1, 94);

    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);

    // ui_Button5

    ui_Button5 = lv_btn_create(ui_Menu);

    lv_obj_set_width(ui_Button5, 100);
    lv_obj_set_height(ui_Button5, 23);

    lv_obj_set_x(ui_Button5, 176);
    lv_obj_set_y(ui_Button5, -18);

    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button5, ui_event_Button5, LV_EVENT_ALL, NULL);

    // ui_Label5

    ui_Label5 = lv_label_create(ui_Button5);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5, 0);

    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label5, "Teclado");

    // ui_TextArea2

    ui_TextArea2 = lv_textarea_create(ui_Menu);

    lv_obj_set_width(ui_TextArea2, 150);
    lv_obj_set_height(ui_TextArea2, 70);

    lv_obj_set_x(ui_TextArea2, 151);
    lv_obj_set_y(ui_TextArea2, -72);

    lv_obj_set_align(ui_TextArea2, LV_ALIGN_CENTER);

    if("" == "") lv_textarea_set_accepted_chars(ui_TextArea2, NULL);
    else lv_textarea_set_accepted_chars(ui_TextArea2, "");

    lv_textarea_set_text(ui_TextArea2, "");
    lv_textarea_set_placeholder_text(ui_TextArea2, "Placeholder...");

    lv_obj_add_event_cb(ui_TextArea2, ui_event_TextArea2, LV_EVENT_ALL, NULL);

    // ui_PanelNotificacion1

    ui_PanelNotificacion1 = lv_obj_create(ui_Menu);

    lv_obj_set_width(ui_PanelNotificacion1, 467);
    lv_obj_set_height(ui_PanelNotificacion1, 29);

    lv_obj_set_x(ui_PanelNotificacion1, 0);
    lv_obj_set_y(ui_PanelNotificacion1, -141);

    lv_obj_set_align(ui_PanelNotificacion1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_PanelNotificacion1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ButtonAjustes1

    ui_ButtonAjustes1 = lv_btn_create(ui_PanelNotificacion1);

    lv_obj_set_width(ui_ButtonAjustes1, 28);
    lv_obj_set_height(ui_ButtonAjustes1, 25);

    lv_obj_set_x(ui_ButtonAjustes1, 0);
    lv_obj_set_y(ui_ButtonAjustes1, 0);

    lv_obj_set_align(ui_ButtonAjustes1, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(ui_ButtonAjustes1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonAjustes1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_ButtonAjustes1, ui_event_ButtonAjustes1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_ButtonAjustes1, lv_color_hex(0x3827C2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAjustes1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label3

    ui_Label3 = lv_label_create(ui_ButtonAjustes1);

    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label3, 0);
    lv_obj_set_y(ui_Label3, 0);

    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label3, "A");

    // ui_Label8

    ui_Label8 = lv_label_create(ui_PanelNotificacion1);

    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label8, 0);
    lv_obj_set_y(ui_Label8, 0);

    lv_obj_set_align(ui_Label8, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label8, "9:50 pm");

    // ui_Label9

    ui_Label9 = lv_label_create(ui_PanelNotificacion1);

    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label9, 0);
    lv_obj_set_y(ui_Label9, 0);

    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label9, "Menu Principal");

    lv_obj_set_style_text_color(ui_Label9, lv_color_hex(0x27B4C2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Ajustes_screen_init(void)
{

    // ui_Ajustes

    ui_Ajustes = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Ajustes, LV_OBJ_FLAG_SCROLLABLE);

    // ui_PanelNotificacion

    ui_PanelNotificacion = lv_obj_create(ui_Ajustes);

    lv_obj_set_width(ui_PanelNotificacion, 467);
    lv_obj_set_height(ui_PanelNotificacion, 29);

    lv_obj_set_x(ui_PanelNotificacion, 0);
    lv_obj_set_y(ui_PanelNotificacion, -141);

    lv_obj_set_align(ui_PanelNotificacion, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_PanelNotificacion, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ButtonAjustes

    ui_ButtonAjustes = lv_btn_create(ui_PanelNotificacion);

    lv_obj_set_width(ui_ButtonAjustes, 28);
    lv_obj_set_height(ui_ButtonAjustes, 25);

    lv_obj_set_x(ui_ButtonAjustes, 0);
    lv_obj_set_y(ui_ButtonAjustes, 0);

    lv_obj_set_align(ui_ButtonAjustes, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(ui_ButtonAjustes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonAjustes, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_ButtonAjustes, ui_event_ButtonAjustes, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_ButtonAjustes, lv_color_hex(0x3827C2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAjustes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label4

    ui_Label4 = lv_label_create(ui_ButtonAjustes);

    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label4, 0);
    lv_obj_set_y(ui_Label4, 0);

    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label4, LV_SYMBOL_POWER);
    lv_label_set_recolor(ui_Label4, "true");

    // ui_Label6

    ui_Label6 = lv_label_create(ui_PanelNotificacion);

    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label6, 0);
    lv_obj_set_y(ui_Label6, 0);

    lv_obj_set_align(ui_Label6, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label6, "9:50 pm");

    // ui_Label7

    ui_Label7 = lv_label_create(ui_PanelNotificacion);

    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label7, 0);
    lv_obj_set_y(ui_Label7, 0);

    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label7, "Ajustes");

    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x27B4C2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Panel2

    ui_Panel2 = lv_obj_create(ui_Ajustes);

    lv_obj_set_width(ui_Panel2, 118);
    lv_obj_set_height(ui_Panel2, 234);

    lv_obj_set_x(ui_Panel2, -173);
    lv_obj_set_y(ui_Panel2, 2);

    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x292831), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Roller2

    ui_Roller2 = lv_roller_create(ui_Panel2);
    lv_roller_set_options(ui_Roller2, "WiFi\nBluetooth\nSonido\nPantalla", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_height(ui_Roller2, 214);
    lv_obj_set_width(ui_Roller2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Roller2, 2);
    lv_obj_set_y(ui_Roller2, -1);

    lv_obj_set_align(ui_Roller2, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_Roller2, ui_event_Roller2, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_Roller2, lv_color_hex(0x504E5F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Roller2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_PanelWifi

    ui_PanelWifi = lv_obj_create(ui_Ajustes);

    lv_obj_set_width(ui_PanelWifi, 335);
    lv_obj_set_height(ui_PanelWifi, 261);

    lv_obj_set_x(ui_PanelWifi, 61);
    lv_obj_set_y(ui_PanelWifi, 15);

    lv_obj_set_align(ui_PanelWifi, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_PanelWifi, LV_OBJ_FLAG_SCROLLABLE);

    // ui_panelActivacionWifi

    ui_panelActivacionWifi = lv_obj_create(ui_PanelWifi);

    lv_obj_set_width(ui_panelActivacionWifi, 312);
    lv_obj_set_height(ui_panelActivacionWifi, 34);

    lv_obj_set_x(ui_panelActivacionWifi, 0);
    lv_obj_set_y(ui_panelActivacionWifi, -104);

    lv_obj_set_align(ui_panelActivacionWifi, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_panelActivacionWifi, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_panelActivacionWifi, lv_color_hex(0x159D5A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_panelActivacionWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_panelActivacionWifi, lv_color_hex(0x1FD5F6), LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Switch1

    ui_Switch1 = lv_switch_create(ui_panelActivacionWifi);

    lv_obj_set_width(ui_Switch1, 50);
    lv_obj_set_height(ui_Switch1, 25);

    lv_obj_set_x(ui_Switch1, 0);
    lv_obj_set_y(ui_Switch1, 0);

    lv_obj_set_align(ui_Switch1, LV_ALIGN_RIGHT_MID);

    lv_obj_add_event_cb(ui_Switch1, ui_event_Switch1, LV_EVENT_ALL, NULL);

    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0x66BC30), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_color(ui_Switch1, lv_color_hex(0x458D18), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui_Switch1, LV_GRAD_DIR_VER, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // ui_Label10

    ui_Label10 = lv_label_create(ui_panelActivacionWifi);

    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label10, 0);
    lv_obj_set_y(ui_Label10, 0);

    lv_obj_set_align(ui_Label10, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label10, "Desactivado");

    // ui_Spinner1

    ui_Spinner1 = lv_spinner_create(ui_panelActivacionWifi, 1000, 90);

    lv_obj_set_width(ui_Spinner1, 25);
    lv_obj_set_height(ui_Spinner1, 25);

    lv_obj_set_x(ui_Spinner1, 64);
    lv_obj_set_y(ui_Spinner1, 0);

    lv_obj_set_align(ui_Spinner1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Spinner1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Spinner1, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_style_arc_color(ui_Spinner1, lv_color_hex(0x5D9D15), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Spinner1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Spinner1, 7, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_Image3

    ui_Image3 = lv_img_create(ui_PanelWifi);
    lv_img_set_src(ui_Image3, &ui_img_818450103);

    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image3, 50);
    lv_obj_set_y(ui_Image3, 33);

    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Slider1

    ui_Slider1 = lv_slider_create(ui_PanelWifi);
    lv_slider_set_range(ui_Slider1, 0, 100);

    lv_obj_set_width(ui_Slider1, 150);
    lv_obj_set_height(ui_Slider1, 10);

    lv_obj_set_x(ui_Slider1, -69);
    lv_obj_set_y(ui_Slider1, -71);

    lv_obj_set_align(ui_Slider1, LV_ALIGN_CENTER);

    // ui_Label16

    ui_Label16 = lv_label_create(ui_PanelWifi);

    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label16, 0);
    lv_obj_set_y(ui_Label16, 0);

    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label16, "Text");

    // ui_PanelBluetooth

    ui_PanelBluetooth = lv_obj_create(ui_Ajustes);

    lv_obj_set_width(ui_PanelBluetooth, 329);
    lv_obj_set_height(ui_PanelBluetooth, 259);

    lv_obj_set_x(ui_PanelBluetooth, 64);
    lv_obj_set_y(ui_PanelBluetooth, 15);

    lv_obj_set_align(ui_PanelBluetooth, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_PanelBluetooth, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_PanelBluetooth, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ButtonAtras

    ui_ButtonAtras = lv_btn_create(ui_Ajustes);

    lv_obj_set_width(ui_ButtonAtras, 67);
    lv_obj_set_height(ui_ButtonAtras, 26);

    lv_obj_set_x(ui_ButtonAtras, -197);
    lv_obj_set_y(ui_ButtonAtras, 140);

    lv_obj_set_align(ui_ButtonAtras, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonAtras, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonAtras, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_ButtonAtras, ui_event_ButtonAtras, LV_EVENT_ALL, NULL);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_ButtonAtras);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, 0);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "Salir");

    // ui_PanelMenuPower

    ui_PanelMenuPower = lv_obj_create(ui_Ajustes);

    lv_obj_set_width(ui_PanelMenuPower, 282);
    lv_obj_set_height(ui_PanelMenuPower, 99);

    lv_obj_set_x(ui_PanelMenuPower, 8);
    lv_obj_set_y(ui_PanelMenuPower, 10);

    lv_obj_set_align(ui_PanelMenuPower, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_PanelMenuPower, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_FLOATING);
    lv_obj_clear_flag(ui_PanelMenuPower, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_PanelMenuPower, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_PanelMenuPower, lv_color_hex(0x5A5D5D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_PanelMenuPower, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_PanelMenuPower, 300, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_ButtonApagar

    ui_ButtonApagar = lv_btn_create(ui_PanelMenuPower);

    lv_obj_set_width(ui_ButtonApagar, 71);
    lv_obj_set_height(ui_ButtonApagar, 69);

    lv_obj_set_x(ui_ButtonApagar, -90);
    lv_obj_set_y(ui_ButtonApagar, -7);

    lv_obj_set_align(ui_ButtonApagar, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(ui_ButtonApagar, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonApagar, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_ButtonApagar, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonApagar, lv_color_hex(0xBA1818), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonApagar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label11

    ui_Label11 = lv_label_create(ui_ButtonApagar);

    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label11, 0);
    lv_obj_set_y(ui_Label11, 0);

    lv_obj_set_align(ui_Label11, LV_ALIGN_BOTTOM_MID);

    lv_label_set_text(ui_Label11, "Apagar");

    // ui_Label14

    ui_Label14 = lv_label_create(ui_ButtonApagar);

    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label14, 0);
    lv_obj_set_y(ui_Label14, 0);

    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label14, LV_SYMBOL_POWER);

    // ui_ButtonReiniciar

    ui_ButtonReiniciar = lv_btn_create(ui_PanelMenuPower);

    lv_obj_set_width(ui_ButtonReiniciar, 74);
    lv_obj_set_height(ui_ButtonReiniciar, 67);

    lv_obj_set_x(ui_ButtonReiniciar, 0);
    lv_obj_set_y(ui_ButtonReiniciar, -5);

    lv_obj_set_align(ui_ButtonReiniciar, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(ui_ButtonReiniciar, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonReiniciar, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_ButtonReiniciar, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonReiniciar, lv_color_hex(0xFF7920), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonReiniciar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label12

    ui_Label12 = lv_label_create(ui_ButtonReiniciar);

    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label12, 0);
    lv_obj_set_y(ui_Label12, 0);

    lv_obj_set_align(ui_Label12, LV_ALIGN_BOTTOM_MID);

    lv_label_set_text(ui_Label12, "Reiniciar");

    // ui_Label15

    ui_Label15 = lv_label_create(ui_ButtonReiniciar);

    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label15, 0);
    lv_obj_set_y(ui_Label15, 0);

    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label15, LV_SYMBOL_REFRESH);

    // ui_ButtonSalirPower

    ui_ButtonSalirPower = lv_btn_create(ui_PanelMenuPower);

    lv_obj_set_width(ui_ButtonSalirPower, 73);
    lv_obj_set_height(ui_ButtonSalirPower, 72);

    lv_obj_set_x(ui_ButtonSalirPower, 88);
    lv_obj_set_y(ui_ButtonSalirPower, -7);

    lv_obj_set_align(ui_ButtonSalirPower, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(ui_ButtonSalirPower, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonSalirPower, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_ButtonSalirPower, ui_event_ButtonSalirPower, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_ButtonSalirPower, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonSalirPower, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonSalirPower, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label13

    ui_Label13 = lv_label_create(ui_ButtonSalirPower);

    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label13, 0);
    lv_obj_set_y(ui_Label13, 0);

    lv_obj_set_align(ui_Label13, LV_ALIGN_BOTTOM_MID);

    lv_label_set_text(ui_Label13, "Salir");

    // ui_Label17

    ui_Label17 = lv_label_create(ui_ButtonSalirPower);

    lv_obj_set_width(ui_Label17, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label17, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label17, 0);
    lv_obj_set_y(ui_Label17, 0);

    lv_obj_set_align(ui_Label17, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label17, LV_SYMBOL_CLOSE);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Menu_screen_init();
    ui_Ajustes_screen_init();
    lv_disp_load_scr(ui_Menu);
}

