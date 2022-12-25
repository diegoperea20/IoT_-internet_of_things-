<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="preconnect" href="https://fonts.googleapis.com">
	<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
	<link href="https://fonts.googleapis.com/css2?family=Quicksand:wght@500;700&display=swap" rel="stylesheet">  
	<link rel="stylesheet" href="assets/css/estilos.css">
	<link rel="shortcut icon" type="image/x-icon" href="assets/fondo.webp">
	<title>Login sesión con PHP y MySQL</title>

	<!--Notificacion -->
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/toastr.js/latest/toastr.min.css">
	<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/toastr.js/latest/toastr.min.js"></script>
	<script src="assets/js/script.js"></script>
</head>
<body>
<!--Precarga --->
<div id='spinner'></div>

<?php include("msjs.php"); ?>

	<div class="contenedor">
		<div class="columna-izquierda">
			<div class="registro activo" id="registro">
				<div class="header">
					<h1>¡Iniciar sesión!</h1>
					<p> - - - - - - - - - - - - - - - -</p>
				</div>
		
				<form class="formulario" name="formulario" action="index.php"  method="POST">
					<label for="nombre">Correo Electrónico</label>
					<div class="contenedor-input">
						<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-envelope" viewBox="0 0 16 16">
							<path d="M0 4a2 2 0 0 1 2-2h12a2 2 0 0 1 2 2v8a2 2 0 0 1-2 2H2a2 2 0 0 1-2-2V4zm2-1a1 1 0 0 0-1 1v.217l7 4.2 7-4.2V4a1 1 0 0 0-1-1H2zm13 2.383-4.758 2.855L15 11.114v-5.73zm-.034 6.878L9.271 8.82 8 9.583 6.728 8.82l-5.694 3.44A1 1 0 0 0 2 13h12a1 1 0 0 0 .966-.739zM1 11.114l4.758-2.876L1 5.383v5.73z"/>
						</svg>
						<input type="email" name="usuario" id="emailUser" required="true" autofocus="autofocus">
					</div>
		
					<label for="correo">Clave</label>
					<div class="contenedor-input">
						<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-person-circle" viewBox="0 0 16 16">
							<path d="M11 6a3 3 0 1 1-6 0 3 3 0 0 1 6 0z"/>
							<path fill-rule="evenodd" d="M0 8a8 8 0 1 1 16 0A8 8 0 0 1 0 8zm8-7a7 7 0 0 0-5.468 11.37C3.242 11.226 4.805 10 8 10s4.757 1.225 5.468 2.37A7 7 0 0 0 8 1z"/>
						</svg>
						<input type="password" name="pass" id="passwordUser" required>
					</div>
					
					<div class="contenedor-boton">
						<input type="submit" name="enviar" value="Entrar Ahora!" id="btn-login">
					</div>
					<div class="contenedor-boton">
						<a href="crearusuario.php">Crear mi cuenta!</a>
					</div><br>

					<div class="contenedor-boton">
						<a href="info_pagina.php">¿Cómo funciona?</a>
					</div>
					
				</form>
			</div>
		</div>

		<div class="columna-derecha">

		</div> 
	</div>
	
</body>
</html>