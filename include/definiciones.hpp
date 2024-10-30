// PINOUT
/*
No usar los gpio 26,27,28,29,30,31,32 pines conectados a la memoria flash spi
usaremos los GPIO 08(SDA) y 09(SCL) para el display OLED
*/
#define DHTPIN 12    // GPIO 12 entrada sensor dht22 (temperatura y humedad)
#define POZO 13      // GPIO 13 sensor de pozo (temperatura)
#define NUM_RELAYS 2 // numero de relays
#define RELAY1 17    // GPIO 41 Relevador1
#define RELAY2 18    // GPIO 42 Relevador2
#define DIMMER 19    // led DIMMER
// el WIFI led es el 48 VERDE
// el MQTT led es el 48 AZUL
// el DIMER led es el 48 ROJO
#define NUM_ALARMS 8 // numero de alarmas
#define ALARMPIN1 35 // Entrada de la alarma1
#define ALARMPIN2 36 // Entrada de la alarma2
#define ALARMPIN3 37 // Entrada de la alarma3
#define ALARMPIN4 38 // Entrada de la alarma4
#define ALARMPIN5 39 // Entrada de la alarma5
#define ALARMPIN6 40 // Entrada de la alarma6
#define ALARMPIN7 41 // Entrada de la alarma7
#define ALARMPIN8 42 // Entrada de la alarma8
//-----------------------------------------------------------------------------------------------
// VERSION DE FIRMWARE (Por documentación) se toman de las variables de entorno de platformio.ini
//-----------------------------------------------------------------------------------------------
#define TEXTTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTTIFY(A)
String device_fw_version = ESCAPEQUOTE(BUILD_TAG);

//----------------------------------------------------
// Zons firmware
//------------------------------------------------------
size_t content_len;
#define U_PART U_SPIFFS // para actualizacion del firmare via remota

//-----------------------------------------------------------------------
// HARDWARE AND MANUFACTURE Y FABRICANTE
//-----------------------------------------------------------------------
#define device_hw_version "ADMINESP32 v1 0000" // version del Hardware
#define device_manufacture "IOTMX"             // Fabricante

//-----------------------------------------------------------------------------
// ZONA DE CONFIGURACION DEL DISPOSITIVO (variables globales)
//-----------------------------------------------------------------------------
char device_id[30];       // número identificador
char device_name[30];     // nombre del dispositivo ejemplo: es el lugar HGO3PISO
char device_user[16];     // usuario web
char device_password[16]; // para logearse en el servidor web
u_int16_t device_restart; // numero entero positivo que va hasta 65535

//-------------------------------------------------------------------
// Zona configuración WIFI en modo Cliente (Variables)
//-------------------------------------------------------------------
int wifi_app = WIFI_AP;
boolean wifi_mode;      // true = cliente de un modem, false = ap(accespoint)
char wifi_ssid[63];     // nombre de modem
char wifi_password[63]; // su password
boolean wifi_dhcp;      // ip fijo si es false o es asignada una ip automaticamente si es true
char wifi_ipv4[16];
char wifi_gateway[16];
char wifi_subnet[16];
char wifi_dns_primary[16];
char wifi_dns_secondary[16];

//------------------------------------------------------------
// Zona configuración wifi AP(AccesPOINT)
//-----------------------------------------------------------
char ap_ssid[63];     // Nombre del SSID modo AP máximo 63
char ap_password[63]; // Contraseña del modo AP mínimo 8 NULL red abierta
int ap_channel;       // 1-13 el canal de la red wifi
int ap_visibility;    // 0 visible y 1 oculto por documentación
int ap_connect;       // 0 - 8 numero de clientes

//---------------------------------------------------------------
// Zona configuración MQTT
//---------------------------------------------------------------
boolean mqtt_enabled;
char mqtt_server[39];
int mqtt_port;
boolean mqtt_retain;
int mqtt_qos;
char mqtt_id[63];
char mqtt_user[63];
char mqtt_password[63];
boolean mqtt_clean_session;
char mqtt_commandTopic[150];
char mqtt_sendTopic[150];
char mqtt_willTopic[150];
char mqtt_willMessage[150];
int mqtt_willQos;
boolean mqtt_willRetain;
boolean mqtt_time_send;
int mqtt_time_interval;
boolean mqtt_status_send;

//---------------------------------------------------
// Zona EEPROM para contador de reinicios por documentación
//----------------------------------------------------
#define Start_Address 0
#define Restart_Address Start_Address + sizeof(int)

//----------------------------------------------------
// otras variables globales a utilizar
//----------------------------------------------------
float tempPozoC, tempPozof; // centigrados y fahrenheit

//---------------------------------------------------
// Zona Relay
//-------------------------------------------------
bool RELAY1_STATUS; // estado del relay1
bool RELAY2_STATUS; // estado del relay2

//-------------------------------------------------
// zona PWM
//---------------------------------------------------
const int freq = 1000;    // frecuencia de trabajo de 1khz
const int ledChannel = 0; // Definicion del Canal
const int resolution = 8; // 8 bits lo cual corresponde a 255 bit de resolución
int dim;                  // un valor que va de 0 a 255 a enviar

// ---------------------------------------------------
// Zona de alarmas
// ---------------------------------------------------
bool ALARM_STATUS1, ALARM_STATUS2, ALARM_STATUS3, ALARM_STATUS4;
bool ALARM_STATUS5, ALARM_STATUS6, ALARM_STATUS7, ALARM_STATUS8;
// guardar la logica, el pin y el nombre en el settings
bool ALARM_LOGICA1, ALARM_LOGICA2, ALARM_LOGICA3, ALARM_LOGICA4;
bool ALARM_LOGICA5, ALARM_LOGICA6, ALARM_LOGICA7, ALARM_LOGICA8;
String ALARM_NAME1, ALARM_NAME2, ALARM_NAME3, ALARM_NAME4;
String ALARM_NAME5, ALARM_NAME6, ALARM_NAME7, ALARM_NAME8;
String ALARM_TIMEON1, ALARM_TIMEON2, ALARM_TIMEON3, ALARM_TIMEON4;
String ALARM_TIMEON5, ALARM_TIMEON6, ALARM_TIMEON7, ALARM_TIMEON8;
String ALARM_TIMEOFF1, ALARM_TIMEOFF2, ALARM_TIMEOFF3, ALARM_TIMEOFF4;
String ALARM_TIMEOFF5, ALARM_TIMEOFF6, ALARM_TIMEOFF7, ALARM_TIMEOFF8;
int ALARM_CONT1, ALARM_CONT2, ALARM_CONT3, ALARM_CONT4; // registra el valor del contador de alarmas
int ALARM_CONT5, ALARM_CONT6, ALARM_CONT7, ALARM_CONT8;
// contador de alarmas indica cuantas veces se a producido esa alarma
int cont[8] = {ALARM_CONT1, ALARM_CONT2, ALARM_CONT3, ALARM_CONT4, ALARM_CONT5, ALARM_CONT6, ALARM_CONT7, ALARM_CONT8}; // lleva la contavilizacion en un for
bool prueba = false;                                                                                                    // en caso de requerir hacer una prueba remota                                                                                                // por si necesito mandar una prueba de todas las alarmas y se vean en el gestor (Huawei)                                                                                                   // envia por mqtt que se hace una prueba de alarmas
bool cambiar[8] = {false, false, false, false, false, false, false, false};