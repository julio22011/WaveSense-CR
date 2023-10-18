

#define RXD2 15
#define TXD2 14

// Para esperar a que llegue la respuesta antes de continuar
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial2.available()) 
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

void enviarSMSdePrueba() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

  //////////////////////////
  delay(10000);
  Serial2.println("AT+CPIN=\"8781\""); //Once the handshake test is successful, it will back to OK
  updateSerial();
  Serial2.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial2.println("AT+CMGS=\"+50686314323\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  Serial2.print("Hola desde el ESP32"); //text content
  updateSerial();
  Serial2.write(26);
  //////////////////////////
}

/*
void loop() { //Choose Serial1 or Serial2 as required

  // Traspasar mensaje del serial2 al Serial de depuracion
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }

  /*
  while (Serial.available()) {
    Serial2.print(char(Serial.read()));
  }
  
}
*/
