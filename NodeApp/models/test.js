const { INSPECT_MAX_BYTES } = require("buffer");
const { getUnpackedSettings } = require("http2");
const mongoose = require("mongoose");
const internal = require("stream");
const { Schema } = mongoose;

const arduinoSchema = new Schema({
    name: String,
    description: String
});

const sensorSchema = new Schema({
    name: String,
    sensorType: String,
    variable: String,
    unit: String,
    arduinoID: Schema.Types.ObjectId
});

const readingSchema = new Schema({
    value: Number,
    sensorID: Schema.Types.ObjectId
});

const Arduino = mongoose.model("Arduino", arduinoSchema);
const Sensor = mongoose.model("Sensor", sensorSchema);
const Reading = mongoose.model("Reading", readingSchema);

module.exports = { Arduino, Sensor, Reading };