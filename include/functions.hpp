
// realizar un log en el puerto serial
void myLog(const char *type, const char *arch, const char *func, const char *msg)
{
    // type: [DEBUG, INFO, WARN, ERROR]
    Serial.printf("[%s] [%s] [%s] %s\n", type, arch, func, msg);
}

// platform
const char *platform()
{
#if defined(ARDUINO_ESP32_DEV)
    return "ESP32";
#else
    return "ESP32-S3";
#endif
}

String hexStr(const unsigned long &h, const byte &l = 8)
{
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}

String UniqueID()
{
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);
    String id = String(chip, HEX);
    id.toUpperCase();
    while (id.length() < 4)
    {
        id = "0" + id;
    }
    return id;
}

// Device ID unico
String DeviceID()
{
    return platform() + hexStr(ESP.getEfuseMac(), 8) + UniqueID();
}

// Crear topico para MQTT
//  //usuario/+/id/# => /emqx/vue32/ESP32299b1c52100C3D/status = true/false
String PathMqttTopic(const String &topic)
{
    return String("/") + mqtt_user + "/vue32/" + mqtt_id + "/" + topic;
}

// se definen los dos pines de salida de los relays
const int outputsPins[NUM_RELAYS] = {RELAY1, RELAY2};
// se define las ocho pines de alarmas
const int inputsPins[NUM_ALARMS] = {ALARMPIN1, ALARMPIN2, ALARMPIN3, ALARMPIN4, ALARMPIN5, ALARMPIN6, ALARMPIN7, ALARMPIN8};
// apagar todas las salidas
void turnOffOutputs()
{
    for (int i = 0; i < NUM_RELAYS; i++)
    {
        digitalWrite(outputsPins[i], LOW);
    }
}
// definir pines
void gpioDefineOut() // pines de salida
{
    for (int i = 0; i < NUM_RELAYS; i++)
    {
        pinMode(outputsPins[i], OUTPUT);
    }
    // PWM
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(DIMMER, ledChannel);
    // setear todo a 0 o apagado
    turnOffOutputs();
    ledcWrite(ledChannel, 0);
}
void gpioDefineIn() // pines de entrada
{
    for (int i = 0; i < NUM_ALARMS; i++)
    {
        pinMode(inputsPins[i], INPUT_PULLUP);
    }
}
// APAGAR o ENCENDER UNA SALIDA
void setOnOffSingle(int _pin, bool status)
{
    digitalWrite(_pin, status);
}