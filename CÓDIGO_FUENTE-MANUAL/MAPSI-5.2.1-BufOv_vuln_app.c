void modo_de_uso (char * nomprog)
{
   printf ("MODO DE USO: %s <par�metro> \n\n",nomprog);
}

unsigned long sp(void)       //peque�a funci�n para obtener
{__asm__("movl %esp,%eax");} //contenido de ESP
 
int main(int argc, char *argv[])
{
   char buffer[200];
                             // Algunos indicadores	para depuraci�n
   printf("*** Apuntador a pila (ESP) : 0x%x\n",sp());
   printf("*** Apuntador a buffer     : 0x%x\n",(unsigned long)buffer);  
   if (argc < 2)
   {
      modo_de_uso(argv[0]);
      return (1);
   }
   else	
	{
	   strcpy(buffer, argv[1]);
	   printf ("Programa vulnerable ante ataques de");
	   printf ("desbordamiento de memoria.\n");
         printf ("Entrada de datos como primer par�metro:\n\n");
         printf ("%s \n\n",buffer);
	   return (0);
   }
}

