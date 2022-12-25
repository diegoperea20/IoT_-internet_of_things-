<?php
session_start();
$us=$_SESSION['usuario'];
?>

<!doctype html>
<html lang="es">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-F3w7mX95PdgyTmZZMECAngseQB83DfGTowi0iMjiWaeVhAn4FJkqJByhZMI3AhiU" crossorigin="anonymous">
      <link rel="shortcut icon" type="image/x-icon" href="assets/fondo.webp">
      <!-- biblioteca  plotly-->
      <script src="https://cdn.plot.ly/plotly-latest.min.js"></script>
      <!-- fin biblioteca -->
    <title>Inicio :: <?php echo $us; ?></title>
    <style>
         
        #primero{
        
          background: rgb(34,193,195);
          background: linear-gradient(0deg, rgba(34,193,195,1) 0%, rgba(253,187,45,1) 100%);
        }
        

        .contenedor {
	width: 90%;
	max-width: 1200px;
	margin: auto;
	padding: 40px 0;

	
}

.titulo {
	font-size: 24px;
	padding: 20px 0;
}

.contenedor-conciertos {
  width:70%;
  display:flex;
  flex-wrap:wrap;
  gap: 30px;
	
}

.card {
	border-radius: 10px;
	min-height: 200px;
	font-weight: bold;
	padding: 20px;
	position: relative;
	overflow: hidden;
	background-size: cover;
	background-position: center center;

}

.card .textos {
	height: 100%;
	
	
}

.banner {
	border-radius: 10px;
	text-align: center;
	padding: 20px;
	background-size: cover;
	background-position: center center;


}

.banner ul {
	list-style: none;
}

.banner ul li {
	margin: 15px;
	font-weight: bold;
}

.banner .boton {
	background: #FFD600;
	display: block;
	width: 100%;
	font-weight: bold;
	font-size: 14px;
	text-align: center;
	padding: 10px;
	border: none;
	border-radius: 100px;
	font-family: 'Roboto', sans-serif;
	cursor: pointer;
}

    
      </style>
  </head>
  <body>
<nav class="navbar navbar-light bg-light mb-5" style="background-color: #33FF52!important;">
  <div class="container-fluid">
    <a class="navbar-brand" href="https://blogangular-c7858.web.app" style="color:#fff;">
     <strong style="color:#333;">Bienvenido Cliente</strong>
    </a>
    <span><a href="logout.php?email=<?php echo $us; ?>" style="color: #333; font-weight: bold;">Salir</a></span>
  </div>
</nav>

<div class="container">

<?php
 ?>
  <div class="alert alert-success alert-dismissible fade show" role="alert">
    <strong>Felicitaciones!</strong> Acaba de iniciar sesión correctamente..
  </div>
<?php  ?>


  <div class="row text-center">
    <div class="col-md-12 p-md-4" style="background-color: #f9f9f9;">
      
      <p>Cliente usuario : <strong><?php echo $us; ?></strong></p>
      <hr>
    </div>
  </div>

</div>

<!--Inicia codigo visualizacion-->
<div>
<div class="card" id="primero"><h1>Obtener Datos de Nodo</h1>
          <form  action="get_datos_cliente.php" method="post">
          IdNodo :
        <input type="text" name="idnodo"/><br>
        
        <input type="submit" name="get_datos_cliente" value="GET"/>
    </form></div>
    </div>



</body>
</html>
