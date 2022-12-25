
<style>
    table.blueTable {
  border: 1px solid #1C6EA4;
  background-color: #EEEEEE;
  width: 100%;
  text-align: left;
  border-collapse: collapse;
}
table.blueTable td, table.blueTable th {
  border: 1px solid #AAAAAA;
  padding: 3px 2px;
}
table.blueTable tbody td {
  font-size: 13px;
}
table.blueTable tr:nth-child(even) {
  background: #D0E4F5;
}
table.blueTable thead {
  background: #23AF38;
  background: -moz-linear-gradient(top, #5ac36a 0%, #39b74c 66%, #23AF38 100%);
  background: -webkit-linear-gradient(top, #5ac36a 0%, #39b74c 66%, #23AF38 100%);
  background: linear-gradient(to bottom, #5ac36a 0%, #39b74c 66%, #23AF38 100%);
  border-bottom: 2px solid #444444;
}
table.blueTable thead th {
  font-size: 15px;
  font-weight: bold;
  color: #FFFFFF;
  border-left: 2px solid #D0E4F5;
}
table.blueTable thead th:first-child {
  border-left: none;
}

table.blueTable tfoot {
  font-size: 15px;
  font-weight: bold;
  color: #FFFFFF;
  background: #D0E4F5;
  background: -moz-linear-gradient(top, #dcebf7 0%, #d4e6f6 66%, #D0E4F5 100%);
  background: -webkit-linear-gradient(top, #dcebf7 0%, #d4e6f6 66%, #D0E4F5 100%);
  background: linear-gradient(to bottom, #dcebf7 0%, #d4e6f6 66%, #D0E4F5 100%);
  border-top: 2px solid #444444;
}
table.blueTable tfoot td {
  font-size: 15px;
}
table.blueTable tfoot .links {
  text-align: right;
}
table.blueTable tfoot .links a{
  display: inline-block;
  background: #23AF38;
  color: #FFFFFF;
  padding: 2px 8px;
  border-radius: 5px;
}
    </style>
<table class="blueTable"  border="2px">
 <tr><th>idnodo</th><th>temperatura</th><th>humedad</th><th>fecha</th><th>hora</th><th>Mensaje T</th><th>Mensaje H</th></tr>
             



<?php
    if(isset($_POST["get_datos_cliente"])){
        
        $n = $_POST["idnodo"];

    $url_rest = "http://localhost:3000/datos/$n";
    $curl = curl_init($url_rest);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    $respuesta = curl_exec($curl);
    if($respuesta===false){
    curl_close($curl);
    die ("Error...");
    }
    curl_close($curl);
    //echo $respuesta;
    $resp = json_decode($respuesta);
    $tam = count($resp);
    for ($i=0; $i<$tam; $i++){
    $j = $resp[$i];
    $idnodo = $j -> idnodo;
    $temperatura = $j -> temperatura;
    $hum = $j -> humedad;
    $fecha = $j -> fecha;
    $hora = $j -> hora;
        //INICIO DE MENSAJE DE TEMPERATURA
        if($temperatura < 10){
            $mensaje_T="Temperatura Baja";
            
        }if($temperatura >= 10 && $temperatura <= 13 ){
                $mensaje_T="Temperatura Optima";
            }if($temperatura > 13){
                $mensaje_T="Temperatura Alta";
            }
        
            //INICIO DE MENSAJE DE HUMEDAD
        if($hum < 85){
            $mensaje_H="Humedad Baja";
            
        }if($hum >= 85 && $hum <= 90 ){
                $mensaje_H="Humedad Optima";
            }if($temperatura > 90){
                $mensaje_H="Humedad Alta";
            }
        


    echo "<tr><td >$idnodo</td><td>$temperatura </td><td>$hum</td><td>$fecha</td><td>$hora</td><td>$mensaje_T</td><td>$mensaje_H</td></tr>";
    }
        } else{

        }
   

?> 

</table>

<a href="cliente_home.php">Volver</a><br>


