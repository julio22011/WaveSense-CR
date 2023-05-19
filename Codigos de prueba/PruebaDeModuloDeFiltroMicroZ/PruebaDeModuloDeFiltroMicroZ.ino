////////////////////////
// Filtro 1
#define f1_1 4
#define f1_2 27 //

// Filtro 2
#define f2_1 17 //
#define f2_2 35

// Filtro 3
#define f3_1 34
#define f3_2 36
/////////////////////////
// Rele doble 1
#define rele1_1 2
#define rele1_2 13

// Rele doble 2
#define rele2_1 26
#define rele2_2 16
/////////////////////////

void setup() {
  Serial.begin(115200);

  // Configuracion de pines

  // Pines de entrada
  pinMode(f1_1, INPUT);
  pinMode(f1_2, INPUT);

  pinMode(f2_1, INPUT);
  pinMode(f2_2, INPUT);

  pinMode(f3_1, INPUT);
  pinMode(f3_2, INPUT);
  
  // Pines de salida
  pinMode(rele1_1, OUTPUT);
  pinMode(rele1_2, OUTPUT);
  pinMode(rele2_1, OUTPUT);
  pinMode(rele2_2, OUTPUT);

  digitalWrite(rele1_1, HIGH);
  digitalWrite(rele1_2, HIGH);
  digitalWrite(rele2_1, HIGH);
  digitalWrite(rele2_2, HIGH);
}

void loop() {
  /* Verificacion de funcionamieto de las
     señales de los interruptores. */
  if (!digitalRead(f1_1)){
    Serial.println("Filtro 1_1");
    delay(200);
    //
    digitalWrite(rele1_1, HIGH);
  } else if (!digitalRead(f1_2)){  // 
    Serial.println("Filtro 1_2");
    delay(200);
    //
    digitalWrite(rele1_2, HIGH);
  } else if (!digitalRead(f2_1)){ // 
    Serial.println("Filtro 2_1");
    delay(200);
    //
    digitalWrite(rele2_1, HIGH);
  } else if (!digitalRead(f2_2)){
    Serial.println("Filtro 2_2");
    delay(200);
    //
    digitalWrite(rele2_2, HIGH);
  } else if (!digitalRead(f3_1)){
    Serial.println("Filtro 3_1");
    delay(200);
    //
    digitalWrite(rele1_1, LOW);
    digitalWrite(rele1_2, LOW);
    digitalWrite(rele2_1, LOW);
    digitalWrite(rele2_2, LOW);
  } else if (!digitalRead(f3_2)){
    Serial.println("Filtro 3_2");
    delay(200);
  }
} // fin del loop
