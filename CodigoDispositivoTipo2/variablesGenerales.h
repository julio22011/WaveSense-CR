
/************************************************************************
Varibles generales para el dispostivo tipo 2 y tipo 3:
  En este archivo se definen algunas de las variables que requiere el
  dispostitivo para su funcionamiento y configuracion.
*************************************************************************/

//=====================================================================
//           Opciones de depuracion
//=====================================================================

//#define depuracionBotones //activa el envio de datos por serial sobre los botones



//=====================================================================
//           Varibles de trabajo
//=====================================================================



//=====================================================================
//           Datos del dispositivo
//=====================================================================
int IDdelDispositivo = 1475025633;


//=====================================================================
//           Pines del conexion
//=====================================================================

// Pines de los interruptores de los filtros
//-----------------------------
// Filtro 1
#define f1_1 4
#define f1_2 27 //
// Filtro 2
#define f2_1 17 //
#define f2_2 35
// Filtro 3
#define f3_1 34
#define f3_2 39  // cambiado

// Pines de los reles de los filtros
//-----------------------------
// Rele doble 1
#define rele1_1 2
#define rele1_2 13
// Rele doble 2
#define rele2_1 26
#define rele2_2 16

// Pines de I2C
//-----------------------------
int I2C_SDA = 22;
int I2C_SCL = 21;

// Pin del buzzer
//-----------------------------
//#define pinBuzzer 12
int pinBuzzer = 12;

// Pin del transistor
//-----------------------------
#define pinTransistor 33

// Definir pines de sensores
//-----------------------------
#define pinADC_pH   2    // Pin del ADC
#define pinADC_Cond 1    // Pin del ADC
#define pinADC_TDS  1    // Pin del ADC
#define pinADC_Turb 0    // Pin del ADC
#define pinADC_Pres 3    // Pin del ADC
#define pin_Temp    15   // Pin del microcontrolador

//=====================================================================
//           Variables de configuracion
//=====================================================================

// Para los botones
//-----------------------------
#define pinDeLosBotones 36
uint8_t tipoBotonesDisp = 0;
//int limitesDeLect[] = {100,3900,4095,2700,3000,1600,2000,600,1000};  // limite de no presionado, limte min y max de cada boton
int limitesDeLect[] = {100,4095,3900,3000,2700,2000,1600,1000,600};  // limite de no presionado, limte min y max de cada boton

// Para la red mesh
//-----------------------------
#define   MESH_PREFIX     "redMeshParqueIndustrialZeta"
#define   MESH_PASSWORD   "TEC_Zeta_acueducto"
#define   MESH_PORT       5555

int msDeMensajeRutinario = 3000;  // tiempo de espera entre los mensajes rutinarios

//=====================================================================
//           FreeRTOS
//=====================================================================
bool aplicandoRetro = false;    // variable para evitar iniciar dos veces las misma tarea
bool yendoPosServicio = false;  // variable para evitar iniciar dos veces las misma tarea
