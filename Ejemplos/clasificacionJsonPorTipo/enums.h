

// Enums: peermiten clasificar por numero los types, commands, etc., ahorra memoria y otras ventajas de depuracion
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Tipo de comando que se recibe/envía
const char *types[] = {
    "r", // request
    "a", // answer
    "u", // update
    "d"  // datos nuevos
};
enum types {
    r,
    a,
    u,
    d
};

//**********************

const char *commandsHMI[] = {
    "WiFiSearch",
    "WiFiCredentials",
    "Date",
    "MeshNodesConnected",
    "SensorCalibration",
    "RestartNET",
    "PlatformCredentials",
    "AlarmEmail",
    "AlarmLimits",
    "SilentAlarmBuzzer",
    "FilterSchedule",
    "ConfigDispType1",
    "ConfigDispType23"
};
enum commandsHMI {
    WiFiSearch,
    WiFiCredentials,
    Date,
    MeshNodesConnected,
    SensorCalibration,
    RestartNET,
    PlatformCredentials,
    AlarmEmail,
    AlarmLimits,
    SilentAlarmBuzzer,
    FilterSchedule,
    ConfigDispType1,
    ConfigDispType23
};

//**********************

const char *commandsNET[] = {
    "MsgPlatform",
    "ConnectionsChanged",
    "AlarmGotActivated",
    "NewData",
    "RestartHMI",
    "ActivateOTA"
};
enum commandsNET {
    MsgPlatform,
    ConnectionsChanged,
    AlarmGotActivated,
    NewData,
    RestartHMI,
    ActivateOTA
};

//**********************

const char *answersHMI[] = {
    "dataRecOk",
    "dataRecError",
    "msgConnRecOk",
    "msgConnRecError",
    "msgAlarmRecOk",
    "msgAlarmRecError",
    "newDataOk",
    "newDataError",
    "restartOkHMI",
    "restartErrorHMI",
    "activateOTAOk",
    "activateOTAError"
};
enum answersHMI {
    dataRecOk,
    dataRecError,
    msgConnRecOk,
    msgConnRecError,
    msgAlarmRecOk,
    msgAlarmRecError,
    newDataOk,
    newDataError,
    restartOk,
    restartError,
    activateOTAOk,
    activateOTAError
};

//**********************

const char *answersNET[] = {
    "WifiList",
    "newWiFiCredOk",
    "timestamp",
    "noTimeError",
    "nodeList",
    "calibOk",
    "caliError",
    "restartOkNET",
    "restartErrorNET",
    "newPlatformCredOk",
    "emailUpdated",
    "emailUpdateError",
    "alarmLimUdated",
    "alarmLimError",
    "silentAlarmBuzOk",
    "newFilterScheduleOk",
    "newFilterScheduleError",
    "newConfig1Ok",
    "newConfig1Error",
    "newConfig23Ok",
    "newConfig23Error"
};
enum answersNET {
    WifiList,
    newWiFiCredOk,
    timestamp,
    noTimeError,
    nodeList,
    calibOk,
    caliError,
    restartOkNET,
    restartErrorNET,
    newPlatformCredOk,
    emailUpdated,
    emailUpdateError,
    alarmLimUdated,
    alarmLimError,
    silentAlarmBuzOk,
    newFilterScheduleOk,
    newFilterScheduleError,
    newConfig1Ok,
    newConfig1Error,
    newConfig23Ok,
    newConfig23Error
};
