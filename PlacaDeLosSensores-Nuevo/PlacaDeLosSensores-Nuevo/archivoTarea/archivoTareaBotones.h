

// Funciones para la tarea
//--------------------------
bool inRange(unsigned low, unsigned high, unsigned x)    // permite saber si un numero esta en un rango     
{         
 return (low <= x && x <= high);         
}


//*************************************************************************
void tareaBotones(void * parameters){
  //
  while(true){ // bucle infinito
    //
    lecturaBotones = analogRead(pinBotones); // obtine la lectura analogica para saber caul es el boton presionado
    //Serial.print("Valor de botones: "); Serial.println(lecturaBotones); // para obtener valor de cada boton. Resultados: 1:4094, 2:2815, 3:1800, 4:824

    // Lo siguiente identifica el boton presionado dependiendo del rango donde se encuentra
    if (lecturaBotones >= blim7){
      inRange(blim1, blim2, lecturaBotones)? botonPresionado = 1:
        inRange(blim3, blim4, lecturaBotones)? botonPresionado = 2:
          inRange(blim5, blim6, lecturaBotones)? botonPresionado = 3:
            inRange(blim7, blim8, lecturaBotones)? botonPresionado = 4: Serial.println("Error en botones");
       Serial.println(botonPresionado); // para verificar funcionamiento, imprime el boton presionado
    }else{
      botonPresionado = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  vTaskDelete(NULL);
}
