// Esta tarea se encarga de hacer lectura de los botones y el joystick



void tareaBotones(void * parameter){

  while(true){
        ///////////////////////////////////////  
        // Verificacion del boton presionado  
    lecturaBotones = analogRead(botones); // inicia la lectura del valor del pin de los botones
    lecturaAnalogoX = analogRead(analogoX); // medicion del analogo
    lecturaAnalogoY = analogRead(analogoY); // medicion del analogo

    if (lecturaBotones > 2500 and lecturaBotones < 3100) { // botón abajo 
      botonPresionado = "a";
      Serial.println(analogRead(botones));
      vTaskDelay(150 / portTICK_PERIOD_MS);
    }
    else if (lecturaBotones > 3800 and lecturaBotones < 4100) { // botón derecha
      botonPresionado = "d";
      Serial.println("Derecha");
      vTaskDelay(150 / portTICK_PERIOD_MS);
      //iniciarSD(3000);
    }
    else if (lecturaBotones > 500 and lecturaBotones < 1100) { // botón izquierda
      botonPresionado = "i";
      Serial.println("Izquierda");
      vTaskDelay(150 / portTICK_PERIOD_MS);
    }
    else if (lecturaBotones > 1500 and lecturaBotones < 2100) { // botón arriba 
      botonPresionado = "A";
      Serial.println("Arriba");
      vTaskDelay(150 / portTICK_PERIOD_MS);
    }
    else {botonPresionado = "";} // define como nada el boton presionado



    // Verificacion de la ubicacion del joystick en sus dos coordenadas (x,y)
    if (lecturaAnalogoX > 3000){
      ubicacionAnalogoX = "R";
      Serial.println("Analogo: Right");
    } else if (lecturaAnalogoX < 1200) {
      ubicacionAnalogoX = "L";
      Serial.println("Analogo: Left");
    } else {ubicacionAnalogoX = "";}

    if (lecturaAnalogoY < 1200){ 
      ubicacionAnalogoY = "U";
      Serial.println("Analogo: Upper");
    } else if (lecturaAnalogoY > 3000) {
      ubicacionAnalogoY = "D";
      Serial.println("Analogo: Down");
    } else {ubicacionAnalogoY = "";}

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL); // elimina la tarea en caso de que se salga del bucle
}