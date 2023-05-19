#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String deviceName = "ESP32Receptor";

//bool connectedSerialBT;
//String MACadd = "9C:9C:1F:E9:43:02";
//uint8_t address[6]  = {0x9C, 0x9C, 0x1F, 0xE9, 0x43, 0x02};
//uint8_t address[6]  = {0x00, 0x1D, 0xA5, 0x02, 0xC3, 0x22};
//char *pin = "1234"; //<- standard pin would be provided by default

void bluetoothPrintLine(String line)  // envia los datos de caracter en caracter por bluetooth
{
    unsigned l = line.length();
    for(int i=0; i<l; i++)
    {
        if(line[i]!='\0')
            SerialBT.write(byte(line[i]));
    }
    SerialBT.write(10); // \n
}

String bluetoothReadLine()  // lee el mensaje que se está recibiendo por Bluetooth por parte y lo une en una respuesta en forma de String
{
    String response = "";
    while(SerialBT.available())
    {
        byte r = SerialBT.read();
        if(r!=13 && r!=10 && char(r)!='\0')
            response = response + char(r);
    }
    return response;      
}

void tareaSerialBT(void * parameter) {
  SerialBT.begin("ESP32Serial"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  //connectedSerialBT = SerialBT.connect(address); 
  //if (!SerialBT.connected(10000)) Serial.println("Error");
  while (activarSerialBT){
    if (Serial.available()) {
      SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
      bufferBT = bluetoothReadLine(); // ejecuta la funcion que permite recibir el mensaje
      Serial.println(bufferBT);
      mensajeBTrecibido = true; // indica que se terminado de recibir el msg
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
  SerialBT.disconnect(); // desconexion al dispositivo BT
  vTaskDelete(NULL);
} // fin de la tarea
