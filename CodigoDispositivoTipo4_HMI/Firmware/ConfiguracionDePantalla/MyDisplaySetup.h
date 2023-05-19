// Install LovyanGFX if you don't have it yet
// Or You can use TFT_eSPI instead.


#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif

static lv_style_t style_textoMouse;  // estilo del cursor del mouse


#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
lgfx::Panel_ILI9488     _panel_instance;
lgfx::Bus_SPI       _bus_instance;   // SPIバスのインスタンス
lgfx::Light_PWM     _light_instance;
lgfx::Touch_XPT2046     _touch_instance;

public:
  Preferences preferences;  // para guardar datos de calibracion en la memoria NVR (de la libreria <Preferences.h>)
  
  LGFX(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。
      cfg.spi_host = VSPI_HOST;     // 使用するSPIを選択  (VSPI_HOST or HSPI_HOST)
      cfg.spi_mode = 0;             // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 40000000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read  = 16000000;    // 受信時のSPIクロック
      cfg.spi_3wire  = false;        // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock   = true;        // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = 1;          // Set the DMA channel (1 or 2. 0=disable)   使用するDMAチャンネルを設定 (0=DMA不使用)
      cfg.pin_sclk = 18;            // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 23;            // SPIのMOSIピン番号を設定
      cfg.pin_miso = 19;            // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc   = 2;      //16   // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。
      cfg.pin_cs           =    15; //5 // CSが接続されているピン番号   (-1 = disable)
      cfg.pin_rst          =    -1; //17 // RSTが接続されているピン番号  (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)
      cfg.memory_width     =   320;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   480;  // ドライバICがサポートしている最大の高さ
      cfg.panel_width      =   320;  // 実際に表示可能な幅
      cfg.panel_height     =   480;  // 実際に表示可能な高さ
      cfg.offset_x         =     0;  // パネルのX方向オフセット量
      cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg);
    }
    
    { // バックライト制御の設定を行います。（必要なければ削除）
      auto cfg = _light_instance.config();    // バックライト設定用の構造体を取得します。

      cfg.pin_bl = 17;   //21           // バックライトが接続されているピン番号
      cfg.invert = false;           // バックライトの輝度を反転させる場合 true
      cfg.freq   = 44100;           // バックライトのPWM周波数
      cfg.pwm_channel = 7;          // 使用するPWMのチャンネル番号

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);  // バックライトをパネルにセットします。
    }

    { // タッチスクリーン制御の設定を行います。（必要なければ削除）
      auto cfg = _touch_instance.config();
      cfg.x_min      = 0;    // タッチスクリーンから得られる最小のX値(生の値)
      cfg.x_max      = 319;  // タッチスクリーンから得られる最大のX値(生の値)
      cfg.y_min      = 0;    // タッチスクリーンから得られる最小のY値(生の値)
      cfg.y_max      = 479;  // タッチスクリーンから得られる最大のY値(生の値)
      cfg.pin_int    = -1;   // INTが接続されているピン番号
      cfg.bus_shared = true; // 画面と共通のバスを使用している場合 trueを設定
      cfg.offset_rotation = 0;// 表示とタッチの向きのが一致しない場合の調整 0~7の値で設定
      cfg.spi_host = VSPI_HOST;// 使用するSPIを選択 (HSPI_HOST or VSPI_HOST)
      cfg.freq = 1000000;     // SPIクロックを設定
      cfg.pin_sclk = 18;     // SCLKが接続されているピン番号
      cfg.pin_mosi = 23;     // MOSIが接続されているピン番号
      cfg.pin_miso = 19;     // MISOが接続されているピン番号
      cfg.pin_cs   = 16; //22  //   CSが接続されているピン番号
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);  // タッチスクリーンをパネルにセットします。
    }
    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }

  bool saveCalibration(uint16_t * calDataF){
    // Temporal
  }
};

LGFX tft;

//////////////////////////////////////////
/////////////////////////////////////////

// Función para procesar eventos del mouse
void mouse_driver_update(_lv_indev_drv_t* drv, lv_indev_data_t* data) {  // lv_indev_drv_t * drv
  // Procesar eventos del mouse aquí
  // Por ejemplo, mover un cursor en la pantalla
  // o hacer scroll en una lista

  if(data->point.x != botonesHMI.posX || data->point.y != botonesHMI.posY){
    lv_style_set_text_opa(&style_textoMouse, 255); // visiviliza el mouse
  }

  data->point.x = botonesHMI.posX;
  data->point.y = botonesHMI.posY;


  //char botonPresionado = botonesHMI.botonPresionado();

  // Actualizar el estado del botón del mouse
  if (botonesHMI.abajoPresionado) {
      data->state = LV_INDEV_STATE_PR; 

      // Para evitar dobles toques:
      //botonesHMI.arribaPresionado = false;
      botonesHMI.abajoPresionado = false;
      //botonesHMI.izquierdaPresionado = false;
      //botonesHMI.derechaPresionado = false;
  } else {
      data->state = LV_INDEV_STATE_REL;
  }
  
}

//////////////////////////////////////////
/////////////////////////////////////////

//Parte II para configurar la pantalla

/*Change to your screen resolution*/
static const uint32_t screenWidth  = 480;
static const uint32_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

/* "Flush" (refrescar) la pantalla */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   tft.startWrite();
   tft.setAddrWindow( area->x1, area->y1, w, h );
   //tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
   tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
   tft.endWrite();

   lv_disp_flush_ready( disp );
}

/*Leer la pantalla*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
   uint16_t touchX, touchY;
   bool touched = tft.getTouch( &touchX, &touchY);

   if( !touched )
   {
      data->state = LV_INDEV_STATE_REL;
   }
   else
   {
      lv_style_set_text_opa(&style_textoMouse, 0); // invisiviliza el mouse

      data->state = LV_INDEV_STATE_PR;

      /*Registrar las coordenadas*/
      data->point.x = touchX;
      data->point.y = touchY;

      #ifdef activarDepuracionTouch   // imprime las coordenadas de las pulsaciones de la pantalla tactil
        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
      #endif

   }

}

void calibracion(){
//----De tft_eSPI

  uint16_t calibrationData[8];
  bool calDataOK = false;

  // verificacion la existencia del archivo de calibracion de la pantalla
  /*
  if (SPIFFS.exists(CALIBRATION_FILE)) {
  
    File f = SPIFFS.open(CALIBRATION_FILE, "r");
    if (f) {
      f.readBytes((char *)calibrationData, 24);
      calDataOK = true;

      //if (f.readBytes((char *)calibrationData, 14) == 14) calDataOK = true;  // parece que no da 14

      f.close();
    }
  }
  */
  //tft.preferences.clear();  // para borrar datos

  tft.preferences.begin("screenCal");
  // Recuperar los datos de calibracion
  for(int i=0; i<8; i++){
    //tft.preferences.remove("calibration" + i);  // para borrar datos
    calibrationData[i] = tft.preferences.getInt("calibration" + i, 0);
  }
  if(calibrationData[0] == 0 && calibrationData[1] == 0 && calibrationData[2] == 0){
    calDataOK = false; // si los primeros 3 datos son 0, se indica que hay que efectuar calibracion
    Serial.println("No hay datos guardados. Calibracion de tft requerida");
    //for(int i=0; i<8; i++){
    //  Serial.println(tft.preferences.getInt("calibration" + i, 4));
    //}
  } else {
    Serial.println("Preferencias Calibracion recuperadas.");
    calDataOK = true;
  }

  if (calDataOK) {
    // calibration data valid
    tft.setTouchCalibrate(calibrationData);  //
    Serial.print("Datos de calibracion> ");  for(int u = 0; u < 8; u++) {Serial.println(calibrationData[u]);};
  } else {
    // data not valid. recalibrate
    //----------------------
    if (tft.touch())
    {
      if (tft.width() < tft.height()) tft.setRotation(tft.getRotation() ^ 1);

      // 画面に案内文章を描画します。
      tft.setTextDatum(textdatum_t::middle_center);
      tft.drawString("touch the arrow marker.", tft.width()>>1, tft.height() >> 1);
      tft.setTextDatum(textdatum_t::top_left);

      // タッチを使用する場合、キャリブレーションを行います。画面の四隅に表示される矢印の先端を順にタッチしてください。
      std::uint16_t fg = TFT_WHITE;
      std::uint16_t bg = TFT_BLACK;
      if (tft.isEPD()) std::swap(fg, bg);
      tft.calibrateTouch(calibrationData, fg, bg, std::max(tft.width(), tft.height()) >> 3);  // nullptr

      // Guardar los datos:
      for(int i=0; i<8; i++){
        tft.preferences.putInt("calibration" + i, calibrationData[i]);
      }

	    Serial.print("Datos de calibracion> "); for(int u = 0; u < 8; u++) {Serial.println(calibrationData[u]);};
    }

    tft.fillScreen(TFT_BLACK);

    tft.preferences.end();  // cerrar el espacio

    /*
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calibrationData, 24);
      f.close();
    }
    */
  }

//---------------------------------

}

// La siguiente funcion se debe localizar en el setup para inicializar la pantalla
void setupPantalla(){
   tft.begin();        
   tft.setRotation(3); // 1
   tft.setBrightness(255);
   uint16_t calData[] = { 239, 3930, 233, 265, 3856, 3896, 3714, 308}; // falta agregar funcion de calibracion***
   //tft.calibration();  // no existe
   //tft.setTouchCalibrate(calData);
   calibracion();

   lv_init();
   lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

   /*Iniciar la pantalla*/
   static lv_disp_drv_t disp_drv;
   lv_disp_drv_init(&disp_drv);

   /*Configurar los valores segun la pantalla, mediante las variables indicadas*/
   disp_drv.hor_res = screenWidth;
   disp_drv.ver_res = screenHeight;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register(&disp_drv);

   /*Iniciar el driver (dummy) del dispositivo de entrada (pantalla tactil)*/
   static lv_indev_drv_t indev_drv;
   lv_indev_drv_init(&indev_drv);
   indev_drv.type = LV_INDEV_TYPE_POINTER;
   indev_drv.read_cb = my_touchpad_read;
   lv_indev_drv_register(&indev_drv);

   /*Iniciar un mouse */
   //------------------------------------
   static lv_indev_drv_t mouse_drv;
   lv_indev_drv_init(&mouse_drv);

   // Rellenar la estructura mouse_drv
   mouse_drv.type = LV_INDEV_TYPE_POINTER;
   mouse_drv.read_cb = mouse_driver_update;

   lv_indev_drv_register(&mouse_drv);

// Prueba de cursor de mouse (poner imagen):
//------------------------------------
//#include "cursor.c"   // imagen convertida

lv_indev_t * mouse_indev = lv_indev_drv_register(&mouse_drv);

//-LV_IMG_DECLARE(ui_img_cursor_png);                          /*Declare the image file.*/                  //  ui_img_175923361 (imagen de bomba, funciona)
//-lv_obj_t * cursor_obj =  lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
//-lv_img_set_src(cursor_obj, &ui_img_cursor_png);             /*Set the image source*/

lv_obj_t * labelMouse = lv_label_create(lv_scr_act());
lv_label_set_text(labelMouse, LV_SYMBOL_GPS);

lv_style_init(&style_textoMouse);
lv_style_set_text_font(&style_textoMouse, &lv_font_montserrat_20);
lv_style_set_text_color(&style_textoMouse, lv_color_hex(0xff0f3d));
lv_obj_add_style(labelMouse, &style_textoMouse, 0);
lv_indev_set_cursor(mouse_indev, labelMouse);               /*Connect the image  object to the driver*/   // cursor_obj (objeto imagen)

}
