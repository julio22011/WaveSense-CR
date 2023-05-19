

// Esta tarea permite probar el funcionamiento de un servo motor en el pin 14 (4 de las salidas del dispositivo)
void tareaServo (void * parameter){
  Servo myservo; // crea el servo
  int pinServo = 14;
  // Published values for SG90 servos; adjust if needed
  int minUs = 500;
  int maxUs = 2500;

  while(activarServo){
    if (!myservo.attached()) {
        myservo.setPeriodHertz(50); // standard 50 hz servo
        myservo.attach(pinServo, minUs, maxUs); // Attach the servo after it has been detatched
    }
    myservo.write(90);
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    myservo.write(0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  } // fin del bucle infinito
  myservo.detach(); // Turn the servo off
  vTaskDelete(NULL); // elimina la tarea al salir del bucle infinito
} // fin de tarea