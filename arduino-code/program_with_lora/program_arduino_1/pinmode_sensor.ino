// membuat fungsi pinMode komponen
void pinmode_setup() {
  // Set pin relay menjadi OUTPU
  pinMode(pinRelay_1, OUTPUT);
  pinMode(pinRelay_2, OUTPUT);
  pinMode(pinEcho, INPUT); // set pin echo menjadi INPUT
  pinMode(pinTrig, OUTPUT); // set pin trig menjadi OUTPUT
}

unsigned long waktuSebelum_2 = 0; // buat variable millis waktu sebelum diproses program
int jedaWaktu_2 = 1000; // 1000 ms = 1 detik

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

    // Mengirimkan data ke serial komunikasi
    data.printTo(pinNodemcu);
    // data.printTo(Serial);
    jsonBuffer.clear();
  }
}