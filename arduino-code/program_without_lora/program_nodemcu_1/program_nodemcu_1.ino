#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// konfigurasi komunikasi arduino
SoftwareSerial pinAtmega(D1, D2); // RX = D1, TX = D2;

// Setting find WiFi Hotspot
#ifndef STASSID
// #define STASSID "awp_wifi"
// #define STAPSK "ppkormawa2022"
#define STASSID "server_api 24/7"
#define STAPSK "Server_ahul07"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Setting Firebase Database
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

// root json firebase data
const String path_sensor_1 = "message-database/3-kelembapan-1/a";
const String path_sensor_2 = "message-database/4-kelembapan-2/a";
const String path_relay_1 = "switcher/switch-1";
const String path_relay_2 = "switcher/switch-2";
const String path_auto_relay = "switcher/auto";
const String path_hum_limit = "data-sensor-pompa-air/hum-limit";
const String path_limit_tampungan = "data-sensor-pompa-air/limit-tampungan";
const String path_tampungan = "data-sensor-pompa-air/sensor-tampungan";

FirebaseData firebaseData; // buat object firebaseData

// reconnect wifi if hotspot disconnect
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

// void ICACHE_RAM_ATTR loop(); // jika nodemcu intrrupt

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
  pinAtmega.begin(9600);
  // Register Event Handler
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  initWiFi();
  Serial.print(F("RSSI : "));
  Serial.println(WiFi.RSSI());

  // Setup firebase auth & host link
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);

  while(!Serial) continue;

  set_data_sensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  // buat object jsonBuffer;
  DynamicJsonBuffer jsonBuffer;
  // JsonObject& data = jsonBuffer.parseObject(Serial);
  JsonObject& data = jsonBuffer.parseObject(pinAtmega);

  if (data == JsonObject::invalid()) {
    return jsonBuffer.clear();
  }

  // ambil nilai sensor dari arduino
  int get_data_sensor_1 = data["sensor_1"];
  int get_data_sensor_2 = data["sensor_2"];
  int get_data_tampungan = data["sensor_tampungan"];

  // kirim data ke firebase
  push_data(get_data_sensor_1, get_data_sensor_2, get_data_tampungan);

  // kirim perintah relay ke arduino
  program_relay();

  delay(15); // jeda program 0.015 detik

}
