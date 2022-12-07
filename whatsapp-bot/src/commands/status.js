/*
* Program menampilkan informasi database ke client melalui aplikasi whatsapp
* 
*/

const db = require("../db/firebaseConfig");
const ref = require("../db/path/reference.json");

exports.run = (client, msg) => {
    var data_sensor_1;
    var data_sensor_2;
    var status_pump_1;
    var status_pump_2;
    var status_auto_pump;

    const sensor = require("../db/path/sensor.json");
    db.ref(ref["ref-1"]).child(sensor["sensor-1"]).child("a").once("value", async (snapshot) => {
        if (snapshot.val() !== null) {
            data_sensor_1 = await snapshot.val();
            db.ref(ref["ref-1"]).child(sensor["sensor-2"]).child("a").once("value", async (snapshot) => {
                if (snapshot.val() !== null) {
                    data_sensor_2 = await snapshot.val();
                    db.ref(ref["ref-2"]).once("value", snapshot => {
                        if (snapshot.val() !== null) {
                            var bool_auto_pump = snapshot.val()["auto"];
                            var bool_pump_1 = snapshot.val()["switch-1"];
                            var bool_pump_2 = snapshot.val()["switch-2"];

                            if (bool_auto_pump === true) status_auto_pump = "Hidup";
                            else if (bool_auto_pump === false) status_auto_pump = "Mati";
                            if (bool_pump_1 === true) status_pump_1 = "Hidup";
                            else if (bool_pump_1 === false) status_pump_1 = "Mati";
                            if (bool_pump_2 === true) status_pump_2 = "Hidup";
                            else if (bool_pump_2 === false) status_pump_2 = "Mati";

                            var information = `\t*Status AWP*\nTanggal : ${DateTimeBot()}\n\nData Sensor\n> Kelembapan 1  : ${data_sensor_1}%\n> Kelembapan 2  : ${data_sensor_2}%\n\nStatus Pompa\n> Auto Pump  : ${status_auto_pump}\n> Pump 1        : ${status_pump_1}\n> Pump 2        : ${status_pump_2}`;

                            msg.reply(information);

                        } else;
                    });
                } else;
            });
        } else;
    });
}

var { DateTime } = require("luxon");

function DateTimeBot() {
    var local = DateTime.local();
    var rezonedString = local.setZone("Asia/Jakarta");

    // get Date
    let year = rezonedString.c.year;
    let month = rezonedString.c.month;
    let day = rezonedString.c.day;

    // get Time
    let hour = rezonedString.c.hour;
    let minute = rezonedString.c.minute;
    let second = rezonedString.c.second;

    let datetime = year + "/" + month + "/" + day + " (" + hour + ":" + minute + ":" + second + ")";
    return datetime;
}