const mongoose = require("mongoose");
const { Schema } = mongoose;

const arduinoSchema = new Schema({
    name: String,
    SN: Number,
});

const Arduino = mongoose.model("Arduino", arduinoSchema);

module.exports = Arduino;
