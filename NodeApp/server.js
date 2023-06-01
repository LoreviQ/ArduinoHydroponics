const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const mongoose = require("mongoose");
const port = 8000;

const Arduino = require("./models/test");

app.use(bodyParser.json());

app.get("/", (req, res) => {
    res.send("Hello World!");
});

app.post("/", async (req, res) => {
    try {
        const arduino = await Arduino.create(req.body);
        res.status(200).json(arduino);
    } catch (error) {
        console.log(error.message);
        res.status(500).json({ message: error.message });
    }
});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`);
});
