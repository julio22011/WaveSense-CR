
/*
AsyncWebServer server2(80); // crear servidor

void servidorDeHtml () {
  server2.on("/Mause480", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/Mause480.jpg", "image/jpg");
  });
  
  server2.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/index.html", "text/html");
  });

  server2.serveStatic("/", SD, "/");
  server2.begin();
}
///////////////////////////////////////
*/

void tareaServidor(void * parameter) {
  //server.begin();
  //servidorDeHtml(); // Comentado para poder compilar
  vTaskDelete(NULL); // elimina la tarea ante de llegar al while
  while(activarServidor) {
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    /*
    WiFiClient client = server.available();   // listen for incoming clients
    if (client) {                             // if you get a client,
      Serial.println("New Client.");           // print a message out the serial port
      String currentLine = "";                // make a String to hold incoming data from the client
      while (client.connected()) {            // loop while the client's connected
        if (client.available()) {             // if there's bytes to read from the client,
          char c = client.read();             // read a byte, then
          Serial.write(c);                    // print it out the serial monitor
          if (c == '\n') {                    // if the byte is a newline character
  
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
  
              // the content of the HTTP response follows the header:
              client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
              client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");
  
              // The HTTP response ends with another blank line:
              client.println();
                      //String lectura = readFile(SD, "/index.html");
                      //client.print(lectura);
              // break out of the while loop:
              break;
            } else {    // if you got a newline, then clear currentLine:
              currentLine = "";
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
  
          // Check to see if the client request was "GET /H" or "GET /L":
          if (currentLine.endsWith("GET /H")) {
            digitalWrite(ledRojo, HIGH);               // GET /H turns the LED on
          }
          if (currentLine.endsWith("GET /L")) {
            digitalWrite(ledRojo, LOW);                // GET /L turns the LED off
          }
        }
      }
      // close the connection:
      client.stop();
      Serial.println("Client Disconnected.");
      
    }  */
  } // fin del bucle infinito
  
} //  fin de tarea