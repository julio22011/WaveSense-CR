
// Estearchivo contine la funcion para iniciar el chip MCP23017, que funciona como un expansor de puertas digitales

void setupMCP(){
  Wire.begin(I2C_SDA, I2C_SCL);   // Inciar I2C con los pines indicados, indicados en variablesYlibrerias

  if (!mcp.begin_I2C()) {
    Serial.println("Error al iniciar MCP.");
  }

  // configuracion de pines como salida/entrada
  for (int i = 0; i<=15 ; i++){
    mcp.pinMode(i, OUTPUT);
  }

  // Cambiar el valor del pin
  for (int i = 0; i<=15 ; i++){
    mcp.digitalWrite(i, LOW);
  }
  mcp.digitalWrite(8,HIGH);
  mcp.digitalWrite(9,HIGH);
  mcp.digitalWrite(10,HIGH);

  // Imprimir condicion
  Serial.println("Configuracion de MCP exitosa.");
}
