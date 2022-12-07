#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>

// Konfigurasi pin serial komunikasi arduino
SoftwareSerial arduino2(4, 5); // RX = 4, TX = 5;

// buat variabel pin sensor
#define pinSensorAir A0

// buat variabel untuk data lora
#define batasMaksimumTandon 80 // cm
#define batasMinimumTandon  65 // %

// buat variable untuk sensor air
#define batasMaksMataAir 80 // %
#define batasMinMataAir  65 // %
int data_sensor;

int packetSize;
String baca, sinyal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
  arduino2.begin(9600);
  while (!Serial) return;

  /* konfigurasi lora (frekuensi transmisi & receiver) 
  * 443E6 = 433 MHz
  * 868E6 = 868 MHz 
  * 915E6 = 915 MHz
  */

  Serial.println("LoRa Receiver");
  if (!LoRa.begin(512E6)) {
    Serial.println("Starting LoRa Failed!");
    while (1);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  receiver_main(); // jalankan program receiver_main()
  relay_main(); // jalankan program relay_main()

  // jika data rusak (NaN) maka kembalikan nilai packetSize ke 0
  if (packetSize == 0) { 
    packetSize = 0;
    baca = "";
    sinyal = "";
    return;
  }
  
  // tampilkan data LoRa di serial monitor Arduino IDE
  Serial.println(F("**********DATA SENSOR**********"));
  Serial.print(F("Data Kapasitas Air Tandon : "));
  Serial.println(baca.toInt());
  Serial.print(F("Data Sensor Mata Air : "));
  Serial.println(data_sensor);
  Serial.print(F("Sinyal LoRa : "));
  Serial.println(sinyal);
  Serial.println(F("******************************"));

  // kosongkan nilai String baca dan sinyal, agar dapat terisi kembali data sensor yang diterima
  baca = ""; sinyal = "";
}


