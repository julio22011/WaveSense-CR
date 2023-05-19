
/////////// funciones del GUI de la pantalla /////

// variables y declaraciones involucradas
TFT_eSPI_Button key, key2, key3, key4, key5, key6, key7, key8, key9, key10; // crea el boton
int tiempoVibrato = 30; // ms
uint8_t barIcoNumAnt; // variable para guardar estado anterior del icono de bateria

void dibujarIconoBateria(int posX, int posY){  // tipicos parametros: 430, 5
  // Dibujar icono de bateria
  if(barIcoNum != barIcoNumAnt){ // verifica si es el mismo icono para evitar dibujar en pantalla lo mismo, y asi no gastar CPU
    switch (barIcoNum){
      case 1: drawArrayJpeg(icoBat1, sizeof(icoBat1), posX, posY); break; // dibuja el icono de bateria del 100%
      case 2: drawArrayJpeg(icoBat2, sizeof(icoBat2), posX, posY); break; // dibuja el icono de bateria del 90%
      case 3: drawArrayJpeg(icoBat3, sizeof(icoBat3), posX, posY); break; // dibuja el icono de bateria del 50%
      case 4: drawArrayJpeg(icoBat4, sizeof(icoBat4), posX, posY); break; // dibuja el icono de bateria del 15%
      default: break; // si no se ha leido la bateria, no hace nada
    }
  }
  int barIcoNumAnt = barIcoNum;
  // Lo siguiente imprime el porcentaje de bateria a la par del icono
  int porcentajeDibujado = (int)porcentajeBat;
  tft.setCursor(posX+35, posY, 2);
  tft.printf("%i \45",porcentajeDibujado);
}
void dibujarMenu() {
  // Dibujar barra de notificaciones
  tft.fillRect(0, 0, 480, 25, TFT_BLUE);
  
  /*
  key.initButton(&tft, KEY_X + col * (KEY_W + KEY_SPACING_X),
                        KEY_Y + row * (KEY_H + KEY_SPACING_Y), // x, y, w, h, outline, fill, text
                        KEY_W, KEY_H, TFT_WHITE, keyColor[b], TFT_WHITE,
                        keyLabel[b], KEY_TEXTSIZE);
  */
  key.initButton(&tft,50,100,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_BLUE, TFT_WHITE,
                "Vibrar", 1);
  key2.initButton(&tft,50,180,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_BLUE, TFT_WHITE,
                "Imagen", 1);
  key3.initButton(&tft,50,240,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_RED, TFT_WHITE,
                "Alt. BT", 1);
  key4.initButton(&tft,125,240,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_RED, TFT_WHITE,
                "WiFi", 1);
  key5.initButton(&tft,200,240,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_RED, TFT_WHITE,
                "Servo", 1);
  key6.initButton(&tft,275,240,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_RED, TFT_WHITE,
                "Serial BT", 1);
  key7.initButton(&tft,350,240,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_RED, TFT_WHITE,
                "Servidor", 1);
  key8.initButton(&tft,425,240,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_RED, TFT_WHITE,
                "ESP_NOW", 1);
  key9.initButton(&tft,125,100,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_BLUE, TFT_WHITE,
                "MouseBLE", 1);
  key10.initButton(&tft,125,180,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_BLUE, TFT_WHITE,
                "Grafico", 1);
  
  key.drawButton();
  key2.drawButton();
  key3.drawButton();
  key4.drawButton();
  key5.drawButton();
  key6.drawButton();
  key7.drawButton();
  key8.drawButton();
  key9.drawButton();
  key10.drawButton();
}

char* pantallaBotones () {
  // Boton 1
  if (touchPresionado && key.contains(x, y)) {
    key.press(true);  // tell the button it is pressed
  } else {
    key.press(false);  // tell the button it is NOT pressed
  }
  
  if (key.justPressed()) {
    key.drawButton(true);  // draw invert 
  }
  if (key.justReleased()) key.drawButton();
  if (key.justReleased() && key.contains(x, y)) {
    key.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton vibrar"); 
    return "a"; 
  }

  // Boton 2
  if (touchPresionado && key2.contains(x, y)) {
    key2.press(true);  // tell the button it is pressed
  } else {
    key2.press(false);  // tell the button it is NOT pressed
  }
  
  if (key2.justPressed()) {
    key2.drawButton(true);  // draw invert 
  }
  if (key2.justReleased()) key2.drawButton();
  if (key2.justReleased() && key2.contains(x, y)) {
    key2.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton Img"); 
    return "b";
  }

  // Boton 3
  if (touchPresionado && key3.contains(x, y)) {
    key3.press(true);  // tell the button it is pressed
  } else {
    key3.press(false);  // tell the button it is NOT pressed
  }
  
  if (key3.justPressed()) {
    key3.drawButton(true);  // draw invert 
  }
  if (key3.justReleased()) key3.drawButton();
  if (key3.justReleased() && key3.contains(x, y)) {
    key3.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: BT boton"); 
    return "c";
  }
  // Boton 4
  if (touchPresionado && key4.contains(x, y)) {
    key4.press(true);  // tell the button it is pressed
  } else {
    key4.press(false);  // tell the button it is NOT pressed
  }
  
  if (key4.justPressed()) {
    key4.drawButton(true);  // draw invert 
  }
  if (key4.justReleased()) key4.drawButton();
  if (key4.justReleased() && key4.contains(x, y)) {
    key4.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton de brazo robotico"); 
    return "d";
  }
  // Boton 5
  if (touchPresionado && key5.contains(x, y)) {
    key5.press(true);  // tell the button it is pressed
  } else {
    key5.press(false);  // tell the button it is NOT pressed
  }
  
  if (key5.justPressed()) {
    key5.drawButton(true);  // draw invert 
  }
  if (key5.justReleased()) key5.drawButton();
  if (key5.justReleased() && key5.contains(x, y)) {
    key5.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton de servo"); 
    return "e";
  }

  // Boton 6
  if (touchPresionado && key6.contains(x, y)) {
    key6.press(true);  // tell the button it is pressed
  } else {
    key6.press(false);  // tell the button it is NOT pressed
  }
  
  if (key6.justPressed()) {
    key6.drawButton(true);  // draw invert 
  }
  if (key6.justReleased()) key6.drawButton();
  if (key6.justReleased() && key6.contains(x, y)) {
    key6.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton Serial BT"); 
    return "f";
  }

  // Boton 7
  if (touchPresionado && key7.contains(x, y)) {
    key7.press(true);  // tell the button it is pressed
  } else {
    key7.press(false);  // tell the button it is NOT pressed
  }
  
  if (key7.justPressed()) {
    key7.drawButton(true);  // draw invert 
  }
  if (key7.justReleased()) key7.drawButton();
  if (key7.justReleased() && key7.contains(x, y)) {
    key7.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton Servidor"); 
    return "g";
  }

  // Boton 8
  if (touchPresionado && key8.contains(x, y)) {
    key8.press(true);  // tell the button it is pressed
  } else {
    key8.press(false);  // tell the button it is NOT pressed
  }
  
  if (key8.justPressed()) {
    key8.drawButton(true);  // draw invert 
  }
  if (key8.justReleased()) key8.drawButton();
  if (key8.justReleased() && key8.contains(x, y)) {
    key8.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton ESP_NOW"); 
    return "h";
  }

  // Boton 9
  if (touchPresionado && key9.contains(x, y)) {
    key9.press(true);  // tell the button it is pressed
  } else {
    key9.press(false);  // tell the button it is NOT pressed
  }
  
  if (key9.justPressed()) {
    key9.drawButton(true);  // draw invert 
  }
  if (key9.justReleased()) key9.drawButton();
  if (key9.justReleased() && key9.contains(x, y)) {
    key9.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton ESP_NOW"); 
    return "i";
  }

    // Boton 10
  if (touchPresionado && key10.contains(x, y)) {
    key10.press(true);  // tell the button it is pressed
  } else {
    key10.press(false);  // tell the button it is NOT pressed
  }
  
  if (key10.justPressed()) {
    key10.drawButton(true);  // draw invert 
  }
  if (key10.justReleased()) key10.drawButton();
  if (key10.justReleased() && key10.contains(x, y)) {
    key10.drawButton();     // draw normal
    digitalWrite(vibrador, HIGH);
    vTaskDelay(tiempoVibrato / portTICK_PERIOD_MS);
    digitalWrite(vibrador, LOW);
    Serial.println("Presionado: Boton graficar"); 
    return "j"; 
  }

} //

// la siguiente funcion permite mostrar un mensaje de texto en la tft de manera sencilla
void imprimirMensajeTFT(uint16_t x, uint16_t y, String mensaje, bool esMensaje){
  tft.setTextFont(1);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(x, y, 2);
  if (esMensaje) mensaje = "Mensaje>>> " + mensaje;
  char msg[80];
  mensaje.toCharArray(msg, 80);
  tft.printf(msg); //f
}


//////////////////////////////////////////////////
//////////////Graficos////////////////////////////
//////////////////////////////////////////////////

#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C

#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49

// these are the only external variables used by the graph function
// it's a flag to draw the coordinate system only on the first call to the Graph() function
// and will mimize flicker
// also create some variables to store the old x and y, if you draw 2 graphs on the same display
// you will need to store ox and oy per each display
boolean display1 = true;
boolean update1 = true;

double ox = -999, oy = -999; // Force them to be off screen

/*

  function to draw a cartesian coordinate system and plot whatever data you want
  just pass x and y and the graph will be drawn

  huge arguement list
  &d name of your display object
  x = x data point
  y = y datapont
  gx = x graph location (lower left)
  gy = y graph location (lower left)
  w = width of graph
  h = height of graph
  xlo = lower bound of x axis
  xhi = upper bound of x asis
  xinc = division of x axis (distance not count)
  ylo = lower bound of y axis
  yhi = upper bound of y asis
  yinc = division of y axis (distance not count)
  title = title of graph
  xlabel = x asis label
  ylabel = y asis label
  &redraw = flag to redraw graph on first call only
  color = plotted trace colour
*/


void Graph(TFT_eSPI &tft, double x, double y, byte dp,
                           double gx, double gy, double w, double h,
                           double xlo, double xhi, double xinc,
                           double ylo, double yhi, double yinc,
                           char *title, char *xlabel, char *ylabel,
                           boolean &redraw, unsigned int color) {

  double ydiv, xdiv;
  double i;
  double temp;
  int rot, newrot;

  // gcolor = graph grid colors
  // acolor = axes line colors
  // pcolor = color of your plotted data
  // tcolor = text color
  // bcolor = background color
  unsigned int gcolor = DKBLUE;
  unsigned int acolor = RED;
  unsigned int pcolor = color;
  unsigned int tcolor = WHITE;
  unsigned int bcolor = BLACK;

  if (redraw == true) {

    redraw = false;
    // initialize old x and old y in order to draw the first point of the graph
    // but save the transformed value
    // note my transform funcition is the same as the map function, except the map uses long and we need doubles
    //ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    //oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

    tft.setTextDatum(MR_DATUM);

    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        tft.drawLine(gx, temp, gx + w, temp, acolor);
        tft.setTextColor(acolor, bcolor);
        tft.drawString(xlabel, (int)(gx + w) , (int)temp, 2);
      }
      else {
        tft.drawLine(gx, temp, gx + w, temp, gcolor);
      }
      // draw the axis labels
      tft.setTextColor(tcolor, bcolor);
      // precision is default Arduino--this could really use some format control
      tft.drawFloat(i, dp, gx - 4, temp, 1);
    }

    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        tft.drawLine(temp, gy, temp, gy - h, acolor);
        tft.setTextColor(acolor, bcolor);
        tft.setTextDatum(BC_DATUM);
        tft.drawString(ylabel, (int)temp, (int)(gy - h - 8) , 2);
      }
      else {
        tft.drawLine(temp, gy, temp, gy - h, gcolor);
      }
      // draw the axis labels
      tft.setTextColor(tcolor, bcolor);
      tft.setTextDatum(TC_DATUM);
      // precision is default Arduino--this could really use some format control
      tft.drawFloat(i, dp, temp, gy + 7, 1);
    }

    //now draw the graph labels
    tft.setTextColor(tcolor, bcolor);
    tft.drawString(title, (int)(gx + w / 2) , (int)(gy - h - 30), 4);
  }

  // the coordinates are now drawn, plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized above
  //x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  //y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  //tft.drawLine(ox, oy, x, y, pcolor);
  // it's up to you but drawing 2 more lines to give the graph some thickness
  //tft.drawLine(ox, oy + 1, x, y + 1, pcolor);
  //tft.drawLine(ox, oy - 1, x, y - 1, pcolor);
  //ox = x;
  //oy = y;

}

void Trace(TFT_eSPI &tft, double x,  double y,  byte dp,
           double gx, double gy,
           double w, double h,
           double xlo, double xhi, double xinc,
           double ylo, double yhi, double yinc,
           char *title, char *xlabel, char *ylabel,
           boolean &update1, unsigned int color)
{
  double ydiv, xdiv;
  double i;
  double temp;
  int rot, newrot;

  //unsigned int gcolor = DKBLUE;   // gcolor = graph grid color
  unsigned int acolor = RED;        // acolor = main axes and label color
  unsigned int pcolor = color;      // pcolor = color of your plotted data
  unsigned int tcolor = WHITE;      // tcolor = text color
  unsigned int bcolor = BLACK;      // bcolor = background color

  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  if (update1) {
    update1 = false;
    
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

    if ((ox < gx) || (ox > gx+w)) {update1 = true; return;}
    if ((oy < gy-h) || (oy > gy)) {update1 = true; return;}
    

    tft.setTextDatum(MR_DATUM);

    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        tft.setTextColor(acolor, bcolor);
        tft.drawString(xlabel, (int)(gx + w) , (int)temp, 2);
      }
      // draw the axis labels
      tft.setTextColor(tcolor, bcolor);
      // precision is default Arduino--this could really use some format control
      tft.drawFloat(i, dp, gx - 4, temp, 1);
    }

    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        tft.setTextColor(acolor, bcolor);
        tft.setTextDatum(BC_DATUM);
        tft.drawString(ylabel, (int)temp, (int)(gy - h - 8) , 2);
      }

      // draw the axis labels
      tft.setTextColor(tcolor, bcolor);
      tft.setTextDatum(TC_DATUM);
      // precision is default Arduino--this could really use some format control
      tft.drawFloat(i, dp, temp, gy + 7, 1);
    }

    //now draw the graph labels
    tft.setTextColor(tcolor, bcolor);
    tft.drawString(title, (int)(gx + w / 2) , (int)(gy - h - 30), 4);
  }

  // the coordinates are now drawn, plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

  if ((x < gx) || (x > gx+w)) {update1 = true; return;}
  if ((y < gy-h) || (y > gy)) {update1 = true; return;}
    
    
  tft.drawLine(ox, oy, x, y, pcolor);
  // it's up to you but drawing 2 more lines to give the graph some thickness
  //tft.drawLine(ox, oy + 1, x, y + 1, pcolor);
  //tft.drawLine(ox, oy - 1, x, y - 1, pcolor);
  
  ox = x; // julio
  oy = y;

}

/*
/// funcion para realizar un grafico en vivo (experimental)
void hacerGrafico(){  // dato a graficar, deltaTiempo (Ej. 100 ms), tamaño de buffer (Ej. 60)

  int deltaTiempo = 100;
  int sizeBuf = sizeof(bufferDatosX)/4;
  display1 = true; // poner esto para volver a activar la funcion Graph una vez ya se hizo el grafico

  //Graph(tft, x, y, 1, 60, 290, 390, 260, 0, 6.5, 1, -1, 1, .25, "", "", "", display1, YELLOW); // dibuja la pantalla donde se grafica (Original de referencia)
  Graph(tft, x, y, 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "", "", "", display1, YELLOW); // dibuja la pantalla donde se grafica
  
  int contador = 0;
  float bufferDatosX[sizeBuf];
  float bufferDatosY[sizeBuf]; //sizeBuf

  // Crea el vector para los datos del eje X:
  for (int i = 0; i <= sizeBuf; i+=1) {  // usar sizeof
    bufferDatosX[i] = (float)i/10;
    Serial.println((float)i/10);
  }

  while(true){
    float valorGraficado = (float)lecturaAnalogoX/1000;
    display1 = true; // activa la funcion graph
    if (contador < sizeBuf) {
      contador = contador + 1;
      update1 = true;
      bufferDatosY[contador] = valorGraficado;
      for (int u = 0; u <= contador; u += 1) {  // este for dibuja los puntos del grafico
        Trace(tft, bufferDatosX[u], bufferDatosY[u], 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "Grafico de pH", "t", "pH", update1, YELLOW);
      }
    }
    // El siguiete else se activa cuando ya se ha completado de llenar la pantalla y los datos antiguos tienen que comenzar a desplazarse hacia la izquierda
    else{
      for (int u = 0; u <= contador; u += 1) {  // Este "for" dibuja los puntos antiguos del grafico en negro para borrarlos
        Trace(tft, bufferDatosX[u], bufferDatosY[u], 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "Grafico de pH", "t", "pH", update1, BLACK);
      }
      for(int p = 0; p < sizeBuf; p++){ // Este "for" mueve cada data del vector un espacio hacia la izuierda, para ir moviendo todo el grafico hacia la izquierda
        bufferDatosY[p] = bufferDatosY[p+1];  
      }
      ////////Lo siguiente imprime la Grafica actualizada
      update1 = true;
      bufferDatosY[contador-1] = valorGraficado;
      for (int u = 0; u < contador; u += 1) {  // este for dibuja los puntos del grafico
        Trace(tft, bufferDatosX[u], bufferDatosY[u], 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "Grafico de pH", "t", "pH", update1, YELLOW);
      }
    }
    vTaskDelay(deltaTiempo / portTICK_PERIOD_MS);
    Graph(tft, x, y, 1, 60*4, 190, 230, 260/2, 0, 6.5, 1, 0, 5, 1, "", "", "", display1, YELLOW); // dibuja la pantalla donde se grafica
  }

} // fin de funcion

//////////////////////////////////////////////
*/


/* En desarrollo

const char* textoBotones[5][5] = {{"A","B","C","D","E"},{"1","2","3","4","5"},{"6","7","8","9","0"},{"!","@","#","$","%"},{"^","&","*","(",")"}};
int filas = (sizeof(textoBotones)/sizeof(textoBotones[0]));
int columnas = (sizeof(textoBotones[0])/sizeof(textoBotones[0][0]));

TFT_eSPI_Button teclado[25];

void dibujarTeclado(){
  for (int i = 0; i < filas; i++){
    for (int j = 0; j < columnas; j++){
      teclado[].initButton(&tft,50,100,                               // x, y, w, h, outline, fill, text
                70, 35, TFT_WHITE, TFT_BLUE, TFT_DARKGREY,
                "Vibrar", 1);
  
      teclado[].drawButton();
    }
  }
} // fin de func

char* teclado() {
  // dibujar el teclado
  dibujarTeclado();
  return "b";
} // fin de func

*/