


#if !defined(claseBateriaUIIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseBateriaUIIncluida

//  Clase para agregar la bateria a la interfaz principal
class bateriaUI{
  //
  private:
  bool transparente = false;

  public:

  uint8_t pinBateria;
  float voltajeBateria = 255;
  float porcentajeBat = 255;
  lv_obj_t * labelBat;  // objeto que muestra la bateria
  lv_style_t style_labelBat;  // estilo de la bateria

  // Funcion para actualizar la bateria
  void actualizar() {
    voltajeBateria = 2*analogRead(pinBateria)*(3.3/4095);   // se multiplica por dos debido al divisor de tension (resistencias)
    porcentajeBat = (voltajeBateria-3)*(1.2) * 100; 

    #ifdef depuracionDeBateria
      Serial.print("Voltaje: "); Serial.print(voltajeBateria); Serial.print(" Porcentaje: "); Serial.println(porcentajeBat);
    #endif

    lv_style_set_text_opa(&style_labelBat, 255); // visiviliza la bat
    if(porcentajeBat < 150 && porcentajeBat >= 75){
      // LV_SYMBOL_BATTERY_FULL
      lv_label_set_text(labelBat, LV_SYMBOL_BATTERY_FULL);
      lv_style_set_text_color(&style_labelBat, lv_color_hex(0x00ff00) ); // Poner color rojo la bateria
    }
    else if(porcentajeBat < 75 && porcentajeBat >= 50){
      // LV_SYMBOL_BATTERY_3
      lv_label_set_text(labelBat, LV_SYMBOL_BATTERY_3);
      lv_style_set_text_color(&style_labelBat, lv_color_hex(0x00ff00) ); // Poner color rojo la bateria
    }
    else if(porcentajeBat < 50 && porcentajeBat >= 25){
      // LV_SYMBOL_BATTERY_2
      lv_label_set_text(labelBat, LV_SYMBOL_BATTERY_2);
      lv_style_set_text_color(&style_labelBat, lv_color_hex(0x00ff00) ); // Poner color rojo la bateria
    }
    else if(porcentajeBat < 25 && porcentajeBat >= 10){
      lv_label_set_text(labelBat, LV_SYMBOL_BATTERY_1);
      lv_style_set_text_color(&style_labelBat, lv_color_hex(0x00ff00) ); // Poner color rojo la bateria
      // LV_SYMBOL_BATTERY_1
    }
    else if(porcentajeBat < 10){
      // LV_SYMBOL_BATTERY_EMPTY
      lv_label_set_text(labelBat, LV_SYMBOL_BATTERY_EMPTY);
      lv_style_set_text_color(&style_labelBat, lv_color_hex(0xff0000) ); // Poner color rojo la bateria

      // Hacer parpadear la bateria
      if(transparente){
        lv_style_set_text_opa(&style_labelBat, 0); // invisiviliza la bat
        transparente = false;
      } else {
        lv_style_set_text_opa(&style_labelBat, 255); // visiviliza la bat
        transparente = true;
      }
    }
  }

  // Funcion para inicializar
  bool iniciar(uint8_t pin, lv_obj_t * objDonde, lv_obj_t * objetoSide){  // pin de conexion, objeto donde se introduce el label, objeto para ubicar el label
    pinBateria = pin;
    pinMode(pin, INPUT);  // poner el pin como entrada

    labelBat = lv_label_create(objDonde);
    lv_label_set_text(labelBat, LV_SYMBOL_BATTERY_EMPTY);
    lv_obj_align_to(labelBat, objetoSide, LV_ALIGN_OUT_LEFT_MID, -20, 0); // alinear el el roller de hora

    // Agregar estilo al texto de bateria
    lv_style_init(&style_labelBat);
    lv_style_set_text_font(&style_labelBat, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_labelBat, lv_color_hex(0x00ff00) );
    lv_obj_add_style(labelBat, &style_labelBat, 0);

    //...

    // Tarea que actualiza automaticamente el estado de la bateria:
    //lv_timer_t * battery_label_task = lv_task_create(actualizarBatUI, 1000, LV_TASK_PRIO_MID, NULL);
    
    //static uint32_t user_data = 10;
    //lv_timer_t * timer = lv_timer_create(actualizarBatUI, 1000, &user_data);  // NULL
  }

};


#endif  // fin if de clase incluida