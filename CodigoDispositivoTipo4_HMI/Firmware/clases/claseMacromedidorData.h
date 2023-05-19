/************************************************************************************************
 * Clase para almacenar los datos recibidos desde los dispositivos tipo 1A y 1B,
 * los cuales registran los caudales de los macromedidores.
************************************************************************************************/

#if !defined(librericaPreferenciasIncluida)
#define librericaPreferenciasIncluida
#include <Preferences.h>                  // incluir libreria que permite guardar Ajustes en la memoria
#endif

#if !defined(claseMacromedidorDataIncluida) // if para evitar ejecutar el mismo codigo dos veces

#define claseMacromedidorDataIncluida

class macromedidorData{
  //
  private:

  float volumenGuardado = -1.0;
  float factorP;


  public:


  // Funciones:
  bool actualizarVolumen(float volumenNuevo);
  bool cargarVolumenGuardado();

};


// Funcion para actualizar el volumen que se encuetra guardado
bool macromedidorData::actualizarVolumen(float volumenNuevo){
  //
}

// Funcion para cargar el dato de volumen guardado en la memoria Spiffs
bool macromedidorData::cargarVolumenGuardado(){
  //
}

#endif