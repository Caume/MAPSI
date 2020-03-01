<?php
function Login()
{
	header ("WWW-Authenticate: Basic realm=\"LOCALHOST\"");
	header ("HTTP/1.0 401 Acceso no autorizado.");
	echo "<h2>ERROR EN AUTENTICACI�N</h2>";
	echo "El nombre de usuario y/o contrase�a no son v�lidos.";
	exit;
}

include 'pwdlist.txt';

if (!isset($PHP_AUTH_USER) or !isset($PHP_AUTH_PW)) {
   // Si no se han proporcionado a�n los par�metros de autenticaci�n,
   // muestra el di�logo de acceso.
   Login();
}
else
{
    // Secuencia de escape para evitar inserci�n de datos
    // err�neos en par�metros.
    $PHP_AUTH_USER = addslashes($PHP_AUTH_USER);
    // Obtiene hash MD5 de password de texto.
    $PHP_AUTH_PW = md5($PHP_AUTH_PW);
    // Verifica usuario in contrase�a en base de datos.
    if (($PHP_AUTH_PW != $OK_PASSWORD) or
        ($PHP_AUTH_USER != $OK_USUARIO))
        {
	   // Si el resultado de la b�squeda en BD es vac�o,
           // muestra de nuevo el di�logo de acceso.
	   Login();
	}
}

// A partir de aqu� se muestra informaci�n �nicamente a
// usuarios autenticados.
echo "�Felicitaciones!, tu acceso es v�lido.";
?>

