<?php
function Login()
{
	header ("WWW-Authenticate: Basic realm=\"LOCALHOST\"");
	header ("HTTP/1.0 401 Acceso no autorizado.");
	echo "<h2>ERROR EN AUTENTICACIÓN</h2>";
	echo "El nombre de usuario y/o contraseña no son válidos.";
	exit;
}

include 'pwdlist.txt';

if (!isset($PHP_AUTH_USER) or !isset($PHP_AUTH_PW)) {
   // Si no se han proporcionado aún los parámetros de autenticación,
   // muestra el diálogo de acceso.
   Login();
}
else
{
    // Secuencia de escape para evitar inserción de datos
    // erróneos en parámetros.
    $PHP_AUTH_USER = addslashes($PHP_AUTH_USER);
    // Obtiene hash MD5 de password de texto.
    $PHP_AUTH_PW = md5($PHP_AUTH_PW);
    // Verifica usuario in contraseña en base de datos.
    if (($PHP_AUTH_PW != $OK_PASSWORD) or
        ($PHP_AUTH_USER != $OK_USUARIO))
        {
	   // Si el resultado de la búsqueda en BD es vacío,
           // muestra de nuevo el diálogo de acceso.
	   Login();
	}
}

// A partir de aquí se muestra información únicamente a
// usuarios autenticados.
echo "¡Felicitaciones!, tu acceso es válido.";
?>

