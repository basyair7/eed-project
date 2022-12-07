// buat variable hidup atau mati
#define HIDUP LOW
#define MATI HIGH

// buat variable millis waktu sebelum diproses program
unsigned long waktuSebelum_1 = 0;
unsigned long waktuSebelum_2 = 0;
int jedaWaktu_1 = 100;  // 100 ms = 0.1 detik
int jedaWaktu_2 = 1000;

// buat fungsi mengambil perintah nodemcu untuk relay
void relay_main() {
  // buat variabel millis waktu sedang diproses program
  unsigned long waktuSekarang_1 = millis();
  if ((unsigned long)(waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1) {
    // buat object jsonBuffer
    waktuSebelum_1 = waktuSekarang_1;
    DynamicJsonBuffer jsonBuffer_relay;
    JsonObject& data_node = jsonBuffer_relay.parseObject(Serial3);
    if (data_node == JsonObject::invalid()) {
      return jsonBuffer_relay.clear();
    }

    // ambil data sensor mata air
    data_sensor_mata_air = map(analogRead(pinSensorAir), 0, 1023, 0, 100);

    // ambil data dari nodemcu
    data_sensor_tampungan = data_node["sensor_tampungan"];
    Serial.print(F("Data Tampungan Air : "));
    Serial.println(data_sensor_tampungan);
    Serial.print(F("Data Mata Air : "));
    Serial.println(data_sensor_mata_air);

    // jika tampungan air kosong dan sumber air ada maka pompa induk hidup
    if (data_sensor_tampungan <= batasMaksTandon && data_sensor_mata_air >= batasMinMataAir) {
      digitalWrite(pinRelay, HIDUP);
    } else if (data_sensor_tampungan >= batasMaksTandon || data_sensor_mata_air <= batasMinMataAir) {
      digitalWrite(pinRelay, MATI);
    }
  }
}

void send_data_sensor() {
  // buat variable millis waktu sedang diproses program
  unsigned long waktuSekarang_2 = millis();

  if ((unsigned long)(waktuSekarang_2 - waktuSebelum_2) >= jedaWaktu_2) {
    // buat object jsonBuffer
    waktuSebelum_2 = waktuSekarang_2;
    DynamicJsonBuffer jsonBuffer_data;
    JsonObject& data = jsonBuffer_data.createObject();
    data["sensor_mata_air"] = map(analogRead(pinSensorAir), 0, 1023, 100, 0);

    // mengirim data ke serial komunikasi
    data.printTo(Serial3);
    jsonBuffer_data.clear();
  }
}