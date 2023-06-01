
/************************************************************************
Funciones de la red mesh
  En este archivo se encuentran las funciones para el uso de la red mesh

*************************************************************************/

void sendMessage(); // prototipo de funcion
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );  // crear tarea de envio de mensajes


void sendMessage() {
  //String msg = "Hi from node1";
  //msg += mesh.getNodeId();
  //mesh.sendBroadcast( msg );
  //mensaje = "Hi from node1"; // provando
  //mensaje += mesh.getNodeId();

  //JsonObject resultadoJsonPru = todosLosSensores[2].obtenerArchivoJson(); // prueba de un solo sensor
  JsonObject resultadoJsonPru = generarJsonDatosRutinarios();               // prueba con paquete general rutinario
  String mensaje;
  serializeJson(resultadoJsonPru, mensaje);
  mesh.sendBroadcast( mensaje );
  //taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 3 )); // Establece un intervalo aleatorio de tiempo

  #if defined(depuracionModoSolitario)
    sendDataRTDB(mensaje, "PriDis2"); // subir datos a Firebase
  #endif
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  //Serial2.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());

  #if defined(depuracionModoSolitario)
  sendDataRTDB(msg, "PriDis2");
  #endif

  // Convertir a Json y procesar los datos recibidos segun su topic:
  DynamicJsonDocument jsonRecibido = genJsonDeString(msg.c_str());  // convertir string recibido a json
  String topic;  // es muy importante que sea String, sino no funcionan las comparaciones
  topic = (const char*) jsonRecibido["topic"];
  int ID = jsonRecibido["ID"];
  int numSensor = (int)jsonRecibido["tipoDeSensor"] - 1;  // permite identificar cual sensor es por medio del tipo

  if(ID == IDdelDispositivo){  // verificar que corresponde con este dispositivo
    if( topic == "Calib" ){
      Serial.println("Calibracion realizada.");
      todosLosSensores[numSensor].actualizarDatosPorJsonCal(jsonRecibido);
    }
    else if( topic == "limit" ){
      Serial.println("Nuevos limites establecidos.");
      todosLosSensores[numSensor].actualizarDatosPorJsonLim(jsonRecibido);  // guardar los datos recibidos en NVS y las clases
      //Serial.println(todosLosSensores[numSensor].limites[0]);  // prueba para ver si se guardo en la clase el valor
      
      // Enviar mensaje de confirmacion:
      mesh.sendBroadcast( genMensajeConfirmacion() );   // generar y enviar el json. La funcion interna esta en multitareaFreeRTOS.h
    }
    else if( topic == "orden" ){
      //
    }
    //... 
  }

  /*
  if(msg == "Hacer retrolavado"){                                                // si el mensaje es hacer retrolavado, inicia los retrolavados
    if(!aplicandoRetro) iniciarTareaEjecucionDeRetrolavadoInterno(2000); // tarea de freRTOS
  }
  if(msg == "Ir a posicion de servicio"){                                                // si el mensaje es hacer retrolavado, inicia los retrolavados
    // tarea de ir a pos de servicio
    if(!yendoPosServicio) iniciarTareaIrPosServicio(2000);
  }
  */
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
  //Serial2.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
  //Serial2.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
  //Serial2.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setupRedMesh(){
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);      // permite que se mantegan coordinados los tiempos de los dispostivos

  mesh.setContainsRoot(true); // debe hacerse en todos los dispositvos
  mesh.initOTAReceive("otareceiverDispTipo2"); // permite recibir actualizaciones por OTA

  userScheduler.addTask( taskSendMessage );
  //taskSendMessage.enable();
}
