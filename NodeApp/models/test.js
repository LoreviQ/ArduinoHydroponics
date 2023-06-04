const { INSPECT_MAX_BYTES } = require("buffer");
const { getUnpackedSettings } = require("http2");
const mongoose = require("mongoose");
const { Schema } = mongoose;

const arduinoSchema = new Schema({
    name: String,
    description: String
});

const sensorSchema = new Schema({
    sensorType: String,
    pin: Number,
    variable: String,
    unit: String,
    description: String
});

const Arduino = mongoose.model("Arduino", arduinoSchema);
const Sensor = mongoose.model("Sensor", sensorSchema);

module.exports = { Arduino, Sensor };