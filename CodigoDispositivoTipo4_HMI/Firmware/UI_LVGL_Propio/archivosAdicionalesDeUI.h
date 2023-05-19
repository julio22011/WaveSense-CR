
/*
Este archivo permite incluir todos aquellos archivos adicionales que se
requieren para la ui de LVGL.
*/

#if !defined(incluidoCreacionDeObjetos)
#define incluidoCreacionDeObjetos
#include "creacionDeObjetos.h"
#endif

// Archivos con la funciones de UI
#include "cajaDeMensaje.h"
#include "labelDeJson.h"
#include "pantallaDeMediciones.h"
#include "pantallaDeConfiguracion.h"
#include "cajaConexionWiFi.h"
//...


// Eventos de la ui (ubicar despues de todo y antes de ui_mod_init.h)
#include "eventosLVGL.h"

// Archivo que recopila todo
#include "ui_mod_init.h"
