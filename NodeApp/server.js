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

app.post("/setup", async (req, res) => {
    try {
        var arduinoJSON = req.body.arduino;
        var arduinoFind = await Arduino.find({'name' : arduinoJSON.name}).exec()[0];
        /*
        if (!arduinoFind) {
            var arduino = await Arduino.create(arduinoJSON);
        } else {
            var arduino = arduinoFind;
        }
        var arduinoID = arduino._id;
        var ids = [arduinoID];
        */
        /*
        var sensorsJSON = req.body.sensors;
        for (const sensorJSON of sensorsJSON) {
            sensorsJSON.arduinoID = arduinoID;
            var sensor = await Sensor.find({'name' : sensorJSON.name, 'arduinoID' : sensorJSON.arduinoID}).exec()[0];
            if (!sensor) {
                sensor = await Sensor.create(sensorJSON);
            }
            //ids.push(arduino);
        }
        //const sensors = await Sensor.insertMany(req.body.sensors);
        */
        res.status(200).json(arduinoFind);
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
