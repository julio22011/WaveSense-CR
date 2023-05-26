
/*********************************************************************************
 *Este archivo contiene el codigo de programacion para la HMI del dispositivo tipo 4,
 * es decri, para el ESP32 del lado derecho del dispositivo (detras de los botones).
 *
**********************************************************************************/
//bool mbedtls_md5_starts = true; // da error (aparece con la actualizacion)

// Activacion de opciones de depuracion
//-----------------------------------------------
//#define depuracionBotones   // activa la depuracion de la clase botones (esta dando error al arrancar)
//#define depuracionDeMemoria // Muestra en parte superior de la pantalla los datos de memoria
//#define depuracionDeBateria   // activa la impresion del voltaje y porcentaje de la bateria
//#define borrarNVS           // activa reset de la particion NVS
#define activarAnimacionDePruebaRoller
//#define activarDepuracionTouch

// Archivo de librerias, variables, objetos y configuracion
//-----------------------------------------------
#include "variablesGenerales.h" // ubicar al inicio del programa

// Archivos para el uso de la pantalla (UI y drivers de pantalla)
//-----------------------------------------------
#include "ui.h"                                       // Los archivos de la ui de SquareLine debe ubicarse en la misma carpeta que el ino
#include "ConfiguracionDePantalla/MyDisplaySetup.h"   // posee las configuraciones para la pantalla, para configurar los drivers

// Archivos adicionales de la UI
//-----------------------------------------------
#include "UI_LVGL_Propio/archivosAdicionalesDeUI.h"   // archivo que recopila todos los archivos adicionales de la ui

// Archivo para la configuracion del expansor de puertas MCP23017
//-----------------------------------------------                     
#include "ExpansorDePuertas/ExpansorPuertasInit.h"

// Cabecera para el manejo de freeRTOS
//-----------------------------------------------   
#include "cabeceraRTOS.h"

void setup() {
  #ifdef borrarNVS
    nvs_flash_erase();
    nvs_flash_init();
  #endif
  
  Serial.begin(115200);

  pinMode(fotocelda, INPUT); // de prueba

  // Configurar botones:
  botonesHMI.iniciar(
    pinDeLosBotones, 
    tipoBotonesDisp, 
    limitesDeLect, 
    pinTransistor, 
    analogoX, 
    analogoY, 
    limitesDeLectJoy); // int pin = 36, uint8_t tipo = 0, int *limitesDeLectura = NULL  // pinTransistor 
  
  setupPantalla();           // inicia la pantalla, funcion del archivo "ConfiguracionDePantalla/MyDisplaySetup.h"
  setupMCP();                // inicia MCP23017, funcion del archivo "ExpansorDePuertas/ExpansorPuertasInit.h"
  iniciarUART_ESP32_2(5000); // Inicia programa para recibrir datos por Uart de la ESP32 de la red mesh

  // Restaurar los datos de red guardados e intentar conectar
  //tryPreviousNetwork();
  preferences.begin("settings"); // iniciar las preferencias
  recuperarContasenaWiFi();

  // Configurar gestor de mensajes, filtrosData y sensoresData
  setupDeData();

  // Iniciar tarea para obtner la fecha y hora
  iniciarFechaHora(10000);

  // Iniciar la memoeria spiffs
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");   // indica si huo un fallo
        return;
  }

  // Iniciar la tarea de los botones
  iniciarBotones(1024);

  // Incio de OTA;l
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  Serial.println("OTA por navegador iniciado.");
  Serial.println(WiFi.localIP());
  server.begin();

  // Inicio de la interfaz grafica
  ui_init();                 // iniciar interfaz LVGL de SquareLine
  ui_mod_init();             // Realiza las modificaciones a la interfaz grafica de SquareLine
  bateriaUI.iniciar(bateria, ui_Principal, ui_LabelBotonMesh);
  
  // Timer que actualiza la bateria cada 1s
  static uint32_t user_data = 10;
  timer = lv_timer_create(actualizarBatUI, 1000, &user_data);  // NULL, &user_data

  // Tarea de actualizacion de datos del Gauge
  //iniciarActualizarDatos(2000);  // no funciona asi, tiene que ser por refresh de LVGL
}

void loop() {
  lv_timer_handler();             // Mantiene en ejecucion la libreria grafica
  vTaskDelay( pdMS_TO_TICKS(5) ); // Espera para evitar sobrecargar el procesador

  recibirDatos();              // debe ir en una tarea aparte
  actulizacionDeHoraUI();      // cambia el estado de la hora // Nota: mejor cambiarlo por un timer de lvgl

  // Nota: mejor cambiarlo por un timer de lvgl
  #ifdef depuracionDeMemoria 
    //Serial.println(uxTaskGetStackHighWaterMark(NULL)); // esp_get_free_heap_size()  uxTaskGetStackHighWaterMark(NULL)
    tft.drawString("Stack M:", 5, 5);  // tft.drawNumber(123, 100, 10);  tft.drawFloat(3.14, 2, 150, 10);
    tft.drawNumber(uxTaskGetStackHighWaterMark(NULL), 60, 5);  // uxTaskGetStackHighWaterMark(NULL) 
    tft.drawString("Heap:", 100, 5);
    tft.drawNumber(esp_get_free_heap_size(), 130, 5);  // uxTaskGetStackHighWaterMark(NULL) 
  #endif

}

// Funcion que se verifica si se ha recibido un mensaje nuevo y activa el gestor de mensajes
void recibirDatos(){
  if (mensajeNuevo){
    int tipoMsgRecibido = gestorMensajes.entregarMensajeRecibido(datoRecibido);
    //Serial.println(todosLosSensoresData[2].lecturaDigital);           // no funciona asi, debe ser desde los asociados
    //Serial.println(gestorMensajes.sensoresAsociados[2].temperatura);    // imprimir valor para ver si se guardo
    
    // Incluir en el gestor de mensajes una funcion para almacenar datos en sniffs
    // ...

    // LVGL
    //char bufferTemperatura[10];
    //sprintf(bufferTemperatura, "%f", gestorMensajes.sensoresAsociados[2].temperatura); // para pasar de float a char*
    //lv_label_set_text(ui_Label_JsonRecibido, bufferTemperatura); // mostrar en la etiqueta la lectura de teemp recibida

    // Acciones si es una confirmacion de recibido
    if(tipoMsgRecibido == 4){  // si es un mensaje de tipo confirmacion(4):
      //cuenta = 0; // resetea la cuenta> necesario al usar variables estaticas, da error aqui
      //lv_timer_del(timerConf);  // Terminar tarea, esta dando reincios
      cuentaConf = 22;
      //lv_timer_reset(timerConf); // disparar timer antes de tiempo para ejecutar de inmediato el cierre de la ventana, el fin de la tarea, etc. 
      lv_msgbox_close(mbox1); // cerrar msgbox anterior
      lv_example_msgbox_1("Exito", "Ajustes nuevos recibidos con exito.");
    }

    // Refrescar Guage
    lv_event_send(meter, LV_EVENT_REFRESH, NULL);
    //lv_event_send_refresh(meter); // No funciona
     
    mensajeNuevo = false;  // Indicar que ya se registro el ultimo mensaje

    // Agregar funcion de cambio de datos de los graficos
    // ...
  }
}

void setupDeData(){
  // Inciar los sensores:
  todosLosSensoresData[0].inicializar("Temp", sensorTemp);
  todosLosSensoresData[1].inicializar("pH  ", sensorPH);
  todosLosSensoresData[2].inicializar("Cond", sensorConductividad);
  todosLosSensoresData[3].inicializar("Turb", sensorTurbidez);
  todosLosSensoresData[4].inicializar("TDS ", sensorTDS);
  todosLosSensoresData[5].inicializar("Pres", sensorPres);
  todosLosSensoresData[6].inicializar("Caud", sensorCaudal);

  todosLosFitrosData[0].inicializar(1);
  todosLosFitrosData[1].inicializar(2);
  todosLosFitrosData[2].inicializar(3);  

  gestorMensajes.asociarObjetos(todosLosSensoresData, todosLosFitrosData, 7,3);          //sensorData *sensores, filtroData *filtros, int numSensores, int numFiltros
}

void actulizacionDeHoraUI(){
  if (actualizarHora && !errorEnHora){
    char bufferHora[10];
    int hora = timeinfo.tm_hour;
    int minuto = timeinfo.tm_min;
    if(minuto<10){
      sprintf(bufferHora, "%i:0%i", hora, minuto); // para pasar de int a char* y darle el formato de hora
    } else{
      sprintf(bufferHora, "%i:%i", hora, minuto); // para pasar de int a char* y darle el formato de hora
    }
    lv_label_set_text(ui_LabelHora, bufferHora);   

    actualizarHora = false;
  } else if(errorEnHora){
    lv_label_set_text(ui_LabelHora, "Error"); 

    // Reiniciar tarea de fechaHora para volver a intentar:
    //vTaskDelete(tarFechaHora);   // problema con el Handle
    //iniciarFechaHora(10000);   
  }
}
