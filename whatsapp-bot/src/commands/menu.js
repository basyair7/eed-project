/*
* Program menampilkan menu perintah yang tersedia didalam bot whatsapp
* 
*/

const { getMessage } = require("../model");

exports.run = (client, message) => {
    try {
        // get message
        getMessage((msg) => {
            var messages = "\n";
            let numbers = 1;
            let listMenu = '';
            let description = '';
            Object.keys(msg).map(async key =>{
                listMenu = msg[key].menu;
                description = msg[key].description;
                
                if(listMenu !== undefined && description !== undefined) return messages += `${numbers++}. ${listMenu}\t : ${description}\n`;
            });
            message.reply(`*Daftar Menu AWP BOT* ${messages}`);
        });
        
    } catch (e) {
        console.error(e)
    }
}