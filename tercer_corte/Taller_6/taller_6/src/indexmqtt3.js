var mqtt = require("mqtt");
var client = mqtt.connect("mqtt://localhost");
const mysql = require("mongodb");
var MongoClient = require("mongodb").MongoClient;
var url = "mongodb://localhost:27017/";
client.on("connect", function () {
  client.subscribe("topico1", function (err) {
    if (err) {
      console.log("error en la subscripcion");
    }
  });
});
client.on("message", function (topic, message) {
  // message is Buffer
  json1 = JSON.parse(message.toString());
  console.log(json1);
  //client.publish('topico2', 'mensaje recibido')
  MongoClient.connect(url, function (err, db) {
    if (err) throw err;
    var dbo = db.db("ProyectoDiegoP");
    dbo.collection("datosNodo").insertOne(json1, function (err, res) {
      if (err) throw err;
      console.log("1 document inserted");
      db.close();
    });
  });
  //client.end() //si se habilita esta opción el servicio termina
});
