const mongoose = require("mongoose");
const { Schema } = mongoose;

const arduinoSchema = new Schema({
    _id: Schema.Types.ObjectId,
    name: String,
    SN: Number,
});

const Arduino = mongoose.model("Arduino", arduinoSchema);

module.exports = Arduino;
