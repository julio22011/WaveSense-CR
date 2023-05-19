
void tareaBateria (void * parameter) {
  while(true){
    float voltajeBatTemp = 0;
    int n = 50;
    for (int i=1;i<=n;i++) { // saca 10 muestras
      voltajeBatTemp = voltajeBatTemp + analogRead(bateria)*2*(3.52/4095);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      //Serial.println(voltajeBatTemp);
    }
    voltajeBat = voltajeBatTemp/n; // promedio de las 10 muestras
    porcentajeBat = (voltajeBat-3.0)*(100/(4.2-3.0)); // porcentaje de bat

    // Para decidir el icono de bateria a mostrar:
    if(porcentajeBat >= 85) {barIcoNum = 1;}
    else if(porcentajeBat >= 50) {barIcoNum = 2;}
    else if(porcentajeBat >= 15) {barIcoNum = 3;}
    else{barIcoNum = 4;}
    listoBateria = true;

    //Serial.println(porcentajeBat);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  } // fin de while infinito
  vTaskDelete(NULL);
} // fin de funcion