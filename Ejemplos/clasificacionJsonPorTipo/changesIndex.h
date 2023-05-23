/*
 * En este archivo se construirá un indice que permite detectar si existe facilmente
 * cuales elementos de la estructura "datosProcesados" han sufrido cambios.
*/

// Bandera principal
//--------------------------------------------
bool pendientChanges = false;


// Matriz de banderas (bool para cada estructura)
//-------------------------------------------
bool * flagsMatrizCommands;
//...
