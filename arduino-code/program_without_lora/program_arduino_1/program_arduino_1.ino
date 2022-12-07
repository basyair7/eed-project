#include <ArduinoJson.h>
#include <MemoryFree.h>
#include <SoftwareSerial.h>

// Konfigurasi pin serial komunikasi nodemcu
SoftwareSerial pinNodemcu(8, 7); // RX = 8, TX = 7;

// Buat variabel sensor tanah
#define pinSensor_1 A0
#define pinSensor_2 A1

// Buat variabel sensor tandon
#define pinEcho 5
#define pinTrig 6
#define pinSensorTampungan A2 // Jika sensor tandon menggunakan pin analog

// Buat variabel relay pompa
#define pinRelay_1 3
#define pinRelay_2 4

bool boolean_relay_1, boolean_relay_2, boolean_relay_auto;
int hum_limit, limit_tampungan;

void setup() {
  // put your setup code here, to run once:
  // untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
  Serial.begin(9600);
  pinNodemcu.begin(9600);
  while (!Serial);
  
  pinmode_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  pinmode_data();
  relay_main();
}
