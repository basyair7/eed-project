// buat variable hidup atau mati
#define HIDUP LOW
#define MATI HIGH

unsigned long waktuSebelum_1 = 0; // buat variable millis waktu sebelum diproses program
int jedaWaktu_1 = 100; // 100 ms = 0.1 detik

// buat fungsi mengambil perintah nodemcu untuk relay
void relay_main() {
  unsigned long waktuSekarang_1 = millis(); // buat variable millis waktu sedang diproses program
  if ((unsigned long) (waktuSekarang_1 - waktuSebelum_1) >= jedaWaktu_1) {
    // Buat object jsonBuffer
    waktuSebelum_1 = waktuSekarang_1;
    DynamicJsonBuffer jsonBuffer_relay;
    JsonObject& boolean_relay = jsonBuffer_relay.parseObject(pinNodemcu);
    if (boolean_relay == JsonObject::invalid()) {
      return jsonBuffer_relay.clear();
    }

    // ambil data dari nodemcu
    hum_limit = boolean_relay["hum_limit"];
    limit_tampungan = boolean_relay["limit_tampungan"];
    boolean_relay_1 = boolean_relay["relay_1"];
    boolean_relay_2 = boolean_relay["relay_2"];
    boolean_relay_auto = boolean_relay["auto_relay"];
    int data_tampungan = map(analogRead(pinSensorTampungan), 0, 1023, 100, 0);

    if (boolean_relay_1 == true) {
      if (data_tampungan >= limit_tampungan) {
        digitalWrite(pinRelay_1, HIDUP);
      }
      else {
        digitalWrite(pinRelay_1, MATI);
      }
    } 
    else {
      digitalWrite(pinRelay_1, MATI);
    }

    if (boolean_relay_2 == true) {
      if(data_tampungan >= limit_tampungan) {
        digitalWrite(pinRelay_2, HIDUP);
      }
      else {
        digitalWrite(pinRelay_2, MATI);
      }
    }
    else {
      digitalWrite(pinRelay_2, MATI);
    }

    if (boolean_relay_auto == true){
      int data_1 = map(analogRead(pinSensor_1), 0, 1023, 100, 0);
      int data_2 = map(analogRead(pinSensor_2), 0, 1023, 100, 0);
      
      if(data_1 >= hum_limit) {
        digitalWrite(pinRelay_1, MATI);
      } else {
        if (data_tampungan >= limit_tampungan) {
          digitalWrite(pinRelay_1, HIDUP);
        } else {
          digitalWrite(pinRelay_1, MATI);
        }
      }

      if (data_2 >= hum_limit) {
        digitalWrite(pinRelay_2, MATI);
      } else {
        if (data_tampungan >= limit_tampungan) {
          digitalWrite(pinRelay_2, HIDUP);
        } else {
          digitalWrite(pinRelay_2, MATI);
        }
      }
    }
  } 
}