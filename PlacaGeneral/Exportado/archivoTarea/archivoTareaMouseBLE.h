
BleMouse bleMouse; // crea un objeto mouse
bool continuaPresionadoIzq = false;

void tareaMouseBLE(void * parameter){  // void * parameter

  bleMouse.begin(); // inicializa el mouse, contiene funcion multitasking
  Serial.println("Starting BLE work!");

  while(activarMouseBLE){
    if(bleMouse.isConnected()) {
      if(ubicacionAnalogoX == "R"){
        bleMouse.move(2,0); // (x,y,scroll-1,Scroll-2)
      }
      if(ubicacionAnalogoY == "U"){
        bleMouse.move(0,-2); // (x,y,scroll-1,Scrool-2)
      }
      if(ubicacionAnalogoX == "L"){
        bleMouse.move(-2,0); // (x,y,scroll-1,Scroll-2)
      }
      if(ubicacionAnalogoY == "D"){
        bleMouse.move(0,2); // (x,y,scroll-1,Scrool-2)
      }

      // click izquierdo
      if(botonPresionado == "a"){
        bleMouse.press(MOUSE_LEFT); // MOUSE_RIGHT, MOUSE_LEFT, MOUSE_MIDDLE, MOUSE_BACK, MOUSE_FORWARD, MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE (al mismo tiempo)
        if(!continuaPresionadoIzq){/*vTaskDelay(1);*/} // solo espera si no está en modo presionado
        if(botonPresionado == "a") {continuaPresionadoIzq = true;}else{bleMouse.release(MOUSE_LEFT);/* bleMouse.click(MOUSE_LEFT);*/}
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      else {continuaPresionadoIzq = false;}
      if(!continuaPresionadoIzq){
        bleMouse.release(MOUSE_LEFT);
      }
      ///////////////////////////////////////
      
      vTaskDelay(1 / portTICK_PERIOD_MS);
      
    } // fin de if mouse conectado
    vTaskDelay(1 / portTICK_PERIOD_MS);
    
  } // fin while infinito
  vTaskDelete(NULL);
} // fin de tarea



/**
 * This example turns the ESP32 into a Bluetooth LE mouse that continuously moves the mouse.

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleMouse.begin();
}

void loop() {
  if(bleMouse.isConnected()) {

    unsigned long startTime;

    Serial.println("Scroll up");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(0,0,1);
      delay(100);
    }
    delay(500);

    Serial.println("Scroll down");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(0,0,-1);
      delay(100);
    }
    delay(500);

    Serial.println("Scroll left");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(0,0,0,-1);
      delay(100);
    }
    delay(500);

    Serial.println("Scroll right");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(0,0,0,1);
      delay(100);
    }
    delay(500);

    Serial.println("Move mouse pointer up");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(0,-1);
      delay(100);
    }
    delay(500);

    Serial.println("Move mouse pointer down");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(0,1);
      delay(100);
    }
    delay(500);

    Serial.println("Move mouse pointer left");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(-1,0);
      delay(100);
    }
    delay(500);

    Serial.println("Move mouse pointer right");
    startTime = millis();
    while(millis()<startTime+2000) {
      bleMouse.move(1,0);
      delay(100);
    }
    delay(500);

  }
}
*/