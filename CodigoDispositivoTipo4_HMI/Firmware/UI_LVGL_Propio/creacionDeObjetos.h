
/*
En este archivo se crean los archivos adicionales que se muestran en la ui

*/

// Para la caja de mensajes
//------------------------------------------------------------------------------------
lv_obj_t * mbox1;

// Crear teclado
//------------------------------------------------------------------------------------
static lv_obj_t * kb;


// Pantalla de los filtros

// Para pantallas creada en SquareLine
//------------------------------------------------------------------------------------
lv_obj_t * ui_Label_JsonRecibido;


// Menu de configuracion
//------------------------------------------------------------------------------------
lv_obj_t * menu;


// Ventana donde se muestran las mediciones de los sensores
//-------------------------------------------------------------------------------------
lv_obj_t * win;
lv_obj_t * tabview;
lv_obj_t * btnTabviewIzq;
lv_obj_t * btnTabviewDer;

// Todos los tab
lv_obj_t * botonEnviar;

// Tab 1
lv_obj_t * dd;               // lista desplegable para seleccion del sensor
static lv_obj_t * meter;
lv_meter_indicator_t * indic;
lv_meter_scale_t * scale; // escala del gauge
lv_obj_t * labelMedida;     // label del medidor Gauge, para mostrar lectura de los sensores
lv_obj_t * labelUnidad;     // label del medidor Gauge, para mostrar unidades de los sensores

lv_obj_t * chart1;
lv_chart_series_t * ser1_1;
lv_chart_series_t * ser2_1;

// Tab 2
lv_obj_t * ddF;               // lista desplegable para seleccion del filtro
lv_obj_t * ddFH;               // lista desplegable para seleccion del horario
lv_obj_t * chart2;
lv_chart_series_t * ser1_2;
lv_chart_series_t * ser2_2;


// Tab 3
lv_obj_t * labelActHorario;

lv_obj_t * rollerHora;
lv_obj_t * rollerMin;


// Tab 4
lv_obj_t * labelEc;

lv_obj_t * cajaTextoCal1;
lv_obj_t * cajaTextoCal2;
lv_obj_t * cajaTextoCal3;

//lv_obj_t * screenMediciones = lv_obj_create(NULL); // crear el objeto pantalla, no funciono asi
//lv_obj_clear_flag(screenMediciones, LV_OBJ_FLAG_SCROLLABLE);    // no funciono asi

// Tab 5
lv_obj_t * slider;
lv_obj_t * sliderVerde;

lv_obj_t * botonInfo;    // boton que muestra informacion sobre el uso

lv_obj_t * cajaTextoMin;
lv_obj_t * cajaTextoMinRojo;
lv_obj_t * cajaTextoMinAma;
lv_obj_t * cajaTextoMaxAma;
lv_obj_t * cajaTextoMaxRojo;
lv_obj_t * cajaTextoMax;
