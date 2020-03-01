/* EJCasm.c, Módulo principal en lenguaje C de la aplicación EJCasm */
#include <stdio.h>
extern int ejemplo(int x, int y);

int main ()
{
   int result;
   result = ejemplo(1,2);
   printf ("el resultado es: %d \n",result);
   return (result);
}
