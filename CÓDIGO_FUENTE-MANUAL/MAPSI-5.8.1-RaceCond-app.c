#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

char buffer[1000];
int main (void)
{
   pid_t pid;
   int cont, cont2;
   
   /* limpia el buffer */   
   for (cont=0; cont<1000; cont++)
   setbuf (stdout,NULL);
   setbuf (stdin,NULL);
   
   {
      buffer[cont]='\0';
   }

 while (1)
 {     
   printf ("Escribe palabras cuyas vocales serán filtradas:\n");   
   if ( (pid = fork()) < 0)
   {
      perror("Error en instrucción FORK\n");
      exit (1);
   }
   else
   {       
      scanf ("%s",buffer);
      if (pid == 0)           /*Si es el programa padre no apliques 
                                ningún filtro */
      {         
         
      }
      else                    /*Programa hijo... filtra las vocales*/
      {                  
         cont = 0;
         while ((buffer[cont] != '\0') && (cont < 1000))
         {
            if (buffer[cont] == 'a')
            {
               buffer[cont] = '*';
            }
            if (buffer[cont] == 'e')
            {
               buffer[cont] = '*';
            } 
            if (buffer[cont] == 'i')
            {
               buffer[cont] = '*';
            }
            if (buffer[cont] == 'o')
            {
               buffer[cont] = '*';
            }
            if (buffer[cont] == 'u')
            {
               buffer[cont] = '*';
            }
            cont++;
         }    
      }
      printf ("Palabra filtrada: %s\n",buffer);   
   }
  }   
}

