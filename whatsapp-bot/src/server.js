// memanggil library whatsapp-bot
const { Client, LocalAuth } = require("whatsapp-web.js");
const { getNumber } = require("./model");
const QRCode = require("qrcode-terminal");
const fs = require("fs");

// make uptimebot server
// const express = require("express");
// const app = express();

// let port = process.env.PORT || 3000;

// app.get("/", function (req, res){
//     res.send("Whatsapp-bot sudah online!");
// });

// app.listen(port, () => {
//     console.log(`Example app is listening on port http://localhost:${port}`);
// });

try {
    // membuat object client
    const client = new Client({
        restartOnAuthFail: true,
        puppeteer: {
            headless: true,
            args: [
                '--no-sandbox',
                '--disable-setuid-sandbox',
                '--disable-extensions'
            ],
        },
        authStrategy: new LocalAuth()
    });

    // memanggil fungsi object on untuk scan QR whatsapp
    client.on('qr', (qr) => {
        QRCode.generate(qr, { small: true });
    });

    // tampilkan pesan jika whatsapp-bot telah terkoneksi ke nomor
    client.on('authenticated', function () {
        console.log('\n\n*****Authenticate*****\n\n');
    });

    // tampilkan pesan jika whatsapp-bot gagal terkoneksi ke nomor
    client.on('auth_failure', msg => {
        // Fired if session restore was unsuccessful
        console.error("\n\n*****Authenticate Error*****\n", msg, "\n");
    });

    // bot is ready
    client.on('ready', () => {
        try {
            // mengambil nomor wa client di database
            getNumber((val) => {
                Object.keys(val).map(async key => {
                    // kirim ke nomor client jika bot siap digunakan
                    var nomorHp = await val[key].number;
                    if (nomorHp !== undefined) client.sendMessage(nomorHp, "Bot AWP Ready!");
                });
            });
                        
        } catch (e) {
            console.error(e)
        } finally {
            console.log("Bot Ready...");
        }
    });

    // memuat pesan perintah, beralih ke program event/message.js
    fs.readdir("./src/events/", (err, files) => {
        if (err) return console.error(err);
        files.forEach((file) => {
            const event = require(`./events/${file}`);
            let eventName = file.split(".")[0];
            client.on(eventName, event.bind(null, client));
        });
    });
    
    client.initialize();

    // disconnected whatsapp-bot jika pada aplikasi nomor wa-bot telah logout dari server
    client.on('disconnected', () => {
        client.destroy();
        client.initialize();
    });

} catch (e) {
    console.error(e);
}