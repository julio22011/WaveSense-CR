
// la siguiente funcion debe ejecutarse por la tarea de la pantalla
// para evitar problemas
// Funcion para hacer un escaneo de la redes disponibles y mostrarlas:
void escaneoDeWifi(){
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
    imprimirMensajeTFT(120,5,"No networks found",true);
  } else {
    Serial.print(n);
    Serial.println(" networks found");

    imprimirMensajeTFT(120,5,"Redes encontradas:",false); // impresion en la TFT
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

      // Impresion en la TFT
      imprimirMensajeTFT(120,30+i*20,"                       ",false); // borra la red anterior
      imprimirMensajeTFT(120,30+i*20,WiFi.SSID(i) + " " + WiFi.RSSI(i),false);

      vTaskDelay(10 / portTICK_PERIOD_MS);
    } // fin del for
  }
} // fin de la funcion

void activarComoHostSpot(){
  WiFi.mode(WIFI_AP_STA); //WIFI_AP_STA para que se conecte y sea estacion a la vez
  
  WiFi.softAPConfig(  // Set IP Address, Gateway and Subnet
    IPAddress(192, 168, 4, 1),
    IPAddress(192, 168, 4, 1),
    IPAddress(255, 255, 255, 0));
  WiFi.softAP(APssid,APpassword);
  WiFi.begin(ssid, password);
  // give DNS servers to AP side
  //dhcpSoftAP.dhcps_set_dns(0, WiFi.dnsIP(0)); //
  //dhcpSoftAP.dhcps_set_dns(1, WiFi.dnsIP(1)); //
  /*
  ///////////////////
  Serial.printf("AP: %s\n", WiFi.softAPIP().toString().c_str());

  Serial.printf("Heap before: %d\n", ESP.getFreeHeap());
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  Serial.printf("ip_napt_init(%d,%d): ret=%d (OK=%d)\n", NAPT, NAPT_PORT, (int)ret, (int)ERR_OK);
  if (ret == ERR_OK) {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.printf("ip_napt_enable_no(SOFTAP_IF): ret=%d (OK=%d)\n", (int)ret, (int)ERR_OK);
    if (ret == ERR_OK) {
      Serial.printf("WiFi Network '%s' with same password is now NATed behind '%s'\n", STASSID "extender", STASSID);
    }
  }
  Serial.printf("Heap after napt init: %d\n", ESP.getFreeHeap());
  if (ret != ERR_OK) {
    Serial.printf("NAPT initialization failed\n");
  }
  */
}

void tareaWifi (void * parameter){
    // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  if(activarHostSpot) activarComoHostSpot(); else {WiFi.mode(WIFI_STA);WiFi.begin(ssid, password);}
  
  uint8_t pruebasDeConeccion = 100;
  while (WiFi.status() != WL_CONNECTED and pruebasDeConeccion > 0) { // repite el intento de conexion varias veces
      vTaskDelay(500 / portTICK_PERIOD_MS);
      Serial.print(".");
      pruebasDeConeccion--;
  }
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Error, intentos de conectar acabados");
  }else{
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // Mantener parpadeando led amarrillo mientras este conectado
  while (WiFi.status() == WL_CONNECTED){
    digitalWrite(ledAmarillo, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(ledAmarillo, LOW);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL); // elimina la tarea una vez terminada
} // fin de tarea
