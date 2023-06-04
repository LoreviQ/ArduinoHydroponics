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
        console.log(res.body);
        const arduino = await Arduino.create(res.arduino);
        const sensors = await Sensor.insertMany(res.sensors);
        res.status(200).json(sensors);
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
