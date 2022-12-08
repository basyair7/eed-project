// buat variable millis waktu sebelum diproses program
unsigned long waktuSebelum_1 = 0;
unsigned long waktuSebelum_2 = 0;

int jedaWaktu_1 = 1000;  // 1000 ms = 1 detik
int jedaWaktu_2 = 100;    // 100 ms = 0.1 detik

// buat fungsi kirim data ke firebase
void push_data(int data_1, int data_2, int data_3) {
  // buat variabel millis waktu sedang diproses program
  unsigned long waktuSekarang_1 = millis();

  if ((unsigned long)(waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1)
  {
    waktuSebelum_1 = waktuSekarang_1;
    // push data in database
    Firebase.setInt(firebaseData, path_sensor_1, data_1);
    delay(5);
    Firebase.setInt(firebaseData, path_sensor_2, data_2);
    delay(5);
    Firebase.setInt(firebaseData, path_tampungan, data_3);
    delay(10);
  }
}

// buat fungsi program relay
void program_relay() {
  // buat object jsonBuffer_relay;
  DynamicJsonBuffer jsonBuffer_relay;
  JsonObject& boolean_relay = jsonBuffer_relay.createObject();
  unsigned long waktuSekarang_2 = millis();  // buat variabel millis waktu sedang diproses program relay

  if ((unsigned long)(waktuSekarang_2 - waktuSebelum_2) >= jedaWaktu_2)
  {
    waktuSebelum_2 = waktuSekarang_2;
    // ambil data limit kelembapan untuk relay arduino
    int hum_limit, limit_tampungan, data_mata_air;
    Firebase.getInt(firebaseData, path_limit_tampungan, &limit_tampungan);
    Firebase.getInt(firebaseData, path_hum_limit, &hum_limit);
    boolean_relay["hum_limit"] = hum_limit;
    boolean_relay["limit_tampungan"] = limit_tampungan;
    
    // ambil data boolean di database
    bool boolean_relay_1, boolean_relay_2, boolean_relay_auto;
    Firebase.getBool(firebaseData, path_relay_1, &boolean_relay_1);
    Firebase.getBool(firebaseData, path_relay_2, &boolean_relay_2);
    Firebase.getBool(firebaseData, path_auto_relay, &boolean_relay_auto);

    if (boolean_relay_1 == true) {
      boolean_relay["relay_1"] = true;
    } else {
      boolean_relay["relay_1"] = false;
    }

    if (boolean_relay_2 == true) {
      boolean_relay["relay_2"] = true;
    } else {
      boolean_relay["relay_2"] = false;
    }

    if (boolean_relay_auto == true) {
      boolean_relay["auto_relay"] = true;
    } else {
      boolean_relay["auto_relay"] = false;
    }

    // kirim perintah boolean ke arduino
    // bool_relay.printTo(Serial);
    boolean_relay.printTo(pinAtmega);
  }
}

// buat fungsi set_data_sensor program
void set_data_sensor() {
  Firebase.setInt(firebaseData, path_sensor_1, 0);
  Firebase.setInt(firebaseData, path_sensor_2, 0);
  Firebase.setInt(firebaseData, path_tampungan, 0);
  delay(10);
}