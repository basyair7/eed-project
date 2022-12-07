const { getMessage } = require("../model"); // call dbMessage
const {
    menu,
    status,
    pump,
    botstatus,
} = require("../commands"); // call command message

module.exports = async (client, message) => {
    try {
        // command in whatsapp
        let messages = await message.body.toLowerCase();

        // Check Commands in Database
        getMessage((data) => {
            Object.keys(data).map(async (key) => {

                // jika perintah client tersedia di database, maka jalankan file pada commands
                if (messages === await data[key].q) {

                    if (messages === "menu" && messages === data[key].q 
                        || messages === "help" && messages === data[key].q) return menu.run(client, message);

                    if (messages === "status" && messages === data[key].q 
                        || messages === "info" && messages === data[key].q) return status.run(client, message);

                    if (messages === "bot status" && messages === data[key].q) return botstatus.run(client, message);

                    if (messages === 'check 1' && messages === data[key].q
                        || messages === 'check 2' && messages === data[key].q) 
                    {
                        return message.reply(`Persentase Kelembapan : ${data[key].a} %`);
                    }

                    // jika perintah client berujuk ke perintah pompa, maka aktifkan program pump.js
                    else {
                        pump.run(client, message);
                    }

                } else;
            });
        });

    } catch (e) {
        console.log(e);
    }
}