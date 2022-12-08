// buat variabel hidup atau mati
#define HIDUP LOW
#define MATI HIGH

// buat variable millis waktu sebelum diproses program
unsigned long waktuSebelum_1 = 0;

int jedaWaktu_1 = 100; // 500 ms = 0.05 detik

// buat fungsi terima data dari LoRa
void receiver_main() {
  // mengambil data LoRa transmisi
  packetSize = LoRa.parsePacket();
  // buat 
  // jika data rusak (NaN) maka kembalikan nilai packetSize ke 0
  if (packetSize == 0) { 
    packetSize = 0;
    return;
  }

  // enkripsikan dan membaca data LoRa transmisi 
  while(LoRa.available()) {
    baca += (char)LoRa.read();
  }

  // enkripsikan dan membaca kekuatan sinyal LoRa transmisi
  sinyal = LoRa.packetRssi();
}

void relay_main() {
  // buat variabel millis waktu sedang diproses program
  unsigned long waktuSekarang_1 = millis();

  // program relay dari LoRa
  if ((unsigned long)(waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1) {
    // jalankan logika untuk relay pompa air
    waktuSebelum_1 = waktuSekarang_1;
    // ubah sinyal analog arduino (0-1023) ke range 0 - 100
    data_sensor = map(analogRead(pinSensorAir), 0, 1023, 100, 0);

    // jika data rusak (NaN) maka kembalikan nilai packetSize ke 0
    if (packetSize == 0) { 
      packetSize = 0;
      baca = "";
      sinyal = "";
      return;
    }

    if (baca.toInt() < batasMinimumTandon && data_sensor > batasMinMataAir) {
      digitalWrite(pinRelay, HIDUP);
      Serial.println(F("POMPA AIR INDUK HIDUP"));
    }
    else if (baca.toInt() >= batasMaksimumTandon || data_sensor <= batasMinMataAir) {
      digitalWrite(pinRelay, MATI);
      Serial.println(F("POMPA AIR INDUK MATI"));
    }
  }


}