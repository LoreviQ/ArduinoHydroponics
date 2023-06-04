const { INSPECT_MAX_BYTES } = require("buffer");
const { getUnpackedSettings } = require("http2");
const mongoose = require("mongoose");
const { Schema } = mongoose;

const arduinoSchema = new Schema({
    name: String,
    description: String
});

const sensorSchema = new Schema({
    name: String,
    sensorType: String,
    pin: Number,
    variable: String,
    unit: String,
    description: String,
    arduinoID: Schema.Types.ObjectId
});

const Arduino = mongoose.model("Arduino", arduinoSchema);
const Sensor = mongoose.model("Sensor", sensorSchema);

module.exports = { Arduino, Sensor };