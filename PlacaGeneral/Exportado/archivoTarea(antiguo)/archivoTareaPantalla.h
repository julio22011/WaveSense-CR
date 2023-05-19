

// La siguiente funcion permite la calibracion e inicio de la pantalla
void procesoDeInicioDePantalla () {
  // procesos iniciales de la pantalla
  uint16_t calibrationData[5];
  uint8_t calDataOK = 0;
  
  tft.init();
  tft.setRotation(3); // rotacion> 1,2,3 : horizontal,x,x
  tft.fillScreen((0xFFFF));

  tft.setCursor(20, 0, 2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);  tft.setTextSize(1);
  tft.println("calibration run");

  // verificacion de la memoria del sistema
  if (!SPIFFS.begin()) {
    Serial.println("formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // verificacion la existencia del archivo de calibracion de la pantalla
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    File f = SPIFFS.open(CALIBRATION_FILE, "r");
    if (f) {
      if (f.readBytes((char *)calibrationData, 14) == 14)
        calDataOK = 1;
      f.close();
    }
  }
  if (calDataOK) {
    // calibration data valid
    tft.setTouch(calibrationData);
    Serial.print("Datos de calibracion> ");  for(int u = 1; u <= 4; u++) {Serial.println(calibrationData[1]);};
  } else {
    // data not valid. recalibrate
    tft.calibrateTouch(calibrationData, TFT_WHITE, TFT_RED, 15);
    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calibrationData, 14);
      f.close();
    }
  }

  tft.fillScreen((0xFFFF)); // pone blanca la pantalla
}

//bool tft_ya_iniciado = false; //permite evitar que se haga el inicio de la pantalla varias veces

void tareaPantalla (void * parameter){
  //if(!tft_ya_iniciado) {procesoDeInicioDePantalla();tft_ya_iniciado = true;}
  procesoDeInicioDePantalla();
  dibujarMenu(); // dibuja los botones en pantalla

  while(true){
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  tft.setTextSize(1); // restablecer ajustes
    static uint16_t color;

    touchPresionado = tft.getTouch(&x, &y);
    if (touchPresionado) {
      tft.setCursor(5, 5, 2);
      tft.printf("x: %i     ", x);
      tft.setCursor(5, 20, 2);
      tft.printf("y: %i    ", y);
  
      tft.drawPixel(x, y, color);
      color += 155;
    }

    /////Imprimir resultado de lectura SD cuando el booleano listoSD lo indique
    if (listoSD) {
      tft.setCursor(300, 270, 2);
      tft.print(tipoDeSD);
      tft.setCursor(300, 300, 2);
      tft.print(lectura);
      listoSD = false;
    }

    //--------------------------------------------------------------------------------
    //*/***/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*//*//*/*/*/*//*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/
    // Lo siguiente ejecuta una accion dependiendo del boton presionado
    char* retornoTecla = pantallaBotones(); // lee el valor registrado por los botones

    if (retornoTecla == "a"){
      imprimirMensajeTFT(185,300,"Vibrando                            ",true);
      iniciarVibracion(1500);

      // Para pruebas:
      iniciarLVGL(5000); // inicia el UI de LVGL
      vTaskDelete(NULL); // elimina la tarea de pantalla, dejando la pantalla a cargo de la tarea de LVGL
    }
    else if (retornoTecla == "b"){
      // Poner imagen de fondo de la tarjeta SD
      //tft.setRotation(1);  // portrait
      tft.fillScreen(random(0xFFFF));
      drawSdJpeg("/Mause480.jpg", 0, 0);     // This draws a jpeg pulled off the SD Card
      String msg = String(tiempoDeTrazadoIMG);
      msg = "Tiempo de dibujo de img: " + msg;
      imprimirMensajeTFT(185,300, msg,true);
      dibujarMenu();
      ////
      //firebaseSetup();
      //enviarDatosDeSensores();
    }
    else if (retornoTecla == "c"){
      iniciarAudBlue(5000);
      imprimirMensajeTFT(185,300,"Alt. BT activado                   ",true);
    }
    else if (retornoTecla == "d"){
      imprimirMensajeTFT(185,300,"Escaneo y conexion WiFi iniciado.  ",true);
      escaneoDeWifi();  // hace un escaneo de las redes wifi y las muestra en pantalla
      iniciarWifi(5000); // Por mientras, este boton ejecula la conexion wifi. Stack normal: 5000. 
    }
    else if (retornoTecla == "e"){
      activarServo = !activarServo;
      if (activarServo) {
        iniciarServo(1000);
        imprimirMensajeTFT(185,300,"Servo activado en pin 14 (4)          ",true); // indica si se ha activado el servo
        dibujarMenu();
      }
      else imprimirMensajeTFT(185,300,"Servo desactivado                  ",true);
    }
    else if (retornoTecla == "f"){
      activarSerialBT = !activarSerialBT;
      if (activarSerialBT) {
        iniciarSerialBT(5000);
        imprimirMensajeTFT(185,300,"Serial BT activado                    ",true);
      }
      else imprimirMensajeTFT(185,300,"Serial Bt desactivado              ",true);
    }
    else if (retornoTecla == "g"){
      activarServidor = !activarServidor;
      if (activarServidor) {
        iniciarServidor(1000);
        imprimirMensajeTFT(185,300,"Servidor activado                     ",true);
      }
      else {imprimirMensajeTFT(185,300,"Servidor desactivado               ",true);/*server2.reset();*/} // se resetea el servidor y se desactiva
    }
    else if (retornoTecla == "h"){
      activarESPNOW = !activarESPNOW;
      if (activarESPNOW) {
        iniciarESPNOW(2000); // Stack normal: 2000
        imprimirMensajeTFT(185,300,"ESP_NOW activado                      ",true);
      }
      else {imprimirMensajeTFT(185,300,"ESP_NOW desactivado                 ",true);}
    }
    else if (retornoTecla == "i"){
      activarMouseBLE = !activarMouseBLE;
      if (activarMouseBLE) {
        iniciarMouseBLE(8000);
        imprimirMensajeTFT(185,300,"Mouse BLE activado                      ",true);
      }
      else {imprimirMensajeTFT(185,300,"Mouse BLE desactivado                 ",true);}
    }
    else if (retornoTecla == "j"){
      activarGraficacion = !activarGraficacion;
      if (activarGraficacion) {
        iniciarGraficacion(5500);
        imprimirMensajeTFT(185,300,"Proceso de graficacion activado       ",true); // indica si se ha activado el servo
        dibujarMenu();
      }
      else imprimirMensajeTFT(185,300,"Proceso de graficacion desactivado    ",true);
    }



    // imprimir mensaje del serial bluetooth
    if (mensajeBTrecibido) {
      imprimirMensajeTFT(185,275,"Bluetooth>>                                     ",false); // limpia el campo
      imprimirMensajeTFT(185,275,"Bluetooth>> " + bufferBT, false); // + bufferBT
      bufferBT = "";
      mensajeBTrecibido = false;
    }

    // Imprimir en pantalla el boton y analogo presionado:
    if (botonPresionado != ""){
      imprimirMensajeTFT(355,20,"Boton> " + String(botonPresionado), false);
    }
    if (ubicacionAnalogoX != ""){
      imprimirMensajeTFT(355,20,"Boton> " + String(ubicacionAnalogoX),false);
    } else if(ubicacionAnalogoY != ""){
      imprimirMensajeTFT(355,20,"Boton> " + String(ubicacionAnalogoY),false);
    }

    if(listoBateria){ // hace mostrar la bateria una vez si ha calculado el porcentaje de bateria

      // Imprimir la cantidad de memoria (stack) disponible en bytes, para poder gestionar las tareas
      imprimirMensajeTFT(180,280,"Stack (bytes)> " + String(xPortGetFreeHeapSize()), false);

      // imprimir porcentaje de bateria en la pantalla
      tft.setCursor(20, 280, 2);
      tft.printf("Voltaje Bat: %f", voltajeBat);
      tft.setCursor(20, 300, 2);
      tft.printf("Bateria: %f", porcentajeBat);
      dibujarIconoBateria(400,5); // dibuja el correspondiente icono de bateria segun nivel. Parametros: (posX, posY)
      listoBateria = false;
    }


    
  } // fin del while infinito
  vTaskDelete(NULL); // desactiva la tarea si sale del bucle
} // fin de tarea
