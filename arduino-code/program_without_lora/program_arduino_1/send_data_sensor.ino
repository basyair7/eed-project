// buat variable millis waktu sebelum diproses program
unsigned long waktuSebelum_2 = 0; 
int jedaWaktu_2 = 1000; // 1000 ms = 1 detik

// membuat fungsi pinMode komponen
void pinmode_setup() {
  // Set pin relay menjadi OUTPU
  pinMode(pinRelay_1, OUTPUT);
  pinMode(pinRelay_2, OUTPUT);
  pinMode(pinEcho, INPUT); // set pin echo menjadi INPUT
  pinMode(pinTrig, OUTPUT); // set pin trig menjadi OUTPUT
}

// buat fungsi mengambil data sensor dan kirim ke nodemcu
void pinmode_data() {
  unsigned long waktuSekarang_2 = millis(); // buat variable millis waktu sedang diproses program
  if ((unsigned long) (waktuSekarang_2 - waktuSebelum_2) >= jedaWaktu_2)
  {
    // Buat object jsonBuffer
    waktuSebelum_2 = waktuSekarang_2;
    DynamicJsonBuffer jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
    data["sensor_1"] = map(analogRead(pinSensor_1), 0, 1023, 100, 0);
    data["sensor_2"] = map(analogRead(pinSensor_2), 0, 1023, 100, 0);
    data["sensor_tampungan"] = map(analogRead(pinSensorTampungan), 0, 1023, 100, 0);

    // Mengirimkan data ke serial komunikasi
    data.printTo(pinNodemcu);
    jsonBuffer.clear();
  }
}

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