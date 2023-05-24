#include "HardwareSerial.h"
#include "WString.h"
#include "WiFiClientSecure.h"


const char * host_google = "docs.google.com";
const int httpsPort = 443;

const char * fingerprint = "41:AA:44:D1:73:4F:07:06:2C:89:5C:CD:18:E1:C9:89:FC:E5:13:22";

String MyDoc = "1iiNYd7FqKai0e8jdZsQIS0jPr_CmayX61feQxcJgcA4";
String usp = "pp_url";


int enviarDatosInternet(){
  
  if(WiFi.status()== WL_CONNECTED){ 

    WiFiClientSecure client;
    HTTPClient http;

/*
    if(!client.connect(host_google, httpsPort)){
      Serial.println("Error conectando con Google.");
    } else{
      String getData, url;

      getData = "?usp=" + usp + "&entry.1016553776=12&entry.1220796517=23&entry.574086702=34&entry.1428969291=54&entry.94691886=56&entry.1646211311=67&entry.439089844=87&entry.1066755542=5&entry.789382520=4&entry.827615926=3&entry.1336955858=2&entry.2102956456=true&entry.157041573=true&entry.380290552=false";
      url = "/forms/u/0/d/e/" + MyDoc + "/formResponse" + getData;

      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
        "Host: " + host_google + "\r\n" +
        "Connection: close\r\n\r\n"
      );
      Serial.println("Datos enviados a Google.");
    }
*/


    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName2);

    // Specify content-type header
    //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Content-Type", "text/plain"); // para enviar texto plano
    // Data to send with HTTP POST
    String httpRequestData = "forms/d/e/1FAIpQLSfzXVoGyFJpHrF6s6Slpw7AKSetiaOwNH3qyR-ZRlJg8o9M4A/formResponse?usp=pp_url&entry.1016553776=12&entry.1220796517=23&entry.574086702=34&entry.1428969291=54&entry.94691886=56&entry.1646211311=67&entry.439089844=87&entry.1066755542=5&entry.789382520=4&entry.827615926=3&entry.1336955858=2&entry.2102956456=true&entry.157041573=true&entry.380290552=false";           
    String httpRequestData2 = "search?q=gool&rlz=1C1SQJL_esCR827CR827&oq=gool&aqs=chrome..69i57j0i10i131i433l6j0i10i512j0i10i131i433l2.945j0j7&sourceid=chrome&ie=UTF-8";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData2);
      
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
     
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
        
    // Free resources
    http.end();

    // Retornar el codigo obtenido, 200 indica exito, 404 error
    return httpResponseCode;
  }

  else {
    Serial.println("WiFi Disconnected");
    return 0;
  }

}



//------------------------------------------------------------------------------------------
// Enviar datos a Thingspeak
#include <ThingSpeak.h>          // libreria para usar el servidor ThingSpeak

DynamicJsonDocument jsonBufferTh(1024); // Crear instancia para los documentos JSON
// Liberia para usar JSON
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

bool enviarDatosThingSpeak(String msg){
  WiFiClient ClientThingSpeak;        // crea un objeto del tipo "cliente wifi", que servirá de puente para conectarse al servidor de ThingSpeak 
  ThingSpeak.begin(ClientThingSpeak); // inicializa el cliente del servidor ThingSpeak
                      // espera unos segundos para asegurarse de que se haya establecido la comunicación con el servidor

  DeserializationError error = deserializeJson(jsonBufferTh, msg);
  JsonObject ultimoJsonRecibido = jsonBufferTh.as<JsonObject>();

  ThingSpeak.setField(1,(float) ultimoJsonRecibido["Temp"]);        // asigna el campo donde se guarda la variable
  ThingSpeak.setField(2,(float) ultimoJsonRecibido["pH"]);          // asigna el campo donde se guarda la variable
  ThingSpeak.setField(3,(float) ultimoJsonRecibido["Cond"]);     // asigna el campo donde se guarda la variable
  ThingSpeak.setField(4,(float) ultimoJsonRecibido["Turb"]);      // asigna el campo donde se guarda la variable
  ThingSpeak.setField(5,(float) ultimoJsonRecibido["TDS"]);      // asigna el campo donde se guarda la variable
  //...
    // 
  ThingSpeak.writeFields(channelID,apikey);  // envia los datos

}
