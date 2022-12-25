<!DOCTYPE html>
<head>

</head>
<body>
    <?php
    if(isset($_POST["enviar"])){
        
        $u = $_POST["usuario"];
        $p = $_POST["pass"];
        $r = $_POST["rol"];
        $n = $_POST["nodo"];


        $url_rest = "http://localhost:3000/usuarios";
        $data = array(
            "user" => $u,
            "password" => $p,
            "rol"=>$r,
            "idnodo" => $n
        );
        $data_string = json_encode($data);
        $curl = curl_init($url_rest);

        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_setopt($curl, CURLOPT_POSTFIELDS, $data_string);
        curl_setopt($curl, CURLOPT_HEADER, true);
        curl_setopt($curl, CURLOPT_HTTPHEADER,
            array(
                'Content-Type:application/json',
                'Content-Length: ' . strlen($data_string)
            )
        );

        $result = curl_exec($curl);
    }
    else{


        
    ?>
    <h1>Crear usuario</h1>
    <form action="crearusuario_porsiiiii.php" method="post">
        Usuario :
        <input type="text" name="usuario"/><br>
        Password :
        <input type="text" name="pass"/><br>
        Rol :
        <input type="text" name="rol"/><br>
        Nodo :
        <input type="text" name="nodo"/><br>
        <input type="submit" name="enviar" value="ENVIAR"/>
    </form>
    <?php } ?>
</body>