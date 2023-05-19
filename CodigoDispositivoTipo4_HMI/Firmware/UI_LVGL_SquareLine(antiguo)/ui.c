// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: HMI_LVGL

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Principal;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui_BarraNotificaciones;
lv_obj_t * ui_Button2;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Button8;
lv_obj_t * ui_Label12;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Label11;
lv_obj_t * ui_PanelDeAcueducto;
lv_obj_t * ui_ButtonDisp1A;
lv_obj_t * ui_Label1;
lv_obj_t * ui_ButtonDisp2;
lv_obj_t * ui_Label7;
lv_obj_t * ui_ButtonDisp3;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Button9;
lv_obj_t * ui_Label14;
lv_obj_t * ui_ButtonDisp1B;
lv_obj_t * ui_Label9;
lv_obj_t * ui_ButtonFMicroz;
lv_obj_t * ui_Label15;
lv_obj_t * ui_ButtonPulido;
lv_obj_t * ui_Label17;
lv_obj_t * ui_Button13;
lv_obj_t * ui_Label18;
lv_obj_t * ui_Button15;
lv_obj_t * ui_Label19;
lv_obj_t * ui_ButtonAlmacenamiento;
lv_obj_t * ui_Label20;
lv_obj_t * ui_Button17;
lv_obj_t * ui_Label21;
lv_obj_t * ui_ButtonTanqDist;
lv_obj_t * ui_Label22;
lv_obj_t * ui_ButtonBombeo;
lv_obj_t * ui_Label23;
lv_obj_t * ui_Button20;
lv_obj_t * ui_Label24;
lv_obj_t * ui_Label25;
lv_obj_t * ui_Button21;
lv_obj_t * ui_Label27;
lv_obj_t * ui_ButtonFFeMn;
lv_obj_t * ui_Label16;
lv_obj_t * ui_Label26;
lv_obj_t * ui_Ajustes;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Principal_screen_init(void)
{

    // ui_Principal

    ui_Principal = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Principal, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Keyboard1

    ui_Keyboard1 = lv_keyboard_create(ui_Principal);

    lv_obj_set_width(ui_Keyboard1, 460);
    lv_obj_set_height(ui_Keyboard1, 120);

    lv_obj_set_x(ui_Keyboard1, 0);
    lv_obj_set_y(ui_Keyboard1, 88);

    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);

    // ui_BarraNotificaciones

    ui_BarraNotificaciones = lv_obj_create(ui_Principal);

    lv_obj_set_width(ui_BarraNotificaciones, 465);
    lv_obj_set_height(ui_BarraNotificaciones, 33);

    lv_obj_set_x(ui_BarraNotificaciones, 0);
    lv_obj_set_y(ui_BarraNotificaciones, -137);

    lv_obj_set_align(ui_BarraNotificaciones, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_BarraNotificaciones, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Button2

    ui_Button2 = lv_btn_create(ui_BarraNotificaciones);

    lv_obj_set_width(ui_Button2, 25);
    lv_obj_set_height(ui_Button2, 25);

    lv_obj_set_x(ui_Button2, 0);
    lv_obj_set_y(ui_Button2, 0);

    lv_obj_set_align(ui_Button2, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label5

    ui_Label5 = lv_label_create(ui_Button2);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5, 0);

    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label5, "A");

    // ui_Button8

    ui_Button8 = lv_btn_create(ui_BarraNotificaciones);

    lv_obj_set_width(ui_Button8, 25);
    lv_obj_set_height(ui_Button8, 25);

    lv_obj_set_x(ui_Button8, -35);
    lv_obj_set_y(ui_Button8, 0);

    lv_obj_set_align(ui_Button8, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(ui_Button8, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button8, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label12

    ui_Label12 = lv_label_create(ui_Button8);

    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label12, 0);
    lv_obj_set_y(ui_Label12, 0);

    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label12, "M");

    // ui_Label6

    ui_Label6 = lv_label_create(ui_BarraNotificaciones);

    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label6, 0);
    lv_obj_set_y(ui_Label6, 0);

    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label6, "Sistema General");

    // ui_Label11

    ui_Label11 = lv_label_create(ui_BarraNotificaciones);

    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label11, 0);
    lv_obj_set_y(ui_Label11, 0);

    lv_obj_set_align(ui_Label11, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label11, "hh:mm");

    // ui_PanelDeAcueducto

    ui_PanelDeAcueducto = lv_obj_create(ui_Principal);

    lv_obj_set_width(ui_PanelDeAcueducto, 460);
    lv_obj_set_height(ui_PanelDeAcueducto, 267);

    lv_obj_set_x(ui_PanelDeAcueducto, -1);
    lv_obj_set_y(ui_PanelDeAcueducto, 21);

    lv_obj_set_align(ui_PanelDeAcueducto, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_PanelDeAcueducto, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ButtonDisp1A

    ui_ButtonDisp1A = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonDisp1A, 30);
    lv_obj_set_height(ui_ButtonDisp1A, 30);

    lv_obj_set_x(ui_ButtonDisp1A, 33);
    lv_obj_set_y(ui_ButtonDisp1A, 108);

    lv_obj_set_align(ui_ButtonDisp1A, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonDisp1A, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonDisp1A, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonDisp1A, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp1A, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_ButtonDisp1A);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, 0);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "1A");

    // ui_ButtonDisp2

    ui_ButtonDisp2 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonDisp2, 30);
    lv_obj_set_height(ui_ButtonDisp2, 30);

    lv_obj_set_x(ui_ButtonDisp2, -97);
    lv_obj_set_y(ui_ButtonDisp2, -109);

    lv_obj_set_align(ui_ButtonDisp2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonDisp2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonDisp2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonDisp2, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label7

    ui_Label7 = lv_label_create(ui_ButtonDisp2);

    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label7, 0);
    lv_obj_set_y(ui_Label7, 0);

    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label7, "2");

    // ui_ButtonDisp3

    ui_ButtonDisp3 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonDisp3, 30);
    lv_obj_set_height(ui_ButtonDisp3, 30);

    lv_obj_set_x(ui_ButtonDisp3, 192);
    lv_obj_set_y(ui_ButtonDisp3, 24);

    lv_obj_set_align(ui_ButtonDisp3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonDisp3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonDisp3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonDisp3, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label8

    ui_Label8 = lv_label_create(ui_ButtonDisp3);

    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label8, 0);
    lv_obj_set_y(ui_Label8, 0);

    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label8, "3");

    // ui_Button9

    ui_Button9 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Button9, 50);
    lv_obj_set_height(ui_Button9, 100);

    lv_obj_set_x(ui_Button9, -196);
    lv_obj_set_y(ui_Button9, 76);

    lv_obj_set_align(ui_Button9, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button9, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button9, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Button9, lv_color_hex(0xD2B31A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Button9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Button9, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label14

    ui_Label14 = lv_label_create(ui_Button9);

    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label14, 0);
    lv_obj_set_y(ui_Label14, 0);

    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label14, "Pozo");

    // ui_ButtonDisp1B

    ui_ButtonDisp1B = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonDisp1B, 30);
    lv_obj_set_height(ui_ButtonDisp1B, 30);

    lv_obj_set_x(ui_ButtonDisp1B, -70);
    lv_obj_set_y(ui_ButtonDisp1B, -64);

    lv_obj_set_align(ui_ButtonDisp1B, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonDisp1B, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonDisp1B, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonDisp1B, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp1B, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label9

    ui_Label9 = lv_label_create(ui_ButtonDisp1B);

    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label9, 0);
    lv_obj_set_y(ui_Label9, 0);

    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label9, "1B");

    // ui_ButtonFMicroz

    ui_ButtonFMicroz = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonFMicroz, 79);
    lv_obj_set_height(ui_ButtonFMicroz, 50);

    lv_obj_set_x(ui_ButtonFMicroz, -155);
    lv_obj_set_y(ui_ButtonFMicroz, -62);

    lv_obj_set_align(ui_ButtonFMicroz, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonFMicroz, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonFMicroz, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonFMicroz, lv_color_hex(0x09A115), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonFMicroz, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label15

    ui_Label15 = lv_label_create(ui_ButtonFMicroz);

    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label15, 0);
    lv_obj_set_y(ui_Label15, 0);

    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label15, "Filtro\nMicro Z");

    // ui_ButtonPulido

    ui_ButtonPulido = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonPulido, 62);
    lv_obj_set_height(ui_ButtonPulido, 50);

    lv_obj_set_x(ui_ButtonPulido, 75);
    lv_obj_set_y(ui_ButtonPulido, -61);

    lv_obj_set_align(ui_ButtonPulido, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonPulido, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonPulido, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonPulido, lv_color_hex(0xE2D415), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPulido, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label17

    ui_Label17 = lv_label_create(ui_ButtonPulido);

    lv_obj_set_width(ui_Label17, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label17, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label17, 0);
    lv_obj_set_y(ui_Label17, 0);

    lv_obj_set_align(ui_Label17, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label17, "Pulido");

    // ui_Button13

    ui_Button13 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Button13, 30);
    lv_obj_set_height(ui_Button13, 30);

    lv_obj_set_x(ui_Button13, -175);
    lv_obj_set_y(ui_Button13, -5);

    lv_obj_set_align(ui_Button13, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button13, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button13, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Button13, lv_color_hex(0x5A32FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label18

    ui_Label18 = lv_label_create(ui_Button13);

    lv_obj_set_width(ui_Label18, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label18, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label18, 0);
    lv_obj_set_y(ui_Label18, 0);

    lv_obj_set_align(ui_Label18, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label18, "Cl");

    // ui_Button15

    ui_Button15 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Button15, 30);
    lv_obj_set_height(ui_Button15, 30);

    lv_obj_set_x(ui_Button15, 157);
    lv_obj_set_y(ui_Button15, -112);

    lv_obj_set_align(ui_Button15, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button15, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button15, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Button15, lv_color_hex(0x5A32FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label19

    ui_Label19 = lv_label_create(ui_Button15);

    lv_obj_set_width(ui_Label19, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label19, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label19, 0);
    lv_obj_set_y(ui_Label19, 0);

    lv_obj_set_align(ui_Label19, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label19, "Cl");

    // ui_ButtonAlmacenamiento

    ui_ButtonAlmacenamiento = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonAlmacenamiento, 79);
    lv_obj_set_height(ui_ButtonAlmacenamiento, 50);

    lv_obj_set_x(ui_ButtonAlmacenamiento, 175);
    lv_obj_set_y(ui_ButtonAlmacenamiento, -63);

    lv_obj_set_align(ui_ButtonAlmacenamiento, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonAlmacenamiento, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonAlmacenamiento, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label20

    ui_Label20 = lv_label_create(ui_ButtonAlmacenamiento);

    lv_obj_set_width(ui_Label20, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label20, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label20, 0);
    lv_obj_set_y(ui_Label20, 0);

    lv_obj_set_align(ui_Label20, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label20, "Almace-\nnamiento");

    lv_obj_set_style_text_font(ui_Label20, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button17

    ui_Button17 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Button17, 50);
    lv_obj_set_height(ui_Button17, 50);

    lv_obj_set_x(ui_Button17, -140);
    lv_obj_set_y(ui_Button17, 100);

    lv_obj_set_align(ui_Button17, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button17, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button17, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label21

    ui_Label21 = lv_label_create(ui_Button17);

    lv_obj_set_width(ui_Label21, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label21, 0);
    lv_obj_set_y(ui_Label21, 0);

    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label21, "Agua\nMuni.");

    // ui_ButtonTanqDist

    ui_ButtonTanqDist = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonTanqDist, 71);
    lv_obj_set_height(ui_ButtonTanqDist, 44);

    lv_obj_set_x(ui_ButtonTanqDist, -41);
    lv_obj_set_y(ui_ButtonTanqDist, 57);

    lv_obj_set_align(ui_ButtonTanqDist, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonTanqDist, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonTanqDist, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label22

    ui_Label22 = lv_label_create(ui_ButtonTanqDist);

    lv_obj_set_width(ui_Label22, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label22, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label22, 0);
    lv_obj_set_y(ui_Label22, 0);

    lv_obj_set_align(ui_Label22, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label22, "Tanque\ndistrib.");

    // ui_ButtonBombeo

    ui_ButtonBombeo = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_ButtonBombeo, 73);
    lv_obj_set_height(ui_ButtonBombeo, 42);

    lv_obj_set_x(ui_ButtonBombeo, 42);
    lv_obj_set_y(ui_ButtonBombeo, 57);

    lv_obj_set_align(ui_ButtonBombeo, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonBombeo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonBombeo, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonBombeo, lv_color_hex(0xC81496), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonBombeo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label23

    ui_Label23 = lv_label_create(ui_ButtonBombeo);

    lv_obj_set_width(ui_Label23, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label23, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label23, 0);
    lv_obj_set_y(ui_Label23, 0);

    lv_obj_set_align(ui_Label23, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label23, "Bombeo");

    // ui_Button20

    ui_Button20 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Button20, 53);
    lv_obj_set_height(ui_Button20, 50);

    lv_obj_set_x(ui_Button20, 196);
    lv_obj_set_y(ui_Button20, 99);

    lv_obj_set_align(ui_Button20, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button20, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button20, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Button20, lv_color_hex(0x813C15), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button20, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label24

    ui_Label24 = lv_label_create(ui_Button20);

    lv_obj_set_width(ui_Label24, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label24, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label24, 0);
    lv_obj_set_y(ui_Label24, 0);

    lv_obj_set_align(ui_Label24, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label24, "Red\ndistr.");

    // ui_Label25

    ui_Label25 = lv_label_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Label25, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label25, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label25, 24);
    lv_obj_set_y(ui_Label25, -117);

    lv_obj_set_align(ui_Label25, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label25, "Potabilizacion");

    // ui_Button21

    ui_Button21 = lv_btn_create(ui_PanelDeAcueducto);

    lv_obj_set_width(ui_Button21, 57);
    lv_obj_set_height(ui_Button21, 42);

    lv_obj_set_x(ui_Button21, 121);
    lv_obj_set_y(ui_Button21, 56);

    lv_obj_set_align(ui_Button21, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button21, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button21, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Button21, lv_color_hex(0xE2D415), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button21, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label27

    ui_Label27 = lv_label_create(ui_Button21);

    lv_obj_set_width(ui_Label27, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label27, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label27, 0);
    lv_obj_set_y(ui_Label27, 0);

    lv_obj_set_align(ui_Label27, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label27, "Pulido\nfinal");

    lv_obj_set_style_text_align(ui_Label27, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_ButtonFFeMn

    ui_ButtonFFeMn = lv_btn_create(ui_Principal);

    lv_obj_set_width(ui_ButtonFFeMn, 78);
    lv_obj_set_height(ui_ButtonFFeMn, 50);

    lv_obj_set_x(ui_ButtonFFeMn, -8);
    lv_obj_set_y(ui_ButtonFFeMn, -42);

    lv_obj_set_align(ui_ButtonFFeMn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ButtonFFeMn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonFFeMn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ButtonFFeMn, lv_color_hex(0x09A115), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonFFeMn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label16

    ui_Label16 = lv_label_create(ui_ButtonFFeMn);

    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label16, 0);
    lv_obj_set_y(ui_Label16, 0);

    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label16, "Filtro de\nFe y Mn");

    lv_obj_set_style_text_align(ui_Label16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label26

    ui_Label26 = lv_label_create(ui_Principal);

    lv_obj_set_width(ui_Label26, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label26, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label26, 35);
    lv_obj_set_y(ui_Label26, 38);

    lv_obj_set_align(ui_Label26, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label26, "Distribucion");

}
void ui_Ajustes_screen_init(void)
{

    // ui_Ajustes

    ui_Ajustes = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Ajustes, LV_OBJ_FLAG_SCROLLABLE);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Principal_screen_init();
    ui_Ajustes_screen_init();
    lv_disp_load_scr(ui_Principal);
}

