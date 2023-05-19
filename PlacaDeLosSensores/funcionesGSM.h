// El siguiente código permite enviar mensajes GSM al encargado de la ASADA, para avisar sobre las condiciones
// de los sensores. La manera de usar este código es a través de las funciones: setupModemGSM() [la cual configura el modem] y enviarMensajeGSM(String mensaje) [la cual envía el msg SMS]
// Para más detalles sobre su programación ver https://randomnerdtutorials.com/esp32-sim800l-send-text-messages-sms/
                                                                                                                                                                                                            // También podría permitir enviar desde el teléfono un mensaje para consultar los valores actuales de los sensores.
const char simPIN[]   = "8781";  // indicar el pin de la tarjeta sim, si no tiene dejarlo vacío
#define SMS_TARGET  "+50685130093"  // indica el número de teléfono a quien le llegarán los mensajes

// Configurar la librería TinyGSM
#define TINY_GSM_MODEM_SIM800      // Le indica a la librería que el Modem que posee la placa es el SIM800
#define TINY_GSM_RX_BUFFER   1024  // Setea una cantidad de buffer para el Modem, se usará 1Kb (1024)

// Los siguiente le indica a la libreria en qué pines está conectado el modem GSM sobre la placa TTGO T-Call;
// ya que normalmente el modem GSM se vende por separado, pero está directamente integrado sobre esta placa.
// Estos pines no se pueden usar para ninguna función más ya que están siendo usados por el modem.
//#define MODEM_RST            27 //5
//#define MODEM_PWKEY          4   //
//#define MODEM_POWER_ON       23
#define MODEM_TX             1  //1
#define MODEM_RX             3   // 3
//#define I2C_SDA              21
//#define I2C_SCL              22


#include <TinyGsmClient.h>  // incluye la librería que permite controlar el modem GSM de la placa

#define SerialAT  Serial1 // Crea un puerto serial para comunicarse con el Modem GSM mediante comandos AT
                          // (AT o comandos Hayes es un protocolo de comandos que permite comunicación con chips generalmente de telecomunicaciones)


// Lo siguiente es para la depuracion del modem
#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, Serial);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif


bool setupModemGSM() {     // esta función debe ejecutarse dentro del setup principal
  // Lo siguiente configura los pines conectados al modem
  //pinMode(MODEM_PWKEY, OUTPUT);
  //pinMode(MODEM_RST, OUTPUT);
  //pinMode(MODEM_POWER_ON, OUTPUT);
  //digitalWrite(MODEM_PWKEY, LOW);
  //digitalWrite(MODEM_RST, HIGH);
  //digitalWrite(MODEM_POWER_ON, HIGH);

  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX); // inicia comunicación serial con el modem a 115200 baudios

  Serial.println("Iniciando modem GSM");  // envia por serial USB un aviso de que se está conectando con el modem GSM
  //modem.restart();    // usar modem.init() si no se necesita reiniciar por completo el modem
  modem.init();
  
  // Lo siguiente desbloquea la sim con el pin si es necesario
  if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
    if (modem.simUnlock(simPIN)){
      Serial.println("Tarjeta SIM desbloqueada.");
    }
  }
  return true; // retorna en la función un valor booleano verdadero, para indicar que se ha terminado la inicialización del modem
  
} // fin del setup del modem GSM


bool enviarMensajeGSM(String mensaje) {
  Serial.println(modem.getSimStatus());
  if(modem.sendSMS(SMS_TARGET, mensaje)){    // Envía el mensaje y al mismo tiempo verifica si se ha enviado con el "if", ya que modem.sendSMS devuelve "true" si es exitoso. 
    //enviadoSMS = true;
    Serial.println("Mensaje SMS enviado: " + mensaje);                 // Imprime en el monitor serial USB el mensaje que se envió
  }
  else{
    Serial.println("Falló el envío del mensaje GSM.");
  }
} // fin de la función