#include <SoftwareSerial.h>

// Konfigurasi pin serial komunikasi arduino
SoftwareSerial arduino2(5, 4); // RX = 5, TX = 4;

// buat variabel pin relay
#define pinRelay 2

// buat variabel hidup atau mati untuk relay
#define HIDUP HIGH
#define MATI LOW

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Untuk kecepatan kirim dan terima serial data dalam 9600 bit per detik
  arduino2.begin(9600);
  while (!Serial) return;
  
  pinMode(pinRelay, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:

  if (arduino2.available()) {
    int perintah_arduino = arduino2.read();

    if (perintah_arduino == 1) {
      digitalWrite(pinRelay, HIDUP);
      Serial.println(F("POMPA AIR INDUK HIDUP"));
    } 
    else if (perintah_arduino == 0) {
      digitalWrite(pinRelay, MATI);
      Serial.println(F("POMPA AIR INDUK MATI"));
    }
  }

}
