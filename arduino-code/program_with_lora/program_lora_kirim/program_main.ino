// buat variable millis sebelum diproses program
unsigned long waktuSebelum_1 = 0;
int jedaWaktu_1 = 900; // 900 ms = 0.9 detik

// buat fungsi program untuk sensor ultrasonic
long sensor() {
  // proses pemancaran suara ultrasonic
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(80);
  digitalWrite(pinTrig, LOW);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(80);
  delayMicroseconds(80);
  
  // proses penerimaan suara ultrasonic
  durasi = pulseIn(pinEcho, HIGH);
  jarak = (durasi / 2) / 29.1; // mengubah durasi menjadi panjang jarak (cm)

  return jarak;
}

void main_transmisi() {
  // buat variable millis waktu sedang diproses program
  unsigned long waktuSekarang_1 = millis();

  if ((unsigned long)(waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1) {
    waktuSebelum_1 = waktuSekarang_1;
    // kirim data sensor ke LoRa receiver
    Serial.println(String(sensor()));
    LoRa.beginPacket();
    // LoRa.print(String(sensor()));
    LoRa.print(30);
    LoRa.endPacket();
  }
}