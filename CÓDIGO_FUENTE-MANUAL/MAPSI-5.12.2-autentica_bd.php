<?php
function Login() 
{
	header ("WWW-Authenticate: Basic realm=\"LOCALHOST\"");
	header ("HTTP/1.0 401 Acceso no autorizado.");
	echo "<h2>ERROR EN AUTENTICACIÓN</h2>";
	echo "El nombre de usuario y contraseña no son válidos, favor de intentar de nuevo.";
	exit;
}

$db = mysql_connect('localhost','root','') or die ("Error en conexión a MySQL.");
mysql_select_db ('autentica') or die ("Error, no se pudo seleccionar la base de datos.");

if (!isset($PHP_AUTH_USER) or !isset($PHP_AUTH_PW)) {
	// Si no se han proporcionado aún los parámetros de autenticación, muestra el diálogo de acceso.
	Login();
} 
else 
{

	//obtiene hash md5 de contraseña
	$PHP_AUTH_PW = md5($PHP_AUTH_PW);
	//elimina funcionalidad addslashes(); activa por default.
	$PHP_AUTH_USER = stripslashes($PHP_AUTH_USER);
	// Verifica usuario con contraseña en base de datos.
	$result = mysql_query("select * from usuario where password='$PHP_AUTH_PW' and nombre='$PHP_AUTH_USER'");
	if(!mysql_num_rows($result)) 
	{
		// Si el resultado de la búsqueda en BD es vacío, muestra de nuevo el diálogo de acceso.
		Login();
	}
}

// A partir de aquí se muestra información únicamente a usuarios autenticados.
echo "¡Felicitaciones!, tu acceso es válido.";
?>
