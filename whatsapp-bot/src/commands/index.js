const menu = require("./menu"); // call command menu
const status = require("./status"); // call command status
const pump = require("./pump"); // call command pump
const botstatus = require("./botstatus"); // call command botstatus

// aktifkan semua perintah bot ke dalam file index
module.exports = {
    menu,
    status,
    pump,
    botstatus,
}