// buat variable millis waktu sebelum diproses program
unsigned long waktuSebelum_1 = 0;
unsigned long waktuSebelum_2 = 0;

int jedaWaktu_1 = 1000;  // 1000 ms = 1 detik
int jedaWaktu_2 = 100;    // 100 ms = 0.1 detik

// buat fungsi kirim data ke firebase
void push_data(int data_1) {
  // buat variabel millis waktu sedang diproses program
  unsigned long waktuSekarang_1 = millis();

  if ((unsigned long)(waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1)
  {
    waktuSebelum_1 = waktuSekarang_1;
    // push data in database
    Firebase.setInt(firebaseData, path_mata_air, data_1);
    delay(10);
  }
}

// buat fungsi program relay
void program_relay() {
  unsigned long waktuSekarang_2 = millis();  // buat variabel millis waktu sedang diproses program relay

  if ((unsigned long)(waktuSekarang_2 - waktuSebelum_2) >= jedaWaktu_2)
  {
    waktuSekarang_2 = waktuSebelum_2;
    // buat object jsonBuffer_relay;
    DynamicJsonBuffer jsonBuffer_relay;
    JsonObject& data_sensor = jsonBuffer_relay.createObject();
    // ambil data tampungan air untuk relay arduino
    int data_tampungan;
    Firebase.getInt(firebaseData, path_tampungan, &data_tampungan);
    data_sensor["sensor_tampungan"] = data_tampungan;
    
    // kirim perintah boolean ke arduino
    data_sensor.printTo(Serial);
    
  }
}

// buat fungsi set_data_sensor program
void set_data_sensor() {
  Firebase.setInt(firebaseData, path_mata_air, 0);
  Firebase.setInt(firebaseData, path_tampungan, 0);
  delay(10);
}