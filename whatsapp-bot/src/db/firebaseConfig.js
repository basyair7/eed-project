var admin = require("firebase-admin");
var serviceAccount = require("./firebaseKey/serviceAccount.json");
var https = require("./firebaseKey/httpsFirebase.json");

admin.initializeApp({
    credential: admin.credential.cert(serviceAccount),
    databaseURL: https["https"]
});


const db = admin.database();

module.exports = db;