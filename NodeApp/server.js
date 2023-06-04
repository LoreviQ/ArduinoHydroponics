const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const mongoose = require("mongoose");
const port = 8000;

const { Arduino, Sensor } = require("./models/test");

app.use(bodyParser.json());

app.get("/", (req, res) => {
    res.send("Hello World!");
});

// Setup endpoint that arduino calls on boot.
// Returns array of ids corresponding to the Arduino and Sensor
app.post("/setup", async (req, res) => {
    try {
        // Arduino
        var arduinoJSON = req.body.arduino;
        var arduino = await Arduino.find({'name' : arduinoJSON.name}).exec();
        arduino = arduino[0];
        if (!arduino) {
            var arduino = await Arduino.create(arduinoJSON);
        }
        var ids = [arduino._id];

        // Sensors
        for (const sensorJSON of req.body.sensors) {
            sensorJSON.arduinoID = arduino._id;
            var sensor = await Sensor.find({'name' : sensorJSON.name, 'arduinoID' : sensorJSON.arduinoID}).exec();
            sensor = sensor[0];
            if (!sensor) {
                sensor = await Sensor.create(sensorJSON);
            }
            ids.push(sensor._id);
        }
        res.status(200).json(ids);
    } catch (error) {
        console.log(error.message);
        res.status(500).json({ message: error.message });
    }
});

mongoose.set("strictQuery", true);
mongoose
    .connect("mongodb://testUser:testPassword@localhost:27017/test", { useNewUrlParser: true })
    .then(() => {
        console.log("connected to MongoDB");
        app.listen(port, () => {
            console.log(`Example app listening on port ${port}`);
        });
    })
    .catch((error) => {
        console.log(error);
    });
