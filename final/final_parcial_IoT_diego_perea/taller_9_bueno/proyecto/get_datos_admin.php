<table border="2px">
 <tr><th>idnodo</th><th>temperatura</th><th>humedad</th><th>fecha</th><th>hora</th></tr>
             



<?php
 $url_rest = "http://localhost:3000/datos/";
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
 echo "<tr><td>$idnodo</td><td>$temperatura </td><td>$hum</td><td>$fecha</td><td>$hora</td></tr>";
 }
        
   

?> 

</table>
<a href="home.php">Volver</a><br>
 
