// Definiciones necesarias
#include <Arduino.h>           // para que entienda codigo
#include <Adafruit_NeoPixel.h> // utilizar el NEOPIXEL
#include <EEPROM.h>            // para manejar la memoria EEPROM del esp32 (no volatil)
#include <SPIFFS.h>            // para manejos de archivos que se almacenas en la memoria no volatil
#include <ESPmDNS.h>           // para direcciones ip con nombre
#include <ArduinoJson.h>       // manejo de archivos JSON para las variables
#include <TimeLib.h>           // para las fechas
#include <PubSubClient.h>      // para el MQTT
#include <ESPAsyncWebServer.h> // para el servidor dentro del esp32

/*Librerias agregadas para nuevas funcionalidades y obligatorias (LALO)*/
#include <DHT.h>                // para la temperatura y humedad by Adafruit
#include <Adafruit_I2CDevice.h> //Para la comunicaciones serial by Adafruit
#include <Adafruit_GFX.h>       // para la pantalla de lcd de gráficos (cuadrados circulos toda una especializacion)
#include <Adafruit_SSD1306.h>   // para la pantalla de lcd by Adafruit

// Archivos *.hpp Fragmentación del codigo
#include "definiciones.hpp"
#include "var_entorno.hpp"
#include "functions.hpp"
#include "settings.hpp"

// Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(# de NEOPIXEL, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(1, 48, NEO_GRB + NEO_KHZ800);
// put function declarations here:

void setup()
{
  // put your setup code here, to run once:
  NeoPixel.begin(); // inicializacion del neopixel
  NeoPixel.show();  // apagar el NeoPixel ya que no hay valores asignados para mostrar
  Serial.begin(115200);
  myLog("INFO", "main.cpp", "setup()", "Iniciando..."); // para que el programa no avance hasta que termine de transmitir los datos que se encuentran en el buffer
  Serial.flush();
  if (!SPIFFS.begin(true))
  {
    // esto indica que si no logra inicializar el SPIFFS continuara este buclu hasta que el resultado sea un true
    myLog("ERROR", "main.cpp", "SPIFFS.begin(true)", "Falla al inicializar SPIFSS"); // para que el programa no avance hasta que termine de transmitir los datos que se encuentran en el buffer
    while (true);
  }
  // contador de reinicios
  EEPROM.begin(256); // bytes
  EEPROM.get(Restart_Address, device_restart);
  device_restart++;
  // verificar que no exeda de 65535 en ese caso se iguala a 0
  if (device_restart > 65535)
  {
    device_restart = 0;
    EEPROM.put(Restart_Address, device_restart);
  }
  EEPROM.put(Restart_Address, device_restart);
  EEPROM.commit(); // guardamos la información
  EEPROM.end();
  String message = "Cantidad de reinicios: " + String(device_restart);
  myLog("INFO", "main.cpp", "EEPROM", message.c_str());
  // leer las configuraciones del settings.json
  if (!settingsRead())
  { // al negarlo se vuelve un verdadero
    // TODO: mandar a llamar a la funcion de guardar
    settingsSave();
  }
  // definir los pines de entrada y salida
  gpioDefineIn();
  gpioDefineOut();
  // despues de definir los pines ya podemor configurar las salidas segun lo guardado en settings.json
  setOnOffSingle(RELAY1, RELAY1_STATUS);
  setOnOffSingle(RELAY2, RELAY1_STATUS);
  // PWM
  ledcWrite(ledChannel, dim * 2.55); // 8 bits 255 dim es = 0-100
}

void loop()
{
}
