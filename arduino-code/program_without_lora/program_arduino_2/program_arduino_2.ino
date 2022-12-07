#include <ArduinoJson.h>
#include <MemoryFree.h>

// buat variabel pin sensor & relay
#define pinRelay 4
#define pinSensorAir A0

// buat variable untuk tampingan
#define batasMaksTandon 60 // %
#define batasMinTandon 55 // %

// buat variable untuk sensor air
#define batasMinMataAir  10 // %

int data_sensor_tampungan, data_sensor_mata_air;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
  Serial3.begin(9600);
  while (!Serial) return;

  pinMode(pinRelay, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  relay_main(); // jalankan program relay_main()
}


