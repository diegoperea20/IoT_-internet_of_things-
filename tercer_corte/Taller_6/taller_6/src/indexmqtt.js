var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://localhost') // URL del broker 

client.on('connect', function () {
    client.subscribe('topico1', function (err) {
        if (err) {
            console.log("error en la subscripcion")}
        })
})

client.on('message', function (topic, message) {
    // message is Buffer
    console.log(message.toString())
    //json1 = JSON.parse(message.toString())
    //let operador1=json1.op1;
    //let operador2=json1.op2;
    //let suma = operador1 + operador2;
    
    client.publish('topico2', "mensaje ")
    //client.end() //si se habilita esta opción el servicio termina
})
