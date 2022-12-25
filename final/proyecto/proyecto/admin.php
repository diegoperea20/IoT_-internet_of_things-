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
           echo "<h1>Estoy en admin $us </h1>";
        }
    ?>
    <br><a href="logout.php">Cerrar sesion</a>
    
</body>