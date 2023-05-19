//****************************************************************
//  Este archivo contiene la tarea que se encarga de controlar la
//  interfaz de la pantalla OLED del dispoitivo.
//****************************************************************

void imprimirMenu(){
  //
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,8);
  display.println(F("    Menu principal"));
  display.setCursor(0,16);
  display.println(F("  Configuracion"));
  display.println(F("  Ver lecturas"));
  display.println(F("  Mostrar codigo QR"));
  display.display();
}

int16_t selectMenuPrincipal = 1;
bool actualizarMenu = true;
void imprimirCursor(){
  //
  if (actualizarMenu == true){
    display.setCursor(0,16);
    display.println(F(">"));
    display.display();  // refrescar pantalla
    actualizarMenu = false;    
  }
}

//**************************************************
void tareaUI(void * parameters){
  //
  while(true){ // bucle infinito
    //
    imprimirMenu();
    imprimirCursor();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}
