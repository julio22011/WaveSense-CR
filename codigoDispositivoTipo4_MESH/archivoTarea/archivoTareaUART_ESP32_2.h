
// Esta tarea permite recibir datos por Uart desde la ESP32 secundaria

void updateCredentialsWiFi(String newDatosCred);

void tareaUART_ESP32_2(void * parameters){
  //
  //Serial2.begin(115200, SERIAL_8N1, RX_ESP, TX_ESP);
  while(true){
    if(Serial2.available()){
      datoRecibido = Serial2.readStringUntil('\n');
      Serial.println(datoRecibido);
      mensajeNuevo = true;                // bandera para indicar que se ha recibido un mensaje nuevo
      mesh.sendBroadcast( datoRecibido ); // enviar el mensaje a la red mesh
      
      // Nuevo 26/4/2023    
      // Ver si el mensaje fue de actualizacion de credenciales
      if(datoRecibido.substring(0, 11) == "Credentials"){  // .substring(x,x) saca una parte de un string. Argumentos: (inicio, longitud)
        String datosCred = datoRecibido.substring(13, 100);
        updateCredentialsWiFi(datosCred); // Actualizar credenciales de la red WiFi
        WiFi.disconnect(); // desconectar WiFi para cambiar de WiFi
        //return; // no hacer nada mas. No se puede return aqui
      }
      // Nuevo fin
    }
    vTaskDelay(pdMS_TO_TICKS(200));       // darle un momento para que se llene el buffer del serial
  }
  //if (cuenta>200){vTaskDelay(pdMS_TO_TICKS(10));cuenta = 0;}
  vTaskDelete(NULL);
}

// Nuevo 26/4/2023
// Funcion para actualizar los datos de las credenciales WiFi de la red
void updateCredentialsWiFi(String newDatosCred){
  size_t pos = newDatosCred.indexOf(":::"); // Busca el patrón ":::" dentro del texto

  if (pos != -1) { // Si se encuentra el patrón, imprime el texto hasta ese punto
    String ssidNuevo = newDatosCred.substring(0, pos);
    String passwordNuevo = newDatosCred.substring(pos+3);
    mesh.stationManual(ssidNuevo, passwordNuevo); // Configurar las nuevas credenciales
    Serial.printf("Nuevas credenciales: %s ::: %s\n", ssidNuevo.c_str(), passwordNuevo.c_str());

    // Guardar las nuevas credenciales en la memoria permanente
    preferences.putString("ssid", ssidNuevo);              //"KONOHA";        // char*
    preferences.putString("password", passwordNuevo);     //"familiars58";  // char*
    //ESP.restart(); // Temporal: reiniciar para aplicar cambio
  }
  else { // Si no se encuentra el patrón, imprime todo el texto
    Serial.println("Error al configurar las credenciales: No se encontro el patron :::");
  }
}
// Nuevo fin
