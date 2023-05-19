//**************************************************
//  En este archivo contine lo requerido para controlar 
//  los ampliadores de puestas por I2C.
//**************************************************

//=====================================================================
//           Parametros generales de los chips
//=====================================================================

#define mcp1_ADDRESS 0x20 // direccion del primer mcp23017
//#define mcp2_ADDRESS 0x20 // direccion del segundo mcp23017

//=====================================================================
//           Funciones de configuracion
//=====================================================================

void setupDeAmpliadoresDePuertas(){
  // MCP23017
  if (!mcp.begin_I2C(0x20)) {      // )x20 e la dirreccion
    Serial.println("Error inician mcp1.");
    //while (1);
  }
//  if (!mcp.begin_I2C(0x20)) {      // )x20 e la dirreccion
//    Serial.println("Error inician mcp1.");
//    //while (1);
//  }

  // configure pin for output
  //----------------------------
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);
}
