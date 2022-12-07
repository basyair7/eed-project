const firebase = require("../db/firebaseConfig");
const reference = require("../db/path/reference.json");

function getMessage (callback) {
    firebase.ref(reference["ref-1"]).once(
        'value',
        (snapshot) => {
            if (snapshot.val() !== null) {
                callback(snapshot.val());
            } else;
        },
        (err) => {
            console.error(`Read Failed ${err.name}`);
        }
    )
};

module.exports = getMessage;