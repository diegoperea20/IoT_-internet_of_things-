<!DOCTYPE html>
<head>

</head>
<body>
    <?php
    if(isset($_POST["enviar"])){
        echo "<h2> el usuario dio clic en enviar </h2>";
        $u = $_POST["usuario"];
        $p = $_POST["pass"];
        $url_rest = "http://localhost:3000/usuarios/$u";
        $curl = curl_init($url_rest);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        $respuesta = curl_exec($curl);

        if($respuesta===false){
            curl_close($curl);
            die ("Error...");
        }

        curl_close($curl);
        $resp = json_decode($respuesta);
        $tam = count($resp);

        if ($tam == 0)
            {
               header("Location: index.php"); 
            }
            else
            {
                $result = $resp[0];
                $pass = $result -> password;
                $rol = $result -> rol;
                $idnodo = $result -> idnodo;

                if ($pass == $p){
                    session_start();
                    $_SESSION['usuario']=$u;
                    $_SESSION['nodo']=$idnodo;
                    if($rol==1){
                        header("Location: cliente.php"); 
                    }
                    else {
                        header("Location: admin.php"); 
                    }
                }
                else {
                    header("Location: index.php"); 
                }
            }  
        
        
    }
    else
    {

    ?>
    <h1>Proyecto IoT</h1>
    <form action="index.php" method="post">
        Usuario :
        <input type="text" name="usuario"/><br>
        Password :
        <input type="password" name="pass"/><br>
        <input type="submit" name="enviar" value="ENVIAR"/>
    </form>
    <a href="crearusuario.php">Crear mi cuenta!</a>
    <?php } ?>
</body>