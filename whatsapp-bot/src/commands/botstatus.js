/*
* Program menampilkan informasi server ke client melalui aplikasi whatsapp
* 
*/

const { platform, arch, cpus } = require('os');
const model = cpus()[0].model + " " + arch();

exports.run = (client, message) => {
    var information = `\t*System Information*\n\nTanggal : ${DateTimeBot()}\nCPU : ${model}\nPlatform : ${platform}\nStatus : Online\n`;

    message.reply(information);
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