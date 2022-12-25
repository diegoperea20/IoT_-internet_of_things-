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

router.get('/usuarios', (req, res) => {
    var json1 = {}; //variable para almacenar cada registro que se lea, en formato json
    var arreglo = []; //variable para almacenar todos los datos, en formato arreglo de json

    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error;  //si no se pudo conectar
        }
        else {
            console.log('Conexion correcta.');
            //ejecución de la consulta
            tempConn.query('SELECT * FROM usuario', function (error, result) {
                var resultado = result; //se almacena el resultado de la consulta en la variable resultado
                if (error) {
                    throw error;
                    res.send("error en la ejecución del query");
                } else {
                    tempConn.release(); //se librea la conexión
                    for (i = 0; i < resultado.length; i++) { 		//se lee el resultado y se arma el json
                        json1 = { "usuario": resultado[i].user, "password": resultado[i].password, "rol": resultado[i].rol, "idnodo": resultado[i].idnodo};
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
router.post('/usuarios', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('INSERT INTO usuario VALUES(?,?,?,?)', [json1.user, json1.password, json1.rol, json1.idnodo], function (error, result) { //se ejecuta lainserción
                if (error) {
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("usuario almacenado"); //mensaje de respuesta
                }
            });
        }
    });
}); 

//función get para consultar un nodo
router.get('/usuarios/:idusuario', (req, res) => {
    var json1 = {}; //variable para almacenar cada registro que se lea, en formato json
    var arreglo = []; //variable para almacenar todos los datos, en formato arreglo de json
    var id = req.params.idusuario; //recogemos el parámetro enviado en la url

    connection.getConnection(function (error, tempConn) { //conexion a mysql
        if (error) {
            throw error;  //si no se pudo conectar
        } else {
            console.log('Conexion correcta.');
            //ejecución de la consulta
            tempConn.query('SELECT * FROM usuario where user=?', [id], function (error, result) {
                var resultado = result; //se almacena el resultado de la consulta en la variable resultado
                if (error) {
                    throw error;
                    //res.send("error en la ejecución del query");
                } else {
                    tempConn.release(); //se libera la conexión
                    for (i = 0; i < resultado.length; i++) { 		//se lee el resultado y se arma el json
                        json1 = { "usuario": resultado[i].user, "password": resultado[i].password, "rol": resultado[i].rol, "idnodo": resultado[i].idnodo};
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

//función put para modificar un usuario
router.put('/usuarios/:idusuario', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    var id = req.params.idusuario; //recogemos el parámetro enviado en la url
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('UPDATE usuario SET password=?, rol=?, idnodo=? WHERE user=?', [json1.password, json1.rol, json1.idnodo, id], function (error, result) { //se ejecuta lainserción
                if (error) {
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("usuario actualizado"); //mensaje de respuesta
                }
            });
        }
    });
}); 

//función delete para borrar un nodo
router.delete('/usuarios/:idusuario', (req, res) => {
    console.log(req.body); //mustra en consola el json que llego
    json1 = req.body; //se almacena el json recibido en la variable json1
    var id = req.params.idusuario; //recogemos el parámetro enviado en la url
    connection.getConnection(function (error, tempConn) { //conexion a mysql
        
        if (error) {
            throw error; //en caso de error en la conexion
        }
        else {
            console.log('Conexion correcta.');
            tempConn.query('DELETE FROM usuario WHERE user=?', [id], function (error, result) { //se ejecuta el borrado
                if (error) {
                    res.send("error al ejecutar el query");
                } else {
                    tempConn.release();
                    res.send("usuario borrado"); //mensaje de respuesta
                }
            });
        }
    });
}); 

module.exports = router;
