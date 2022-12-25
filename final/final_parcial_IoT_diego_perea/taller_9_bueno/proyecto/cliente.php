<!DOCTYPE html>
<head>

</head>
<body>
    <?php
        session_start();
        $us=$_SESSION['usuario'];
            
        if($us== "") 
        { 
            header("Location: index.php");
        }
        else {
            $nodo = $_SESSION["nodo"];
            echo "<h1>Estoy en cliente $us - su nodo es $nodo</h1>";
        }
    ?>
    <br><a href="logout.php">Cerrar sesion</a>
    
</body>