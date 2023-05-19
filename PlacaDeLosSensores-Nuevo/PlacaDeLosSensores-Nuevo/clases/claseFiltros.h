/* En este archivo se encuentra la definicion de la clase
 *  que permite crear los objetos que representan los filtros
 */

class filtro {
  private:
    
  public:
  // Variables:
  uint16_t numeroDeFiltro;
  uint16_t interruptorA;
  uint16_t interruptorB;
  uint16_t rele;
  bool off = 0; // Permite definir si es logica positiva o negativa
  bool on = 1;  // Permite definir si es logica positiva o negativa

  // Funciones asociadas:
  bool caracteristicas(uint16_t nDeFiltro, uint16_t pinInterruptorA,  uint16_t pinInterruptorB, uint16_t pinRele);
  bool activarLogicaNegativaEnReles();
  bool inicializar(bool activarLogicaNegativa);
  bool colocarEtapaServicio();
  bool aplicarRetrolavado(int segundosRetrolavado, int segundosEnjuague);
};


// Funciones de los objetos de la clase filtro
/////////////////////////////////////////////////////

bool filtro::colocarEtapaServicio(){
  // Esta funcion coloca el filtro en su posicion de servicio
  digitalWrite(rele, on);
  while(digitalRead(interruptorB)){} // esperar hasta llegar a la posicion de servicio
  digitalWrite(rele, off);    // reset de motor
  Serial.println("En estapa de servicio");
  return 1;
}

bool filtro::aplicarRetrolavado(int segundosRetrolavado, int segundosEnjuague){
  // Aplicar un retrolabado de acuerdo con los tiempos indicados
  ////////////////////////////////////////////////////////////
  
  // Asegurarse de que se inicie en la etapa de servicio
  Serial.println("Colocando en posicion de servicio");
  colocarEtapaServicio();

  // Iniciar proceso de retrolavado
  digitalWrite(rele, on); // set del motor
  Serial.println("Esperando A*B");
  while( !(digitalRead(interruptorA) && digitalRead(interruptorB)) ){} // Esperar hasta llegar a la posicion de retrolavado
  digitalWrite(rele, off); // reset del motor
  Serial.println("Primer timer iniciado");
  vTaskDelay(pdMS_TO_TICKS(segundosRetrolavado*1000)); // Esperar en esa posicion el tiempo indicado
  digitalWrite(rele, on); // set del motor
  Serial.println("Esperando !A*B");
  while( !(!digitalRead(interruptorA) && digitalRead(interruptorB)) ){}; // Esperar hasta llegar a la posicion succion y enjuegue
  digitalWrite(rele, off);
  Serial.println("Segundo timer iniciado");
  vTaskDelay(pdMS_TO_TICKS(segundosEnjuague*1000)); // Esperar en esa posicion el tiempo indicado
  
  Serial.println("Regresando a posicion de servicio");
  colocarEtapaServicio(); // Finaliza el proceso volviendo a la etapa de servicio
  Serial.println("Retrolavado finalizado");
  
  return 1;
}

bool filtro::caracteristicas(uint16_t nDeFiltro, uint16_t pinInterruptorA,  uint16_t pinInterruptorB, uint16_t pinRele){
  // Asignar las caracteristicas del filtro
  numeroDeFiltro = nDeFiltro;
  interruptorA = pinInterruptorA;
  interruptorB = pinInterruptorB;
  rele = pinRele;
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
