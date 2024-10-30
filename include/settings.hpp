// definicion de funciones
boolean settingsRead();
boolean settingsSave();
void settingsReset();

// funcion que leera el archivo settings.json devolviendo un true o false
//  documentación www.arduinojson.org/v7/
//  la nueva version de JSON ya calcula el tamaño (excelente)

boolean settingsRead()
{
    JsonDocument jsonSettings;                            // objeto jsonSettings donde se leeran las configuraciones iniciales
    File file = SPIFFS.open("/settings.json", FILE_READ); // modo lectura antes o tambien en vez de FILE_READ , "r"

    if (!file)
    { // instalar la extencion TODO Highlight
        // FIXME: Serial.println("[WARNING][settings.hpp][settingsRead()]Falla en abrir el archivo settings.json");
        // dejare ese FIXME como ejemplo pero la siguiente linea es la solucion
        myLog("ERROR", "settings.hpp", "settingsRead()", "Error al abrir el archivo settings.json o este no existe");
        // TODO: llamar a la función de iniciar el json de fabrica (HECHO)
        settingsReset();
        return false;
    }
    // Deserealizacion del archivo settings.json osea, lo que esta en el archivo file
    // lo pazamos a la variable jsonSettings gracias a la funcion deserializeJson() y
    // si eso no sucede dará un error
    // la deseralizeJson() si todo sale ok devuelve un 0 o false indicando que no hay error
    // en caso contrario da
    DeserializationError error = deserializeJson(jsonSettings, file);
    // cerramos el archivo este paso es necesario ya que ya no o usaremos y con esto liberamos memoria
    file.close();
    // si se presenta un error
    if (error)
    {
        myLog("ERROR", "settings.hpp", "settingsRead()", "Fallo la deserealización del archivo settings.json");
        settingsReset();
        return false;
    }
    myLog("INFO", "settings.hpp", "settingsRead()", "Se procede a asignar valores almacenados a las variables");
    // si ya pasamos todos esos errores, pasaremos a copiar los valores del archivo json a las variables globales
    // como son de tipo char
    strlcpy(device_id, jsonSettings["device_id"] | "", sizeof(device_id));                   // si no hay nada lo pone vacio
    strlcpy(device_name, jsonSettings["device_name"] | "", sizeof(device_name));             // si no hay nada lo pone vacio
    strlcpy(device_user, jsonSettings["device_user"] | "", sizeof(device_user));             // si no hay nada lo pone vacio
    strlcpy(device_password, jsonSettings["device_password"] | "", sizeof(device_password)); // si no hay nada lo pone vacio
    // wifi modo estación
    // como el siguiente es un boolean es de la siguiente manera o si son numeros enteros
    wifi_mode = jsonSettings["wifi"]["wifi_mode"] | false; // si no viene nada se pone en false
    strlcpy(wifi_ssid, jsonSettings["wifi"]["wifi_ssid"] | "", sizeof(wifi_ssid));
    strlcpy(wifi_password, jsonSettings["wifi"]["wifi_password"] | "", sizeof(wifi_password));
    wifi_dhcp = jsonSettings["wifi"]["wifi_dhcp"] | false; // si no viene nada se pone en false
    strlcpy(wifi_ipv4, jsonSettings["wifi"]["wifi_ipv4"] | "", sizeof(wifi_ipv4));
    strlcpy(wifi_subnet, jsonSettings["wifi"]["wifi_subnet"] | "", sizeof(wifi_subnet));
    strlcpy(wifi_gateway, jsonSettings["wifi"]["wifi_gateway"] | "", sizeof(wifi_gateway));
    strlcpy(wifi_dns_primary, jsonSettings["wifi"]["wifi_dns_primary"] | "", sizeof(wifi_dns_primary));
    strlcpy(wifi_dns_secondary, jsonSettings["wifi"]["wifi_dns_secondary"] | "", sizeof(wifi_dns_secondary));
    // wifi ap
    strlcpy(ap_ssid, jsonSettings["wifi"]["ap_ssid"] | "", sizeof(ap_ssid));
    strlcpy(ap_password, jsonSettings["wifi"]["ap_password"] | "", sizeof(ap_password));
    ap_channel = jsonSettings["wifi"]["ap_channel"] | 1;
    ap_visibility = jsonSettings["wifi"]["ap_visibility"] | false; // 0 es para que se vea
    ap_connect = jsonSettings["wifi"]["ap_connect"] | 3;           // cantidad de conexiones en modo AP
    // MQTT
    mqtt_enabled = jsonSettings["mqtt"]["mqtt_enabled"] | false;
    strlcpy(mqtt_server, jsonSettings["mqtt"]["mqtt_server"] | "", sizeof(mqtt_server));
    mqtt_port = jsonSettings["mqtt"]["mqtt_port"] | 1883;
    mqtt_retain = jsonSettings["mqtt"]["mqtt_retain"] | false;
    mqtt_qos = jsonSettings["mqtt"]["mqtt_qos"] | 0;
    strlcpy(mqtt_id, jsonSettings["mqtt"]["mqtt_id"] | "", sizeof(mqtt_id));
    strlcpy(mqtt_user, jsonSettings["mqtt"]["mqtt_user"] | "", sizeof(mqtt_user));
    strlcpy(mqtt_password, jsonSettings["mqtt"]["mqtt_password"] | "", sizeof(mqtt_password));
    mqtt_clean_session = jsonSettings["mqtt"]["mqtt_clean_session"] | false;
    strlcpy(mqtt_commandTopic, jsonSettings["mqtt"]["mqtt_commandTopic"] | "", sizeof(mqtt_commandTopic));
    strlcpy(mqtt_sendTopic, jsonSettings["mqtt"]["mqtt_sendTopic"] | "", sizeof(mqtt_sendTopic));
    strlcpy(mqtt_willTopic, jsonSettings["mqtt"]["mqtt_willTopic"] | "", sizeof(mqtt_willTopic));
    strlcpy(mqtt_willMessage, jsonSettings["mqtt"]["mqtt_willMessage"] | "", sizeof(mqtt_willMessage));
    mqtt_willQos = jsonSettings["mqtt"]["mqtt_willQos"] | 0;
    mqtt_willRetain = jsonSettings["mqtt"]["mqtt_willRetain"] | false;
    mqtt_time_send = jsonSettings["mqtt"]["mqtt_time_send"] | false;
    mqtt_time_interval = jsonSettings["mqtt"]["mqtt_time_interval"] | 60; // 60 es el standard
    mqtt_status_send = jsonSettings["mqtt"]["mqtt_status_send"] | false;
    RELAY1_STATUS = jsonSettings["relay"]["RELAY1_STATUS"] | false;
    RELAY2_STATUS = jsonSettings["relay"]["RELAY2_STATUS"] | false;
    // DIMER
    dim = jsonSettings["dimer"]["dim_value"] | 0;
    // ---------------------------------------------------------
    //  ZONA DE ALARMAS
    // ---------------------------------------------------------
    ALARM_LOGICA1 = jsonSettings["ALARM_LOGICA1"].as<bool>();
    ALARM_NAME1 = jsonSettings["ALARM_NAME1"].as<String>();
    ALARM_LOGICA2 = jsonSettings["ALARM_LOGICA2"].as<bool>();
    ALARM_NAME2 = jsonSettings["ALARM_NAME2"].as<String>();
    ALARM_LOGICA3 = jsonSettings["ALARM_LOGICA3"].as<bool>();
    ALARM_NAME3 = jsonSettings["ALARM_NAME3"].as<String>();
    ALARM_LOGICA4 = jsonSettings["ALARM_LOGICA4"].as<bool>();
    ALARM_NAME4 = jsonSettings["ALARM_NAME4"].as<String>();
    ALARM_LOGICA5 = jsonSettings["ALARM_LOGICA5"].as<bool>();
    ALARM_NAME5 = jsonSettings["ALARM_NAME5"].as<String>();
    ALARM_LOGICA6 = jsonSettings["ALARM_LOGICA6"].as<bool>();
    ALARM_NAME6 = jsonSettings["ALARM_NAME6"].as<String>();
    ALARM_LOGICA7 = jsonSettings["ALARM_LOGICA7"].as<bool>();
    ALARM_NAME7 = jsonSettings["ALARM_NAME7"].as<String>();
    ALARM_LOGICA8 = jsonSettings["ALARM_LOGICA8"].as<bool>();
    ALARM_NAME8 = jsonSettings["ALARM_NAME8"].as<String>();
    // log
    myLog("INFO", "settings.hpp", "settingsRead()", "lecturas de las configuraciones correctamente");
    return true;
}

// Funcion que resetea a los valores de fabrica
void settingsReset()
{
    myLog("INFO", "settings.hpp", "settingsReset()", "Se procede a asignar valores de fabrica");
    strlcpy(device_id, DeviceID().c_str(), sizeof(device_id));
    strlcpy(device_name, DeviceName.c_str(), sizeof(device_name));
    // TODO: ver si jala el archivo var_entorno
    strlcpy(device_user, Administrador.c_str(), sizeof(device_user));
    strlcpy(device_password, Contra.c_str(), sizeof(device_password));
    // wifi modo estación
    // como el siguiente es un boolean es de la siguiente manera o si son numeros enteros
    wifi_mode = true; // true es modo estación
    strlcpy(wifi_ssid, SSID.c_str(), sizeof(wifi_ssid));
    strlcpy(wifi_password, WifiPassword.c_str(), sizeof(wifi_password));
    wifi_dhcp = DHCP; // para configurar con ips fijas
    strlcpy(wifi_ipv4, Ipv4.c_str(), sizeof(wifi_ipv4));
    strlcpy(wifi_subnet, SubRed.c_str(), sizeof(wifi_subnet));
    strlcpy(wifi_gateway, Gateway.c_str(), sizeof(wifi_gateway));
    strlcpy(wifi_dns_primary, DnsPrimary.c_str(), sizeof(wifi_dns_primary));
    strlcpy(wifi_dns_secondary, DnsSecondary.c_str(), sizeof(wifi_dns_secondary));
    // wifi ap
    strlcpy(ap_ssid, DeviceID().c_str(), sizeof(ap_ssid));
    strlcpy(ap_password, Contra.c_str(), sizeof(ap_password));
    ap_channel = 9;        // 1-13
    ap_visibility = false; // para que se vea
    ap_connect = 3;        // cantidad de conexiones en modo AP 0-8
    // MQTT
    mqtt_enabled = MqttAcceso;
    strlcpy(mqtt_server, MqttServer.c_str(), sizeof(mqtt_server));
    mqtt_port = MqttPort;
    mqtt_retain = false;
    mqtt_qos = 0;
    strlcpy(mqtt_id, DeviceID().c_str(), sizeof(mqtt_id));
    strlcpy(mqtt_user, MqttUser.c_str(), sizeof(mqtt_user));
    strlcpy(mqtt_password, MqttPassword.c_str(), sizeof(mqtt_password));
    mqtt_clean_session = true;
    strlcpy(mqtt_commandTopic, PathMqttTopic("command").c_str(), sizeof(mqtt_commandTopic));
    strlcpy(mqtt_sendTopic, PathMqttTopic("device").c_str(), sizeof(mqtt_sendTopic));
    strlcpy(mqtt_willTopic, PathMqttTopic("status").c_str(), sizeof(mqtt_willTopic));
    strlcpy(mqtt_willMessage, "{\"connected\":false}", sizeof(mqtt_willMessage));
    mqtt_willQos = 0;
    mqtt_willRetain = false;
    mqtt_time_send = true;
    mqtt_time_interval = 6000; // 60 es el standard
    mqtt_status_send = true;
    RELAY1_STATUS = false;
    RELAY2_STATUS = false;
    // DIMER
    dim = 0;
    // ---------------------------------------------------------
    //  ZONA DE ALARMAS
    // ---------------------------------------------------------
    ALARM_LOGICA1 = false;
    ALARM_NAME1 = "ALARMA IO35";
    ALARM_LOGICA2 = false;
    ALARM_NAME2 = "ALARMA IO36";
    ALARM_LOGICA3 = false;
    ALARM_NAME3 = "ALARMA IO37";
    ALARM_LOGICA4 = false;
    ALARM_NAME4 = "ALARMA IO38";
    ALARM_LOGICA5 = false;
    ALARM_NAME5 = "ALARMA IO39";
    ALARM_LOGICA6 = false;
    ALARM_NAME6 = "ALARMA IO40";
    ALARM_LOGICA7 = false;
    ALARM_NAME7 = "ALARMA IO41";
    ALARM_LOGICA8 = false;
    ALARM_NAME8 = "ALARMA IO42";

    // log
    myLog("INFO", "settings.hpp", "settingsReset()", "Se reiniciaron todos los valores por defecto de fabrica");
}
// hasta el momento todo esto solo pone en la memoria la información pero aun no se salva y toda la configuración se pierde al reiniciar el dispositivo
// Guardar configuraciones en el json
boolean settingsSave()
{
    // definicion del json
    JsonDocument jsonSettings; // se crea una variable tipo JSON
    // asignando en el JSON las variables que estan en memoria
    // generales
    jsonSettings["device_id"] = device_id;
    jsonSettings["device_name"] = device_name;
    jsonSettings["device_user"] = device_user;
    jsonSettings["device_password"] = device_password;
    // wifi
    JsonObject wifiObj = jsonSettings["wifi"].to<JsonObject>(); // se le indica que es un objeto de JSON
    wifiObj["wifi_mode"] = wifi_mode;
    wifiObj["wifi_ssid"] = wifi_ssid;
    wifiObj["wifi_password"] = wifi_password;
    wifiObj["wifi_dhcp"] = wifi_dhcp;
    wifiObj["wifi_ipv4"] = wifi_ipv4;
    wifiObj["wifi_subnet"] = wifi_subnet;
    wifiObj["wifi_gateway"] = wifi_gateway;
    wifiObj["wifi_dns_primary"] = wifi_dns_primary;
    wifiObj["wifi_dns_secondary"] = wifi_dns_secondary;
    wifiObj["ap_ssid"] = ap_ssid;
    wifiObj["ap_password"] = ap_password;
    wifiObj["ap_channel"] = ap_channel;
    wifiObj["ap_visibility"] = ap_visibility;
    wifiObj["ap_connect"] = ap_connect;

    // MQTT
    JsonObject mqttObj = jsonSettings["mqtt"].to<JsonObject>(); // se le indica que es un objeto de JSON
    mqttObj["mqtt_enabled"] = mqtt_enabled;
    mqttObj["mqtt_server"] = mqtt_server;
    mqttObj["mqtt_port"] = mqtt_port;
    mqttObj["mqtt_retain"] = mqtt_retain;
    mqttObj["mqtt_qos"] = mqtt_qos;
    mqttObj["mqtt_id"] = mqtt_id;
    mqttObj["mqtt_user"] = mqtt_user;
    mqttObj["mqtt_password"] = mqtt_password;
    mqttObj["mqtt_clean_session"] = mqtt_clean_session; // verificar si no es mqtt_clean_sessions
    mqttObj["mqtt_commandTopic"] = mqtt_commandTopic;
    mqttObj["mqtt_sendTopic"] = mqtt_sendTopic;
    mqttObj["mqtt_willTopic"] = mqtt_willTopic;
    mqttObj["mqtt_willMessage"] = mqtt_willMessage;
    mqttObj["mqtt_willQos"] = mqtt_willQos; // verificar si es mqtt_willQoS
    mqttObj["mqtt_willRetain"] = mqtt_willRetain;
    mqttObj["mqtt_time_send"] = mqtt_time_send;
    mqttObj["mqtt_time_interval"] = mqtt_time_interval;
    mqttObj["mqtt_status_send"] = mqtt_status_send;
    // relays
    JsonObject relayObj = jsonSettings["relay"].to<JsonObject>();
    relayObj["RELAY1_STATUS"] = RELAY1_STATUS;
    relayObj["RELAY2_STATUS"] = RELAY2_STATUS;
    // DIMER
    JsonObject dimmerObj = jsonSettings["dimmer"].to<JsonObject>();
    dimmerObj["dim_value"] = dim;
    // ---------------------------------------------------------
    //  ZONA DE ALARMAS
    // ---------------------------------------------------------
    JsonObject alarmasObj = jsonSettings["alarmas"].to<JsonObject>();
    alarmasObj["ALARM_LOGICA1"] = ALARM_LOGICA1;
    alarmasObj["ALARM_NAME1"] = ALARM_NAME1;
    alarmasObj["ALARM_LOGICA2"] = ALARM_LOGICA2;
    alarmasObj["ALARM_NAME2"] = ALARM_NAME2;
    alarmasObj["ALARM_LOGICA3"] = ALARM_LOGICA3;
    alarmasObj["ALARM_NAME3"] = ALARM_NAME3;
    alarmasObj["ALARM_LOGICA4"] = ALARM_LOGICA4;
    alarmasObj["ALARM_NAME4"] = ALARM_NAME4;
    alarmasObj["ALARM_LOGICA5"] = ALARM_LOGICA5;
    alarmasObj["ALARM_NAME5"] = ALARM_NAME5;
    alarmasObj["ALARM_LOGICA6"] = ALARM_LOGICA6;
    alarmasObj["ALARM_NAME6"] = ALARM_NAME6;
    alarmasObj["ALARM_LOGICA7"] = ALARM_LOGICA7;
    alarmasObj["ALARM_NAME7"] = ALARM_NAME7;
    alarmasObj["ALARM_LOGICA8"] = ALARM_LOGICA8;
    alarmasObj["ALARM_NAME8"] = ALARM_NAME8;
    // guardar el json en spiffs
    File file = SPIFFS.open("/settings.json", "w"); // modo escritura
    if (!file)
    { // verificamos que el archivo se pueda abrir
        myLog("ERROR", "settings.hpp", "settingsSave()", "Error en abrir el archivo de configuraciones settings.json al guardar la información");
        return false;
    }
    // guardando y buscando que no se presenten errores
    if (serializeJson(jsonSettings, file) == 0)
    { // manda un numero en caso de no poder realizar la función
        myLog("ERROR", "settings.hpp", "serializeJson(jsonSettings,file)", "Error al serializar el archivo settings.json");
        file.close();
        return false;
    }
    file.close();
    myLog("INFO", "settings.hpp", "settingsSave()", "Se guardaron las configuraciones en el archivo settings.json");
    // mostrar el settings.json en el monitor
    serializeJsonPretty(jsonSettings, Serial);
    return true;
}