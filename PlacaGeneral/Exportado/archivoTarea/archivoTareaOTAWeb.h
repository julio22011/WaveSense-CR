
/* ***********************************************************************************************
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
archivoTareaOTAWeb.h:
Este es el archivo posee la funcion para ejecutar la tarea para actualizaciones por medio de la Web
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Proyecto WaveSense >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*********************************************************************************************** */


AsyncWebServer server(80);  // crear objeto servidor


void tareaOTAWeb(void * parameter){

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    		request->send(200, "text/plain", "Hi! I am ESP32.");
  	});

  	AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  	server.begin();
  	Serial.println("HTTP server started");

}