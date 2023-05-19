
// Incluir archivos
#include "firebaseServices.h"

bool taskCompleted = false;


void setup(){
  setupFirebaseRTDB(); // realiza
}

void loop()
{
  sendDataRTDB();
  delay(30000);
}
