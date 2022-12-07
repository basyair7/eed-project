#include <SPI.h>
#include <LoRa.h>

// buat variabel sensor tandon
#define pinEcho 5
#define pinTrig 6

// buat variabel durasi dan jarak untuk sensor 
long durasi, jarak;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(pinEcho, INPUT); // set pin echo menjadi INPUT
  pinMode(pinTrig, OUTPUT); // set pin trig menjadi OUTPUT

  /* konfigurasi lora (frekuensi transmisi & receiver) 
  * 443E6 = 433 MHz
  * 868E6 = 868 MHz 
  * 915E6 = 915 MHz
  */
  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(443E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  // jalankan program main_transmisi()
  main_transmisi();

}
