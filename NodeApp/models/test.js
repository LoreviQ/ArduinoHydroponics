import mongoose from "mongoose";
const { Schema } = mongoose;

const arduinoSchema = new Schema({
    _id: ObjectId,
    name: String,
    SN: Number,
});

const Arduino = mongoose.model("Arduino", arduinoSchema);

module.exports = Arduino;
