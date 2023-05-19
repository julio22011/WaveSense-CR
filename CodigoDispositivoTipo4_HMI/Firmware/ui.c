// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: HMI_LVGL

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Principal;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui_BarraNotificaciones;
void ui_event_ButtonAjustes(lv_event_t * e);
lv_obj_t * ui_ButtonAjustes;
lv_obj_t * ui_LabelBotonAjustes;
void ui_event_ButtonMesh(lv_event_t * e);
lv_obj_t * ui_ButtonMesh;
lv_obj_t * ui_LabelBotonMesh;
lv_obj_t * ui_Label6;
lv_obj_t * ui_LabelHora;
lv_obj_t * ui_PanelDeAcueducto;
lv_obj_t * ui_ButtonDisp1A;
lv_obj_t * ui_Label1;
void ui_event_ButtonDisp2(lv_event_t * e);
lv_obj_t * ui_ButtonDisp2;
lv_obj_t * ui_Label7;
lv_obj_t * ui_ButtonDisp3;
lv_obj_t * ui_Label8;
void ui_event_Button9(lv_event_t * e);
lv_obj_t * ui_Button9;
lv_obj_t * ui_Label14;
lv_obj_t * ui_ButtonDisp1B;
lv_obj_t * ui_Label9;
void ui_event_ButtonFMicroz(lv_event_t * e);
lv_obj_t * ui_ButtonFMicroz;
lv_obj_t * ui_Label15;
lv_obj_t * ui_ButtonPulido;
lv_obj_t * ui_Label17;
lv_obj_t * ui_ButtonCloro2;
lv_obj_t * ui_Label18;
lv_obj_t * ui_ButtonCloro1;
lv_obj_t * ui_Label19;
lv_obj_t * ui_ButtonAlmacenamiento;
lv_obj_t * ui_Label20;
lv_obj_t * ui_ButtonAguaMuni;
lv_obj_t * ui_Label21;
lv_obj_t * ui_ButtonTanqDist;
lv_obj_t * ui_Label22;
lv_obj_t * ui_ButtonRedDist;
lv_obj_t * ui_Label24;
lv_obj_t * ui_Label25;
lv_obj_t * ui_ButtonFFeMn;
lv_obj_t * ui_Label16;
lv_obj_t * ui_ButtonPulidoFinal;
lv_obj_t * ui_Label27;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label26;
lv_obj_t * ui_ImgButton2;
lv_obj_t * ui_Spinner1;
lv_obj_t * ui_ScreenMicroZ;
void ui_event_Button1(lv_event_t * e);
lv_obj_t * ui_Button1;
lv_obj_t * ui_Label2;
void ui_event_ButtonFiltro1(lv_event_t * e);
lv_obj_t * ui_ButtonFiltro1;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Label3;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_ButtonAjustes(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        abrirVentanaDeConfiguracion(e);
    }
}
void ui_event_ButtonMesh(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        abrirConfigWiFi(e);
    }
}
void ui_event_ButtonDisp2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenMicroZ, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
void ui_event_Button9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        accionBotonPozo(e);
    }
}
void ui_event_ButtonFMicroz(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenMicroZ, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Principal, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
    }
}
void ui_event_ButtonFiltro1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        abrirPantllaDispTipo2(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Principal_screen_init(void)
{
    ui_Principal = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Principal, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Keyboard1 = lv_keyboard_create(ui_Principal);
    lv_obj_set_width(ui_Keyboard1, 460);
    lv_obj_set_height(ui_Keyboard1, 120);
    lv_obj_set_x(ui_Keyboard1, 0);
    lv_obj_set_y(ui_Keyboard1, 88);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_BarraNotificaciones = lv_obj_create(ui_Principal);
    lv_obj_set_width(ui_BarraNotificaciones, 465);
    lv_obj_set_height(ui_BarraNotificaciones, 33);
    lv_obj_set_x(ui_BarraNotificaciones, 0);
    lv_obj_set_y(ui_BarraNotificaciones, -137);
    lv_obj_set_align(ui_BarraNotificaciones, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BarraNotificaciones, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ButtonAjustes = lv_btn_create(ui_BarraNotificaciones);
    lv_obj_set_width(ui_ButtonAjustes, 25);
    lv_obj_set_height(ui_ButtonAjustes, 25);
    lv_obj_set_align(ui_ButtonAjustes, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_ButtonAjustes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAjustes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAjustes, lv_color_hex(0x5C00A2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAjustes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelBotonAjustes = lv_label_create(ui_ButtonAjustes);
    lv_obj_set_width(ui_LabelBotonAjustes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelBotonAjustes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelBotonAjustes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelBotonAjustes, "A");

    ui_ButtonMesh = lv_btn_create(ui_BarraNotificaciones);
    lv_obj_set_width(ui_ButtonMesh, 25);
    lv_obj_set_height(ui_ButtonMesh, 25);
    lv_obj_set_x(ui_ButtonMesh, -35);
    lv_obj_set_y(ui_ButtonMesh, 0);
    lv_obj_set_align(ui_ButtonMesh, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_ButtonMesh, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonMesh, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelBotonMesh = lv_label_create(ui_ButtonMesh);
    lv_obj_set_width(ui_LabelBotonMesh, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelBotonMesh, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelBotonMesh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelBotonMesh, "M");

    ui_Label6 = lv_label_create(ui_BarraNotificaciones);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Sistema General");

    ui_LabelHora = lv_label_create(ui_BarraNotificaciones);
    lv_obj_set_width(ui_LabelHora, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelHora, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelHora, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_LabelHora, "hh:mm");

    ui_PanelDeAcueducto = lv_obj_create(ui_Principal);
    lv_obj_set_width(ui_PanelDeAcueducto, 460);
    lv_obj_set_height(ui_PanelDeAcueducto, 267);
    lv_obj_set_x(ui_PanelDeAcueducto, -1);
    lv_obj_set_y(ui_PanelDeAcueducto, 21);
    lv_obj_set_align(ui_PanelDeAcueducto, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelDeAcueducto, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_PanelDeAcueducto, &ui_img_background2_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonDisp1A = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonDisp1A, 30);
    lv_obj_set_height(ui_ButtonDisp1A, 30);
    lv_obj_set_x(ui_ButtonDisp1A, -60);
    lv_obj_set_y(ui_ButtonDisp1A, 111);
    lv_obj_set_align(ui_ButtonDisp1A, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonDisp1A, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonDisp1A, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonDisp1A, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp1A, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_ButtonDisp1A);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "1A");

    ui_ButtonDisp2 = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonDisp2, 30);
    lv_obj_set_height(ui_ButtonDisp2, 30);
    lv_obj_set_x(ui_ButtonDisp2, -97);
    lv_obj_set_y(ui_ButtonDisp2, -109);
    lv_obj_set_align(ui_ButtonDisp2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonDisp2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonDisp2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonDisp2, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_ButtonDisp2);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "2");

    ui_ButtonDisp3 = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonDisp3, 30);
    lv_obj_set_height(ui_ButtonDisp3, 30);
    lv_obj_set_x(ui_ButtonDisp3, 192);
    lv_obj_set_y(ui_ButtonDisp3, 24);
    lv_obj_set_align(ui_ButtonDisp3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonDisp3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonDisp3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonDisp3, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_ButtonDisp3);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "3");

    ui_Button9 = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_Button9, 50);
    lv_obj_set_height(ui_Button9, 100);
    lv_obj_set_x(ui_Button9, -196);
    lv_obj_set_y(ui_Button9, 76);
    lv_obj_set_align(ui_Button9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button9, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button9, lv_color_hex(0xA00000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Button9, lv_color_hex(0xA07B00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Button9, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label14 = lv_label_create(ui_Button9);
    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label14, 0);
    lv_obj_set_y(ui_Label14, 2);
    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label14, "Pozo");

    ui_ButtonDisp1B = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonDisp1B, 30);
    lv_obj_set_height(ui_ButtonDisp1B, 30);
    lv_obj_set_x(ui_ButtonDisp1B, -70);
    lv_obj_set_y(ui_ButtonDisp1B, -64);
    lv_obj_set_align(ui_ButtonDisp1B, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonDisp1B, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonDisp1B, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonDisp1B, lv_color_hex(0xC40505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDisp1B, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_ButtonDisp1B);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "1B");

    ui_ButtonFMicroz = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonFMicroz, 79);
    lv_obj_set_height(ui_ButtonFMicroz, 50);
    lv_obj_set_x(ui_ButtonFMicroz, -155);
    lv_obj_set_y(ui_ButtonFMicroz, -62);
    lv_obj_set_align(ui_ButtonFMicroz, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonFMicroz, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonFMicroz, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonFMicroz, lv_color_hex(0x09A115), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonFMicroz, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label15 = lv_label_create(ui_ButtonFMicroz);
    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label15, "Filtro\nMicro Z");
    lv_obj_set_style_text_align(ui_Label15, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPulido = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonPulido, 62);
    lv_obj_set_height(ui_ButtonPulido, 50);
    lv_obj_set_x(ui_ButtonPulido, 75);
    lv_obj_set_y(ui_ButtonPulido, -61);
    lv_obj_set_align(ui_ButtonPulido, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPulido, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPulido, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPulido, lv_color_hex(0xE2D415), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPulido, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label17 = lv_label_create(ui_ButtonPulido);
    lv_obj_set_width(ui_Label17, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label17, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label17, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label17, "Pulido");

    ui_ButtonCloro2 = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonCloro2, 30);
    lv_obj_set_height(ui_ButtonCloro2, 30);
    lv_obj_set_x(ui_ButtonCloro2, -175);
    lv_obj_set_y(ui_ButtonCloro2, -5);
    lv_obj_set_align(ui_ButtonCloro2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonCloro2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonCloro2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonCloro2, lv_color_hex(0x5A32FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonCloro2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label18 = lv_label_create(ui_ButtonCloro2);
    lv_obj_set_width(ui_Label18, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label18, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label18, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label18, "Cl");

    ui_ButtonCloro1 = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonCloro1, 30);
    lv_obj_set_height(ui_ButtonCloro1, 30);
    lv_obj_set_x(ui_ButtonCloro1, 157);
    lv_obj_set_y(ui_ButtonCloro1, -112);
    lv_obj_set_align(ui_ButtonCloro1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonCloro1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonCloro1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonCloro1, lv_color_hex(0x5A32FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonCloro1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label19 = lv_label_create(ui_ButtonCloro1);
    lv_obj_set_width(ui_Label19, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label19, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label19, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label19, "Cl");

    ui_ButtonAlmacenamiento = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonAlmacenamiento, 79);
    lv_obj_set_height(ui_ButtonAlmacenamiento, 50);
    lv_obj_set_x(ui_ButtonAlmacenamiento, 175);
    lv_obj_set_y(ui_ButtonAlmacenamiento, -63);
    lv_obj_set_align(ui_ButtonAlmacenamiento, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonAlmacenamiento, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAlmacenamiento, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label20 = lv_label_create(ui_ButtonAlmacenamiento);
    lv_obj_set_width(ui_Label20, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label20, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label20, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label20, "Almace-\nnamiento");
    lv_obj_set_style_text_font(ui_Label20, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonAguaMuni = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonAguaMuni, 50);
    lv_obj_set_height(ui_ButtonAguaMuni, 100);
    lv_obj_set_x(ui_ButtonAguaMuni, -142);
    lv_obj_set_y(ui_ButtonAguaMuni, 76);
    lv_obj_set_align(ui_ButtonAguaMuni, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonAguaMuni, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAguaMuni, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAguaMuni, lv_color_hex(0x320898), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAguaMuni, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_ButtonAguaMuni, lv_color_hex(0x11C9F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_ButtonAguaMuni, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label21 = lv_label_create(ui_ButtonAguaMuni);
    lv_obj_set_width(ui_Label21, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label21, "Agua\nMuni.");

    ui_ButtonTanqDist = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonTanqDist, 71);
    lv_obj_set_height(ui_ButtonTanqDist, 44);
    lv_obj_set_x(ui_ButtonTanqDist, -41);
    lv_obj_set_y(ui_ButtonTanqDist, 57);
    lv_obj_set_align(ui_ButtonTanqDist, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonTanqDist, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonTanqDist, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label22 = lv_label_create(ui_ButtonTanqDist);
    lv_obj_set_width(ui_Label22, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label22, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label22, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label22, "Tanque\ndistrib.");

    ui_ButtonRedDist = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonRedDist, 53);
    lv_obj_set_height(ui_ButtonRedDist, 50);
    lv_obj_set_x(ui_ButtonRedDist, 196);
    lv_obj_set_y(ui_ButtonRedDist, 99);
    lv_obj_set_align(ui_ButtonRedDist, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonRedDist, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonRedDist, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonRedDist, lv_color_hex(0x813C15), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonRedDist, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label24 = lv_label_create(ui_ButtonRedDist);
    lv_obj_set_width(ui_Label24, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label24, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label24, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label24, "Red\ndistr.");

    ui_Label25 = lv_label_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_Label25, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label25, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label25, 24);
    lv_obj_set_y(ui_Label25, -117);
    lv_obj_set_align(ui_Label25, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label25, "Potabilizacion");

    ui_ButtonFFeMn = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonFFeMn, 78);
    lv_obj_set_height(ui_ButtonFFeMn, 50);
    lv_obj_set_x(ui_ButtonFFeMn, -8);
    lv_obj_set_y(ui_ButtonFFeMn, -63);
    lv_obj_set_align(ui_ButtonFFeMn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonFFeMn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonFFeMn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonFFeMn, lv_color_hex(0x09A115), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonFFeMn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label16 = lv_label_create(ui_ButtonFFeMn);
    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label16, "Filtro de\nFe y Mn");
    lv_obj_set_style_text_align(ui_Label16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPulidoFinal = lv_btn_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_ButtonPulidoFinal, 57);
    lv_obj_set_height(ui_ButtonPulidoFinal, 42);
    lv_obj_set_x(ui_ButtonPulidoFinal, 121);
    lv_obj_set_y(ui_ButtonPulidoFinal, 56);
    lv_obj_set_align(ui_ButtonPulidoFinal, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPulidoFinal, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPulidoFinal, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPulidoFinal, lv_color_hex(0xE2D415), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPulidoFinal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label27 = lv_label_create(ui_ButtonPulidoFinal);
    lv_obj_set_width(ui_Label27, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label27, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label27, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label27, "Pulido\nfinal");
    lv_obj_set_style_text_align(ui_Label27, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label4 = lv_label_create(ui_PanelDeAcueducto);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, 43);
    lv_obj_set_y(ui_Label4, 93);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Bombeo");

    ui_Label26 = lv_label_create(ui_Principal);
    lv_obj_set_width(ui_Label26, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label26, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label26, 39);
    lv_obj_set_y(ui_Label26, 22);
    lv_obj_set_align(ui_Label26, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label26, "Distribucion");

    ui_ImgButton2 = lv_imgbtn_create(ui_Principal);
    lv_imgbtn_set_src(ui_ImgButton2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_175923361, NULL);
    lv_obj_set_height(ui_ImgButton2, 64);
    lv_obj_set_width(ui_ImgButton2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_ImgButton2, 40);
    lv_obj_set_y(ui_ImgButton2, 73);
    lv_obj_set_align(ui_ImgButton2, LV_ALIGN_CENTER);

    ui_Spinner1 = lv_spinner_create(ui_Principal, 1000, 90);
    lv_obj_set_width(ui_Spinner1, 40);
    lv_obj_set_height(ui_Spinner1, 40);
    lv_obj_set_x(ui_Spinner1, 40);
    lv_obj_set_y(ui_Spinner1, 73);
    lv_obj_set_align(ui_Spinner1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Spinner1, LV_OBJ_FLAG_CLICKABLE);      /// Flags

    lv_obj_set_style_arc_width(ui_Spinner1, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ButtonAjustes, ui_event_ButtonAjustes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonMesh, ui_event_ButtonMesh, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonDisp2, ui_event_ButtonDisp2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button9, ui_event_Button9, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonFMicroz, ui_event_ButtonFMicroz, LV_EVENT_ALL, NULL);

}
void ui_ScreenMicroZ_screen_init(void)
{
    ui_ScreenMicroZ = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenMicroZ, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Button1 = lv_btn_create(ui_ScreenMicroZ);
    lv_obj_set_width(ui_Button1, 54);
    lv_obj_set_height(ui_Button1, 33);
    lv_obj_set_x(ui_Button1, -206);
    lv_obj_set_y(ui_Button1, 135);
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label2 = lv_label_create(ui_Button1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Atras");

    ui_ButtonFiltro1 = lv_btn_create(ui_ScreenMicroZ);
    lv_obj_set_width(ui_ButtonFiltro1, 179);
    lv_obj_set_height(ui_ButtonFiltro1, 28);
    lv_obj_set_x(ui_ButtonFiltro1, 144);
    lv_obj_set_y(ui_ButtonFiltro1, 136);
    lv_obj_set_align(ui_ButtonFiltro1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonFiltro1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonFiltro1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label10 = lv_label_create(ui_ButtonFiltro1);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "Abrir panel de control");

    ui_Image1 = lv_img_create(ui_ScreenMicroZ);
    lv_img_set_src(ui_Image1, &ui_img_fotofiltros_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_y(ui_Image1, -45);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label3 = lv_label_create(ui_ScreenMicroZ);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 4);
    lv_obj_set_y(ui_Label3, 88);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3,
                      "Este dispositivo se encarga de controlar los cabezales de los\nfiltros micro Z (imagen) y los parametros del agua que sale\nde ellos mediante un lazo de control.");

    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonFiltro1, ui_event_ButtonFiltro1, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Principal_screen_init();
    ui_ScreenMicroZ_screen_init();
    lv_disp_load_scr(ui_Principal);
}
