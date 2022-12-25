const { Router } = require('express');
const router = Router();
const mysql = require('mysql');

// se crea la conexión a mysql
const connection = mysql.createPool({
    connectionLimit: 500,
    host: 'localhost',
    user: 'root',
    password: '', //el password de ingreso a mysql
    database: 'proyecto',
    port: 3306
});

//function get en la ruta /datos, que trae todos los datos almacenados en la tabla

router.get('/nodos', (req, res) => {
    var json1 = {}; //variable para almacenar cada registro que se lea, en formato json
    var arreglo = []; //variable para almacenar todos los datos, en formato arreglo de json

    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error;  //si no se pudo conectar
        }
        else {
            console.log('Conexion correcta.');
            //ejecución de la consulta
            tempConn.query('SELECT * FROM nodo', function (error, result) {
                var resultado = result; //se almacena el resultado de la consulta en la variable resultado
                if (error) {
                    throw error;
                    res.send("error en la ejecución del query");
                } else {
                    tempConn.release(); //se librea la conexión
                    for (i = 0; i < resultado.length; i++) { 		//se lee el resultado y se arma el json
                        json1 = { "idnodo": resultado[i].idnodo, "nombre": resultado[i].nombre, "estado": resultado[i].estado};
                        console.log(json1); //se muestra el json en la consola
                        arreglo.push(json1); //se añade el json al arreglo
                    }
                    res.json(arreglo); //se retorna el arreglo
                }
            });
        }
    });
});

//función post en la ruta /datos que recibe datos
router.post('/nodos', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('INSERT INTO nodo VALUES(?,?,?)', [json1.idnodo, json1.nombre, json1.estado], function (error, result) { //se ejecuta lainserción
                if (error) {
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("nodo almacenado"); //mensaje de respuesta
                }
            });
        }
    });
}); 

//función get para consultar un nodo
router.get('/nodos/:idnodo', (req, res) => {
    var json1 = {}; //variable para almacenar cada registro que se lea, en formato json
    var arreglo = []; //variable para almacenar todos los datos, en formato arreglo de json
    var id = req.params.idnodo; //recogemos el parámetro enviado en la url

    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error;  //si no se pudo conectar
        } else {
            console.log('Conexion correcta.');
            //ejecución de la consulta
            tempConn.query('SELECT * FROM nodo where idnodo=?', [id], function (error, result) {
                var resultado = result; //se almacena el resultado de la consulta en la variable resultado
                if (error) {
                    throw error;
                    //res.send("error en la ejecución del query");
                } else {
                    tempConn.release(); //se libera la conexión
                    for (i = 0; i < resultado.length; i++) { 		//se lee el resultado y se arma el json
                        json1 = { "idnodo": resultado[i].idnodo, "nombre": resultado[i].nombre, "estado": resultado[i].estado};
                        console.log(json1); //se muestra el json en la consola
                        arreglo.push(json1); //se añade el json al arreglo
                    }
                    res.json(arreglo); //se retorna el arreglo
                }
            }
            );
        }
    });
});

//función put para modificar un nodo
router.put('/nodos/:idnodo', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    var id = req.params.idnodo; //recogemos el parámetro enviado en la url
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('UPDATE nodo SET nombre=?, estado=? WHERE idnodo=?', [json1.nombre, json1.estado, id], function (error, result) { //se ejecuta lainserción
                if (error) {
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("nodo actualizado"); //mensaje de respuesta
                }
            });
        }
    });
}); 

//función delete para borrar un nodo
router.delete('/nodos/:idnodo', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    var id = req.params.idnodo; //recogemos el parámetro enviado en la url
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('DELETE FROM nodo WHERE idnodo=?', [id], function (error, result) { //se ejecuta el borrado
                if (error) {
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("nodo borrado"); //mensaje de respuesta
                }
            });
        }
    });
}); 

module.exports = router;
