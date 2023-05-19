// Esta tarea se encarga de hacer lectura de los botones y el joystick



// Funcion para leer los botones
void leerLosBotones(){
  char joystickPosX = botonesHMI.joystickDirectionX();
  char joystickPosY = botonesHMI.joystickDirectionY();

  char botonPresionado = botonesHMI.botonPresionado();  // Varible para recibir el boton presionado
  if (botonPresionado != '0'){ // si se presiona un boton, verifica cual fue
    if(botonPresionado == '1'){
      //              
    } else if (botonPresionado == '2'){
      //
    }
    else if(botonPresionado == '3'){
      //
    }
    else if(botonPresionado == '4'){
      //
    }
  }
  vTaskDelay(pdMS_TO_TICKS(10));

}



void tareaBotones(void * parameter){

  while(true){
    //
    leerLosBotones();           // Lee el estado de los botones y ejecuta accciones segun el boton presionado
  }
  vTaskDelete(NULL); // elimina la tarea en caso de que se salga del bucle
}


