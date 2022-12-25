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
        
          background: rgb(38,166,203);
          background: linear-gradient(90deg, rgba(38,166,203,1) 1%, rgba(121,99,9,0.76234243697479) 13%, rgba(129,255,0,0.8127626050420168) 95%);
        }
        #segundo{
          background-color:#FFA07A;
        }
        #tercero{
          background-color:#FFEE58;
        }
        #cuarto{
          background-color:#33CCFF;
        }
        #cinco{
          background-color:#BDBDBD;
        }
        #sexto{
          background: rgb(238,174,202);
          background: radial-gradient(circle, rgba(238,174,202,1) 0%, rgba(148,187,233,1) 100%);
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






  #imput{
    margin-left: 30px;
  }




    
      </style>
  </head>
  <body>
<nav class="navbar navbar-light bg-light mb-5" style="background-color: #f7c600 !important;">
  <div class="container-fluid">
    <a class="navbar-brand" href="https://blogangular-c7858.web.app" style="color:#fff;">
     <strong style="color:#333;">Bienvenido Admin </strong>
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
      
      <p>Admin usuario : <strong><?php echo $us; ?></strong></p>
      <hr>
    </div>
  </div>

</div>

<!-- Inicio de CRUD-->


<div class="contenedor">
<div class="contenedor-conciertos">
  <div class="card" id="primero" >
<h1>Crear usuario</h1>
    <form action="post_admin.php" method="post">
        Usuario :
        <input type="text" name="usuario" id="imput" /><br>
        Password :
        <input type="text" name="pass" style="margin-left:18px;"/><br>
        Rol :
        <input type="text" name="rol" style="margin-left:65px;"/><br>
        Nodo :
        <input type="text" name="nodo" style="margin-left:45px;" /><br>
        <input type="submit" name="posti" value="Agregar"/>
        
    </form> </div>

<div  class="card" id="segundo"> <h1>Borrar usuario</h1>
    <form  action="dele_admin.php" method="post">
        Usuario :
        <input type="text" name="usuario"/><br>
        
        
        <input type="submit" name="dele" value="Borrar"/>
    </form></div>


    <div  class="card"  id="tercero" > <h1>Modificar en Usuario</h1>
    <form  action="modifica_usuario.php" method="post">
         Usuario :
        <input type="text" name="usuario" style="margin-left:60px;" /><br>
        Password nueva:
        <input type="text" name="pass" style="margin-left:1px;"/><br>
        Rol nuevo:
        <input type="text" name="rol"  style="margin-left:48px;" /><br>
        Nodo nuevo :
        <input type="text" name="nodo"  style="margin-left:25px;" /><br>
        <input type="submit" name="modifica" value="Modificar"/>
    </form></div>

    <div  class="card" id="cuarto"><h1>Crear Nodos</h1>
          <form  action="crear_nodo.php" method="post">
          IdNodo :
        <input type="text" name="idnodo" style="margin-left:5px;" /><br>
        Nombre :
        <input type="text" name="nombre_nodo"/><br>
        
        
        <input type="submit" name="creanodo" value="Crear"/>
    </form></div>

    <div  class="card" id="cinco"><h1>Borrar Nodos</h1>
          <form  action="dele_nodos.php" method="post">
          IdNodo :
        <input type="text" name="idnodo"/><br>
        
        
        <input type="submit" name="borrar_nodo" value="Borrar"/>
    </form></div>
    
    <div  class="card" id="sexto"><h1>Obtener Datos TODOS</h1>
          <form  action="get_datos_admin.php" method="post">
        
        <input type="submit" name="get_datos_admin" value="GET"/>
    </form></div>

    </div>
</div>

    
<script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.bundle.min.js" integrity="sha384-Piv4xVNRyMGpqkS2by6br4gNJ7DXjqk09RmUpJ8jgGtD7zP9yug3goQfGII0yAns" crossorigin="anonymous"></script>

  </body>
</html>


