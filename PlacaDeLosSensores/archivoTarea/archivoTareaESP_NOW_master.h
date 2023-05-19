// Esta tarea permite establecer una comunicacion entre varios dispositivos esp32

// Constructores de funciones
void ADChacerMediciones();

// Varibles de configuracion de la comunicacion, deben ser las mismas en todos los disp. conectados:
esp_now_peer_info_t slave;
#define CHANNEL 1    //3
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

// La siguiente es la estructura que sigue uno de los tipos de paquetes que se envian por esp-now:
// La siguiente es la estructura que sigue uno de los tipos de paquetes que se envian/reciber por esp-now:
// maximo de 250 bytes
typedef struct paquete{
  // Condicion
  bool pendiente = true; //  permite registrar si el paquete presentó un cambio, para proceder a enviarlo

  // Datos recibidos de los dos ADC
  float voltajeA0 = 0;
  float voltajeA1 = 0;
  float voltajeA2 = 0;
  float voltajeA3 = 0;
  float voltajeB0 = 0;
  float voltajeB1 = 0;
  float voltajeB2 = 0;
  float voltajeB3 = 0;

  // Sensores por otros parametros
  float caudal = 0;
  float temperatura = 0; 

  // Reporte de error
  bool error = false;  // se envia true para anunciar de la presencia de algun error

} paquete;

// funciones para funcionamiento de ESP-NOW: 
//A continuacion se encuentran varias funciones de ESP-Now prefabricadas para su uso
/////////////////////////////////////////////
// Init ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
    WiFi.mode(WIFI_STA); // todos los dispositivos conectados deben estar en este modo
  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    InitESPNow();
    // or Simply Restart
    //ESP.restart();
  }
} // fin de funcion

//-------------------------------------------------------
// Scan for slaves in AP mode
void ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();
  // reset on each scan
  bool slaveFound = 0;
  memset(&slave, 0, sizeof(slave));

  Serial.println("");
  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
  } else {
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(SSID);
        Serial.print(" (");
        Serial.print(RSSI);
        Serial.print(")");
        Serial.println("");
      }
      delay(10);
      // Check if the current device starts with `Slave`
      if (SSID.indexOf("Slave") == 0) {
        // SSID of interest
        Serial.println("Found a Slave.");
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        // Get BSSID => Mac Address of the Slave
        int mac[6];
        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            slave.peer_addr[ii] = (uint8_t) mac[ii];
          }
        }

        slave.channel = CHANNEL; // pick a channel
        slave.encrypt = 0; // no encryption

        slaveFound = 1;
        // we are planning to have only one slave in this example;
        // Hence, break after we find one, to be a bit efficient
        break;
      }
    }
  }

  if (slaveFound) {
    Serial.println("Slave Found, processing..");
  } else {
    Serial.println("Slave Not Found, trying again.");
  }

  // clean up ram
  WiFi.scanDelete();
}

//-------------------------------------------------------
void deletePeer() {
  esp_err_t delStatus = esp_now_del_peer(slave.peer_addr);
  Serial.print("Slave Delete Status: ");
  if (delStatus == ESP_OK) {
    // Delete success
    Serial.println("Success");
  } else if (delStatus == ESP_ERR_ESPNOW_NOT_INIT) {
    // How did we get so far!!
    Serial.println("ESPNOW Not Init");
  } else if (delStatus == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (delStatus == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } else {
    Serial.println("Not sure what happened");
  }
} // fin de la funcion

//-------------------------------------------------------
// Check if the slave is already paired with the master.
// If not, pair the slave with master
bool manageSlave() {
  if (slave.channel == CHANNEL) {
    if (DELETEBEFOREPAIR) {
      deletePeer();
    }

    Serial.print("Slave Status: ");
    // check if the peer exists
    bool exists = esp_now_is_peer_exist(slave.peer_addr);
    if ( exists) {
      // Slave already paired.
      Serial.println("Already Paired");
      return true;
    } else {
      // Slave not paired, attempt pair
      esp_err_t addStatus = esp_now_add_peer(&slave);
      if (addStatus == ESP_OK) {
        // Pair success
        Serial.println("Pair success");
        return true;
      } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        // How did we get so far!!
        Serial.println("ESPNOW Not Init");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        Serial.println("Invalid Argument");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        Serial.println("Peer list full");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        Serial.println("Out of memory");
        return false;
      } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        Serial.println("Peer Exists");
        return true;
      } else {
        Serial.println("Not sure what happened");
        return false;
      }
    }
  } else {
    // No slave found to process
    Serial.println("No Slave found to process");
    return false;
  }
} // fin de la funcion

//-------------------------------------------------------
// Enviar datos
void sendData(paquete data) { // el buffer es el dato que se desea enviar

  const uint8_t *peer_addr = slave.peer_addr;
  Serial.print("Sending: "); Serial.print(sizeof(data)); Serial.println(" bytes.");
  esp_err_t result = esp_now_send(peer_addr, (uint8_t *) &data, sizeof(data));
  Serial.print("Send Status: ");
  if (result == ESP_OK) {
    Serial.println("Success");
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    // How did we get so far!!
    Serial.println("ESPNOW not Init.");
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
    Serial.println("Internal Error");
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } else {
    Serial.println("Not sure what happened");
  }
} // fin de la funcion

//-------------------------------------------------------
// callback cuando los datos son enviados del master al slave
// callback when data is sent from Master to Slave
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Ultimo paquete enviado a: "); Serial.println(macStr);
  Serial.print("Estado del ultimo paquete: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
} // fin de la funcion


//////////////////////////////////////////////////////////
//*/*/*/*/**********************************************
/////////////////////////////////////////////////////////////
// Tarea de ESP-NOW
///////////////////

paquete paqueteEnviar;

void tareaESPNOW(void * parameter){
  WiFi.mode(WIFI_STA); // todos los dispositivos conectados deben estar en este modo
  Serial.println("ESPNow/Basic/Master Example");
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());   // This is the mac address of the Master in Station Mode

  InitESPNow(); // Init ESPNow with a fallback logic
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  ScanForSlave();
  Serial.print("Direccion MAC de este esp: "); Serial.println(WiFi.macAddress());
  uint8_t broadcastAddress[] = {0x84, 0xCC, 0xA8, 0x2F, 0xAD, 0xE4}; // con FF se envia a todos el mensaje // 84:CC:A8:2F:AD:E4 (MAC de placa)
  
  /*
  // El siguiente fragmento es para una prueba>
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;  
  peerInfo.encrypt = false;
    
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  } 
  */
  
  while(true){
    
    // Asignar leturas al paquete
    ADChacerMediciones();  // hace las lecturas
    paqueteEnviar.voltajeA0 = volts0;
    paqueteEnviar.voltajeA1 = volts1;
    paqueteEnviar.voltajeA2 = volts2;
    paqueteEnviar.voltajeA3 = volts3;
    paqueteEnviar.voltajeB0 = 0;
    paqueteEnviar.voltajeB1 = 0;
    paqueteEnviar.voltajeB2 = 0;
    paqueteEnviar.voltajeB3 = 0;

    
    /////////////////////////////////////////////////////////////////////////
    // If Slave is found, it would be populate in `slave` variable
    // We will check if `slave` is defined and then we proceed further
    
    // Lo siguiente es solo de prueba:
    //if (paqueteEnviar.pendiente == true)esp_err_t prueba = esp_now_send(broadcastAddress, (uint8_t *) &paqueteEnviar, sizeof(paqueteEnviar));
    
    if (slave.channel==CHANNEL and paqueteEnviar.pendiente==true) { // check if slave channel is defined, y si está en 1 la variable "pendiente" del paquete
      // `slave` is defined
      // Add slave as peer if it has not been added already
      bool isPaired = manageSlave();
      if (isPaired) {
        // pair success or already paired
        // Send data to device
        //uint8_t * data = (uint8_t *)paqueteEnviar
        sendData(paqueteEnviar);
        
      } else {
        Serial.println("Slave pair failed!");
      }
    } //
    paqueteEnviar.pendiente = true; // restablece el valor de "pendiente", para volver a enviar siempre en este caso
    vTaskDelay(500 / portTICK_PERIOD_MS);

  } // fin de while infinito
  vTaskDelete(NULL); // elimina la tarea
} // fin de tarea
