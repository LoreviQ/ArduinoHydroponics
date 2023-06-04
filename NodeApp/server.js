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
        var query = Arduino.find({name : arduinoJSON.name}).exec();
        //const arduino = await Arduino.create(req.body.arduino);

        //var sensorsJSON = req.body.sensors;
        //const sensors = await Sensor.insertMany(req.body.sensors);
        res.status(200).json(query);
    } catch (error) {
        console.log(error.message);
        res.status(500).json({ message: error.message });
    }
});

mongoose.set("strictQuery", false);
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
