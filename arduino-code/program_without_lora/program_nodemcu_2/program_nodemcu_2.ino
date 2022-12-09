#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>

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
const String path_mata_air = "data-sensor-pompa-air/sensor-mata-air";
const String path_tampungan = "data-sensor-pompa-air/sensor-tampungan";

FirebaseData firebaseData; // buat object firebaseData

// reconnect wifi if hotspot disconnect
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

// void ICACHE_RAM_ATTR loop(); // jika nodemcu intrrupt

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
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

  program_relay(); // jalankan program_relay()

  delay(15); // jeda program 0.015 detik

}
