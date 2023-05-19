
/// funcion para realizar un grafico en vivo de los datos
void hacerGraficoEnVivo(int *valorGraficadoOriginal, int deltaTiempo, int *contador, float *bufferDatosX, float *bufferDatosY, int sizeBuf){  // dato a graficar, deltaTiempo (Ej. 100 ms), tamaño de buffer (Ej. 60)

  //int sizeBuf = sizeof(bufferDatosX)/4;
  display1 = true; // poner esto para volver a activar la funcion Graph una vez ya se hizo el grafico

  //Graph(tft, x, y, 1, 60, 290, 390, 260, 0, 6.5, 1, -1, 1, .25, "", "", "", display1, YELLOW); // dibuja la pantalla donde se grafica (Original de referencia)
  Graph(tft, x, y, 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "", "", "", display1, YELLOW); // dibuja la pantalla donde se grafica
  
  tft.fillScreen(BLACK);
  //tft.setRotation(1);
  
  //int contador = 0;
  //float bufferDatosX[sizeBuf];
  //float bufferDatosY[sizeBuf]; //sizeBuf

  // Crea el vector para los datos del eje X:
  for (int i = 0; i <= sizeBuf; i+=1) {  // usar sizeof
    bufferDatosX[i] = (float)i/20;
    Serial.println((float)i/20);
  }

  while(activarGraficacion){
    float valorGraficado = (float)*valorGraficadoOriginal/1000;
    display1 = true; // activa la funcion graph
    if (*contador < sizeBuf) {
      *contador = *contador + 1;
      update1 = true;
      bufferDatosY[*contador] = valorGraficado;
      for (int u = 0; u <= *contador; u += 1) {  // este for dibuja los puntos del grafico
        Trace(tft, bufferDatosX[u], bufferDatosY[u], 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "Grafico de pH", "t", "pH", update1, YELLOW);
      }
    }
    // El siguiete else se activa cuando ya se ha completado de llenar la pantalla y los datos antiguos tienen que comenzar a desplazarse hacia la izquierda
    else{
      for (int u = 0; u <= *contador; u += 1) {  // Este "for" dibuja los puntos antiguos del grafico en negro para borrarlos
        Trace(tft, bufferDatosX[u], bufferDatosY[u], 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "Grafico de pH", "t", "pH", update1, BLACK);
      }
      for(int p = 0; p < sizeBuf; p++){ // Este "for" mueve cada data del vector un espacio hacia la izuierda, para ir moviendo todo el grafico hacia la izquierda
        bufferDatosY[p] = bufferDatosY[p+1];  
      }
      ////////Lo siguiente imprime la Grafica actualizada
      update1 = true;
      bufferDatosY[*contador-1] = valorGraficado;
      for (int u = 0; u < *contador; u += 1) {  // este for dibuja los puntos del grafico
        Trace(tft, bufferDatosX[u], bufferDatosY[u], 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "Grafico de pH", "t", "pH", update1, YELLOW);
      }
    }
    vTaskDelay(deltaTiempo / portTICK_PERIOD_MS);
    Graph(tft, x, y, 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "", "", "", display1, YELLOW); // dibuja la pantalla donde se grafica
  }

} // fin de funcion


void tareaGraficacion(void * parameters){
  int contador = 0;
  int sizeBuf = 120;
  float bufferDatosX[sizeBuf];
  float bufferDatosY[sizeBuf];
  hacerGraficoEnVivo(&lecturaPinGrafico, 50, &contador, bufferDatosX, bufferDatosY, sizeBuf);
  vTaskDelete(NULL);
}