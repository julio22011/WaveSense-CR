
// Esta tarea maneja las actualizaciones del grafico de LVGl

void tareaGrafica(void * parameters){

  pinMode(fotocelda, INPUT);
  int cuenta = 0;
  while(cuenta<1000){
    //
    int lectura = analogRead(fotocelda);
    for (int i = 0; i<=100 ;i++){
      for(int j = 0; j<=10 ;j++){
        lectura = analogRead(fotocelda);
        //ecg_sample[cuenta] = lectura;
	ecg_sample[cuenta] = lecturaAnalogoY/2-1000;
        cuenta++;
      }
      lv_chart_refresh(ui_Chart3); // actualizar el grafico
      vTaskDelay(pdMS_TO_TICKS(100));
    }
    //cuenta = 0;
  }
  while(1){}
  vTaskDelete(NULL);
}
