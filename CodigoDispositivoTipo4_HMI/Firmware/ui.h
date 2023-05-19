// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: HMI_LVGL

#ifndef _HMI_LVGL_UI_H
#define _HMI_LVGL_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_Principal;
extern lv_obj_t * ui_Keyboard1;
extern lv_obj_t * ui_BarraNotificaciones;
void ui_event_ButtonAjustes(lv_event_t * e);
extern lv_obj_t * ui_ButtonAjustes;
extern lv_obj_t * ui_LabelBotonAjustes;
void ui_event_ButtonMesh(lv_event_t * e);
extern lv_obj_t * ui_ButtonMesh;
extern lv_obj_t * ui_LabelBotonMesh;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_LabelHora;
extern lv_obj_t * ui_PanelDeAcueducto;
extern lv_obj_t * ui_ButtonDisp1A;
extern lv_obj_t * ui_Label1;
void ui_event_ButtonDisp2(lv_event_t * e);
extern lv_obj_t * ui_ButtonDisp2;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_ButtonDisp3;
extern lv_obj_t * ui_Label8;
void ui_event_Button9(lv_event_t * e);
extern lv_obj_t * ui_Button9;
extern lv_obj_t * ui_Label14;
extern lv_obj_t * ui_ButtonDisp1B;
extern lv_obj_t * ui_Label9;
void ui_event_ButtonFMicroz(lv_event_t * e);
extern lv_obj_t * ui_ButtonFMicroz;
extern lv_obj_t * ui_Label15;
extern lv_obj_t * ui_ButtonPulido;
extern lv_obj_t * ui_Label17;
extern lv_obj_t * ui_ButtonCloro2;
extern lv_obj_t * ui_Label18;
extern lv_obj_t * ui_ButtonCloro1;
extern lv_obj_t * ui_Label19;
extern lv_obj_t * ui_ButtonAlmacenamiento;
extern lv_obj_t * ui_Label20;
extern lv_obj_t * ui_ButtonAguaMuni;
extern lv_obj_t * ui_Label21;
extern lv_obj_t * ui_ButtonTanqDist;
extern lv_obj_t * ui_Label22;
extern lv_obj_t * ui_ButtonRedDist;
extern lv_obj_t * ui_Label24;
extern lv_obj_t * ui_Label25;
extern lv_obj_t * ui_ButtonFFeMn;
extern lv_obj_t * ui_Label16;
extern lv_obj_t * ui_ButtonPulidoFinal;
extern lv_obj_t * ui_Label27;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label26;
extern lv_obj_t * ui_ImgButton2;
extern lv_obj_t * ui_Spinner1;
extern lv_obj_t * ui_ScreenMicroZ;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label2;
void ui_event_ButtonFiltro1(lv_event_t * e);
extern lv_obj_t * ui_ButtonFiltro1;
extern lv_obj_t * ui_Label10;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Label3;

void abrirVentanaDeConfiguracion(lv_event_t * e);
void abrirConfigWiFi(lv_event_t * e);
void accionBotonPozo(lv_event_t * e);
void abrirPantllaDispTipo2(lv_event_t * e);

LV_IMG_DECLARE(ui_img_background2_png);    // assets\Background2.PNG
LV_IMG_DECLARE(ui_img_175923361);    // assets\bombaCirc - copia.png
LV_IMG_DECLARE(ui_img_fotofiltros_png);    // assets\FotoFiltros.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
