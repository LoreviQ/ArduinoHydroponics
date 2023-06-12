const express = require("express");
const app = express();
const path = require("path");
const bodyParser = require("body-parser");
const mongoose = require("mongoose");
const port = 8000;

const { Arduino, Sensor, Reading } = require("./models/test");

// fetches root files from client/build
app.use(express.static(path.join(__dirname, 'build')));
app.use(bodyParser.json());

app.get("/", (req, res) => {
    res.send("Hello World");
    //res.sendFile(path.join(__dirname, "build", "index.html"));
});

// Setup endpoint that arduino calls on boot.
// Returns id corresponding to the Arduino
app.post("/setup/arduino", async (req, res) => {
    try {
        var arduino = await Arduino.find({'name' : req.body.name}).exec();
        arduino = arduino[0];
        if (!arduino) {
            arduino = await Arduino.create(req.body);
        }
        res.status(200).send("ID: " + arduino._id);
    } catch (error) {
        console.log(error.message);
        res.status(500).json({ message: error.message });
    }
});

// Setup endpoint that arduino calls on boot.
// Returns id corresponding to the Sensor
app.post("/setup/sensor", async (req, res) => {
    try {
        var sensor = await Sensor.find({'name' : req.body.name, 'arduinoID' : req.body.arduinoID}).exec();
        sensor = sensor[0];
        if (!sensor) {
            sensor = await Sensor.create(req.body);
        }
        res.status(200).send("ID: " + sensor._id);
    } catch (error) {
        console.log(error.message);
        res.status(500).json({ message: error.message });
    }
});

// Setup endpoint that arduino calls on boot.
// Returns id corresponding to the Sensor
app.post("/reading", async (req, res) => {
    try {
        await Reading.insertMany(req.body);
        res.status(200);
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
