const { Router } = require("express");
const router = Router();
//const mysql = require("mongodb");
var MongoClient = require("mongodb").MongoClient;
var url = "mongodb://localhost:27017/";

router.get("/datosm", (req, res) => {
  6;
  MongoClient.connect(url, function (err, db) {
    if (err) throw err;
    var dbo = db.db("ProyectoMongo");
    dbo
      .collection("datosNodo")
      .find({})
      .toArray(function (err, result) {
        if (err) throw err;
        console.log(result);
        res.json(result);
        db.close();
      });
  });
});
router.post("/datosm", (req, res) => {
  console.log(req.body);
  var json2 = req.body;
  MongoClient.connect(url, function (err, db) {
    if (err) throw err;
    var dbo = db.db("ProyectoMongo");
    dbo.collection("datosNodo").insertOne(json2, function (err, res) {
      if (err) throw err;
      console.log("1 document inserted");
      db.close();
    });
  });
  res.send("dato insertado");
});
module.exports = router;
