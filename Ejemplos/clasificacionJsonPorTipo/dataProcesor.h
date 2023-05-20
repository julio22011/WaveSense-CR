
/*
 * En este archivo se encuentran las funciones que permiten procesar los datos.
 * En este caso, obtener los datos y acomodarlos en una estructura para que
 * puedan ser utilizados despues.
 * 
*/

#include "dataDistribution.h"

// Requests
//****************************************************************

struct datosProcesados* getRequest(DynamicJsonDocument * doc, struct datosProcesados* datos){
  int command = datos->etiqueta.command;

  // Nota: Los comandos son opuestos, el receptor recibe los commands del emisor
  
  #ifdef isHMI
  switch (command){
    case RestartHMI:          break;
    case ActivateOTA:         break;
    default:                  datos->error = true; break; // activar bandera de error
  }
  #endif

  #ifdef isNET
  switch (command){
    case WiFiSearch:          break;
    case Date:                break;
    case MeshNodesConnected:  break; 
    case RestartNET:          break;
    case SilentAlarmBuzzer:   break;
    default:                  datos->error = true; break; // activar bandera de error
  }
  #endif
  
  return datos;
}

// Answers
//****************************************************************

struct datosProcesados* getAnswer(DynamicJsonDocument * doc, struct datosProcesados* datos){
  int answer = datos->etiqueta.answer;

  // Nota: Los answers son opuestos, el receptor recibe los commands del emisor
  
  #ifdef isHMI
  switch (answer){
    case WifiList:                WifiListSave(doc, datos); break;
    case newWiFiCredOk:           break;
    case timestamp:               break;
    case noTimeError:             break;
    case nodeList:                break;
    case calibOk:                 break;
    case caliError:               break;
    case restartOkNET:            break;
    case restartErrorNET:         break;
    case newPlatformCredOk:       break;
    case emailUpdated:            break;
    case alarmLimUdated:          break;
    case alarmLimError:           break;
    case silentAlarmBuzOk:        break;
    case newFilterScheduleOk:     break;
    case newFilterScheduleError:  break;
    case newConfig1Ok:            break;
    case newConfig1Error:         break;
    case newConfig23Ok:           break;
    case newConfig23Error:        break;
    default:                      datos->error = true; break; // activar bandera de error
  }
  #endif

  #ifdef isNET
  switch (answer){
    case dataRecOk:          Serial.println(); Serial.println("Ejecucion acorde"); break;
    case dataRecError:       break;
    case msgConnRecOk:       break;
    case msgConnRecError:    break;
    case msgAlarmRecOk:      break;
    case msgAlarmRecError:   break;
    case newDataOk:          break;
    case newDataError:       break;
    case restartOk:          break;
    case restartError:       break;
    case activateOTAOk:      break;
    case activateOTAError:   break;
    default:                 datos->error = true; break; // activar bandera de error
  }
  #endif
  
  return datos;
}


// Update
//****************************************************************

struct datosProcesados* getUpdate(DynamicJsonDocument * doc, struct datosProcesados* datos){
  int command = datos->etiqueta.command;

  // Nota: Los answers son opuestos, el receptor recibe los commands del emisor
  
  #ifdef isHMI
  switch (command){
    case ConnectionsChanged:   break;
    default:                   datos->error = true; break; // activar bandera de error
  }
  #endif

  #ifdef isNET
  switch (command){
    case WiFiCredentials:     break;
    case SensorCalibration:   break;
    case PlatformCredentials: break;
    case AlarmEmail:          break;
    case AlarmLimits:         break;
    case FilterSchedule:      break;
    case ConfigDispType1:     break;
    case ConfigDispType23:    break;
    default:                  datos->error = true; break; // activar bandera de error
  }
  #endif
  
  return datos;
}

// Datos
//****************************************************************

struct datosProcesados* getData(DynamicJsonDocument * doc, struct datosProcesados* datos){
  int command = datos->etiqueta.command;

  // Nota: Los answers son opuestos, el receptor recibe los commands del emisor
  
  #ifdef isHMI
  switch (command){
    case MsgPlatform:         break;
    case AlarmGotActivated:   break;
    case NewData:             break;
    default:                  datos->error = true; break; // activar bandera de error
  }
  #endif

  #ifdef isNET
  switch (command){
    default:           datos->error = true; break; // activar bandera de error
  }
  #endif
  
  return datos;
}
