// buat variabel millis sebelum diproses program
unsigned long waktuSebelum_3 = 0;
int jedaWaktu_3 = 900; // 900 ms = 0.9 detik

// buat fungsi program untuk sensor ultrasonic
long sensorUltrasonic() {
  // proses pemancaran suara ultrasonic
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(80);
  digitalWrite(pinTrig, LOW);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(80);
  delayMicroseconds(80);

  // proses penerimaan suara ultrasonic
  long durasi = pulseIn(pinEcho, HIGH);
  long jarak = (durasi / 2) / 2.91; // mengubah durasi menjadi panjang jarak (cm)

  return jarak;
}

void main_transmisi() {
  // Buat variable millis waktu sedang diproses program
  unsigned long waktuSekarang_3 = millis();

  if ((unsigned long)(waktuSekarang_3 - waktuSebelum_3) >= jedaWaktu_3) {
    // kirim data sensor ke LoRa receiver
    LoRa.beginPacket();
    // LoRa.print(String(sensorUltrasonic()));
    // Serial.println(String(sensorUltrasonic()));
    LoRa.print(String(map(analogRead(pinSensorTampungan), 0, 1023, 100, 0)));
    Serial.println(String(map(analogRead(pinSensorTampungan), 0, 1023, 100, 0)));
    LoRa.endPacket();
  }
}
