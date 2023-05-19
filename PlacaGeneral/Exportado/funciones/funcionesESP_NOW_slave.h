

// Para utilizar esp_now lo siguiente:
#define CHANNEL 1    // define el canal por el cual se enviaran los datos, debe ser igual en el emisor y receptor

// Estructura para almacenar los datos recibidos
////////////////////////////////////////////////////

// La siguiente es la estructura que sigue uno de los tipos de paquetes que se envian/reciber por esp-now:
// maximo de 250 bytes
typedef struct paquete{
  // Condicion
  bool pendiente = false; //  permite registrar si el paquete presentó un cambio, para proceder a enviarlo

  // Datos recibidos de los dos ADC
  float voltajeA0;
  float voltajeA1;
  float voltajeA2;
  float voltajeA3;
  float voltajeB0;
  float voltajeB1;
  float voltajeB2;
  float voltajeB3;

  // Sensores por otros parametros
  float caudal;
  float temperatura; 

  // Reporte de error
  bool error = false;  // se envia true para anunciar de la presencia de algun error

} paquete;

paquete paqueteRecibir;

//*******Funciones para esp_now********************//
/////////////////////////////////////////////////////
// Constructores
void configDeviceAP();
void InitESPNow();
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);


// setup para la conexion ESP-Now
void setupESPNOW(){
  //Set device in AP mode to begin with
  WiFi.mode(WIFI_AP);
  // configure device AP mode
  configDeviceAP();
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  // Init ESPNow with a fallback logic
  InitESPNow();
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info.
  esp_now_register_recv_cb(OnDataRecv);
}

// Init ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect(); // desconecta el WiFi
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();  // reinicia el ESP32
  }
}


// config AP SSID
void configDeviceAP() {
  String Prefix = "Slave:";
  String Mac = WiFi.macAddress();
  String SSID = Prefix + Mac;
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  memcpy(&paqueteRecibir, data, sizeof(paqueteRecibir));
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

/*desactivado temporalmente
  Serial.print("Last Packet Recv from: "); Serial.println(macStr);

  Serial.print("Dato_voltajeA0: "); Serial.println(paqueteRecibir.voltajeA0);
  Serial.print("Dato_voltajeA1: "); Serial.println(paqueteRecibir.voltajeA1);
  Serial.print("Dato_voltajeA2: "); Serial.println(paqueteRecibir.voltajeA2);
  Serial.print("Dato_voltajeA3: "); Serial.println(paqueteRecibir.voltajeA3);
  Serial.print("Dato_voltajeB0: "); Serial.println(paqueteRecibir.voltajeB0);
  Serial.print("Dato_voltajeB1: "); Serial.println(paqueteRecibir.voltajeB1);
  Serial.print("Dato_voltajeB2: "); Serial.println(paqueteRecibir.voltajeB2);
  Serial.print("Dato_voltajeB3: "); Serial.println(paqueteRecibir.voltajeB3);

  //Serial.print("Last Packet Recv Data: "); Serial.println(*data);
*/
  Serial.println("");
  /////////////////////////////
  Serial.print("Turbidez:"); Serial.print(paqueteRecibir.voltajeA0);
  Serial.print(" ");
  Serial.print("Conductividad:"); Serial.print(paqueteRecibir.voltajeA1);
  Serial.print(" ");
  Serial.print("pH:"); Serial.print(paqueteRecibir.voltajeA2);
  Serial.print(" ");
  Serial.print("Presion:"); Serial.print(paqueteRecibir.voltajeA3);
  Serial.println(" ");

  // Camibiar valor de medidor de LVGL:
  lv_meter_set_indicator_value(meter, indic, paqueteRecibir.voltajeA0);

///////////////
	// Conversion de float a char*
	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%f", paqueteRecibir.voltajeA0);

  //lv_label_set_text(label, buffer);

}
