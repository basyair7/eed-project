// buat variabel hidup atau mati
#define HIDUP LOW
#define MATI HIGH

unsigned long waktuSebelum_1 = 0; // buat variable millis waktu sebelum diproses program
int jedaWaktu_1 = 100; // 100 ms = 0,1 detik

// buat fungsi mengambil perintah nodemcu untuk relay
void get_data_relay() {
  unsigned long waktuSekarang_1 = millis(); // buat variable millis waktu sedang diproses program
  if ((unsigned long) (waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1) {
    // Buat object jsonBuffer
    waktuSebelum_1 = waktuSekarang_1;
    DynamicJsonBuffer jsonBuffer_relay;
    JsonObject& bool_relay = jsonBuffer_relay.parseObject(pinNodemcu);
    // JsonObject& bool_relay = jsonBuffer_relay.parseObject(Serial);
    if (bool_relay == JsonObject::invalid()) {
      jsonBuffer_relay.clear();
      Serial.flush();
      // pinNodemcu.flush();
      // Serial.println(F("Data Json Relay Invalid"));
      return;
    }

    // ambil data dari nodemcu
    hum_limit = bool_relay["hum_limit"];
    limit_tampungan = bool_relay["limit_tampungan"];
    bool_relay_1 = bool_relay["relay_1"];
    bool_relay_2 = bool_relay["relay_2"];
    bool_relay_auto = bool_relay["auto_relay"];
    int data_tampungan = map(analogRead(pinSensorTampungan), 0, 1023, 100, 0);

    if (bool_relay_1 == true) {
      if (data_tampungan >= limit_tampungan) digitalWrite(pinRelay_1, HIDUP);
    } 
    else {
      digitalWrite(pinRelay_1, MATI);
      // Serial.println("Pompa Air 1 Mati");
    }

    if (bool_relay_2 == true) {
      if(data_tampungan >= limit_tampungan) digitalWrite(pinRelay_2, HIDUP);
      // Serial.println("Pompa Air 2 Hidup");
    }
    else {
      digitalWrite(pinRelay_2, MATI);
      // Serial.println("Pompa Air 2 Mati");
    }

    if (bool_relay_auto == true){
      int data_1 = map(analogRead(pinSensor_1), 0, 1023, 100, 0);
      int data_2 = map(analogRead(pinSensor_2), 0, 1023, 100, 0);
      
      if(data_1 >= hum_limit) {
        digitalWrite(pinRelay_1, MATI);
      } else {
        if (data_tampungan >= limit_tampungan) digitalWrite(pinRelay_1, HIDUP);
      }

      if (data_2 >= hum_limit) {
        digitalWrite(pinRelay_2, MATI);
      } else {
        if (data_tampungan >= limit_tampungan) digitalWrite(pinRelay_2, HIDUP);
      }
    }
  } 
}