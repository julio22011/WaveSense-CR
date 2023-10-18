
#define pinIn 25
float calibValue = 2.25;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinIn, INPUT);

}


void loop() {
  
  int val = 0;

  for(int i=0; i<=10; i++){
    val += analogRead(pinIn);
    delay(200);
  }

  float voltage = (val/10)*(3.3/4095);
  float corriente = (voltage-calibValue)*30*2/(2^(1/2));

  Serial.print("Voltaje: ");
  Serial.print(voltage);

  Serial.print("Corriente: ");
  Serial.println(corriente);
}
