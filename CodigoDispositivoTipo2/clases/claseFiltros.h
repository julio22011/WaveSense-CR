/* En este archivo se encuentra la definicion de la clase
 *  que permite crear los objetos que representan los filtros
 */

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif

#if !defined(claseFiltroIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseFiltroIncluida

// Etapas de los filtros
#define etapaTransicion        0
#define etapaServicio          1
#define etapaRetrolavado       2
#define etapaSuccion_Enjuague  3

DynamicJsonDocument jsonBufferFilt(1024); // Crear instancia para los documentos JSON

class filtro {
  private:
    
  public:
  // Variables:
  int numeroDeFiltro;
  uint16_t interruptorA;
  uint16_t interruptorB;
  uint16_t rele;
  bool off = 0; // Permite definir si es logica positiva o negativa
  bool on = 1;  // Permite definir si es logica positiva o negativa

  // Nuevos
  int8_t etapa = 1;
  int tiempoMaximoMotor = 40000;  // Tiempo maximo que puede durar el paso de una etapa a otra
  bool falloMotor = false;        // indica si se ha presentado un falla en el motor por durar mucho en cambiar de etapa
  long int tempAntes;             // variable para almacenar el tiempo antes de entrar a un bucle
  int ID;
  String topic = "filtro";
  JsonObject objetoJson = jsonBufferFilt.to<JsonObject>();
  int pinBuzz;                    // pin para indicar donde esta el buzzer

  int horario1[5];   // activado, hora, min, t1-retro, t2-succ: ejemplo: {1,13,50,15,5} significa activado, a la 1:50 pm con retro: 15min*60, succion: 5 min*60
  int horario2[5];
  int horario3[5];
  int horario4[5];
  int horarioInt[5];  // horario de ejecucion desde la pantalla OLED para pruebas

  float disparoTurbMin = -100.0;
  float disparoTurbMax = 3000.0;
  bool fallaAgua = false;        // para indicar si se ha reportado una falla de agua segun los sensores de agua

  // Objeto para guardar los datos de configuracion:
  Preferences preferences;  // para guardar datos en la memoria NVR

  // Funciones asociadas:
  bool caracteristicas(int nDeFiltro, uint16_t pinInterruptorA,  uint16_t pinInterruptorB, uint16_t pinRele, int pinBuzzer);
  bool activarLogicaNegativaEnReles();
  bool inicializar(bool activarLogicaNegativa);
  bool colocarEtapaServicio();
  bool aplicarRetrolavado(int segundosRetrolavado, int segundosEnjuague);
};


// Funciones de los objetos de la clase filtro
/////////////////////////////////////////////////////

bool filtro::colocarEtapaServicio(){
  // Esta funcion coloca el filtro en su posicion de servicio
  etapa = etapaTransicion;      // colocacion en posicion de servicio 
  digitalWrite(rele, on);

  tempAntes = millis();
  while(digitalRead(interruptorB)){
    vTaskDelay(pdMS_TO_TICKS(200));
    if(millis()-tempAntes > tiempoMaximoMotor){
      falloMotor = true;  // indicar que hubo un falla en el motor si dura mucho
      Serial.println("Hubo un fallo en el motor o los interruptores.");
      etapa = -1;
      digitalWrite(pinBuzz, HIGH); // activa alarma sonora
      return 0;
    }
  } // esperar hasta llegar a la posicion de servicio
  digitalWrite(rele, off);    // reset de motor
  Serial.println("En estapa de servicio");
  etapa = etapaServicio;       // en etapa de servicio
  return 1;
}

bool filtro::aplicarRetrolavado(int segundosRetrolavado, int segundosEnjuague){
  // Aplicar un retrolabado de acuerdo con los tiempos indicados
  ////////////////////////////////////////////////////////////
  
  // Asegurarse de que se inicie en la etapa de servicio
  Serial.println("Colocando en posicion de servicio");
  if (!colocarEtapaServicio()) return 0;       

  // Iniciar proceso de retrolavado
  digitalWrite(rele, on); // set del motor
  Serial.println("Esperando A*B");

  tempAntes = millis();
  while( !(digitalRead(interruptorA) && digitalRead(interruptorB)) ){  // Esperar hasta llegar a la posicion de retrolavado
    vTaskDelay(pdMS_TO_TICKS(200)); // es obligatorio esperar para que funcione mesh
    if(millis()-tempAntes > tiempoMaximoMotor){
      falloMotor = true;  // indicar que hubo un falla en el motor si dura mucho
      Serial.println("Hubo un fallo en el motor o los interruptores.");
      etapa = -1;
      digitalWrite(pinBuzz, HIGH); // activa alarma sonora
      return 0;
    }
  }
  digitalWrite(rele, off); // reset del motor
  Serial.println("Primer timer iniciado");
  etapa = etapaRetrolavado;  
  vTaskDelay(pdMS_TO_TICKS(segundosRetrolavado*1000)); // Esperar en esa posicion el tiempo indicado
  digitalWrite(rele, on); // set del motor
  Serial.println("Esperando !A*B");

  tempAntes = millis();
  while( !(!digitalRead(interruptorA) && digitalRead(interruptorB)) ){  // Esperar hasta llegar a la posicion succion y enjuegue
    vTaskDelay(pdMS_TO_TICKS(200)); // es obligatorio esperar para que funcione mesh
    if(millis()-tempAntes > tiempoMaximoMotor){
      falloMotor = true;  // indicar que hubo un falla en el motor si dura mucho
      Serial.println("Hubo un fallo en el motor o los interruptores.");
      etapa = -1;
      digitalWrite(pinBuzz, HIGH); // activa alarma sonora
      return 0;
    }
  };
  digitalWrite(rele, off);
  Serial.println("Segundo timer iniciado");
  etapa = etapaSuccion_Enjuague;
  vTaskDelay(pdMS_TO_TICKS(segundosEnjuague*1000)); // Esperar en esa posicion el tiempo indicado
  
  Serial.println("Regresando a posicion de servicio");
  if (!colocarEtapaServicio()) return 0;            // Finaliza el proceso volviendo a la etapa de servicio
  Serial.println("Retrolavado finalizado");
  
  return 1;
}

bool filtro::caracteristicas(int nDeFiltro, uint16_t pinInterruptorA,  uint16_t pinInterruptorB, uint16_t pinRele, int pinBuzzer = 12){
  // Asignar las caracteristicas del filtro
  numeroDeFiltro = nDeFiltro;
  interruptorA = pinInterruptorA;
  interruptorB = pinInterruptorB;
  rele = pinRele;
  pinBuzz = pinBuzzer;
  
  return 1;
}

bool filtro::inicializar(bool activarLogicaNegativa = false){
  // Esta función configura el hardware para funcionar correctamente
  if (activarLogicaNegativa) activarLogicaNegativaEnReles(); // Configura reles a logica negativa

  pinMode(interruptorA, INPUT);
  pinMode(interruptorB, INPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, off);  // Apaga el motor de la válvula al inicializar

  return 1;
}

bool filtro::activarLogicaNegativaEnReles(){
  off = 1; // Permite definir si es logica positiva o negativa
  on = 0;  // Permite definir si es logica positiva o negativa
  return 1;
}

#endif
