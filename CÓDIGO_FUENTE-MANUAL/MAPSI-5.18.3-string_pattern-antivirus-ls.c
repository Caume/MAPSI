#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MAX_PATTERN_SIZE 100
#define MAX_PATTERNS 10
#define MAX_FILEBUF_SIZE 1000
#define MAX_VIR_NAME 100

struct VIRUSPATTERN     /* Estructura de patrón para virus */
{
   char nombre_virus [MAX_VIR_NAME];
   long offset_start;  /* Desplazamiento en bytes dentro del archivo */
   int pattern_size;   /* Tamaño en bytes del patrón */
   unsigned char pattern [MAX_PATTERN_SIZE]; /* repositorio del patrón */
};

struct VIRUSPATTERN lista_de_patrones [MAX_PATTERNS];
int num_patterns=0;
int infectados=0;

int buscaPatron (struct VIRUSPATTERN patronvir, char *filebuf)
{
   int filebuf_top=0;
   int encontrado=0;
   int cont; 
   while ((encontrado==0) && 
          (filebuf_top <= (MAX_FILEBUF_SIZE-(patronvir.pattern_size))))
   {
      encontrado=1; /* asume que se econtró el virus a menos que haya
                       alguna discrepancia */
      for (cont=0;cont<patronvir.pattern_size;cont++)
      {
         /* si hay una sola discrepancia sale del ciclo "for" */ 
         if ( (unsigned char)patronvir.pattern[cont] != 
              (unsigned char)filebuf[filebuf_top+cont])
         {
             encontrado=0;
             cont = patronvir.pattern_size; /* termina ciclo "for" */             
         }
      }
      filebuf_top++; /* incrementa rango de comparación */         
   }
   return (encontrado);   
}

void generaPatrones () 
{
     int cont=0;
     
     /* prepara primer patrón */
     lista_de_patrones[0].offset_start = 0;
     lista_de_patrones[0].pattern_size = 13;
     memcpy (lista_de_patrones[0].pattern,"Linux Knoppix",13); 
     memcpy (lista_de_patrones[0].nombre_virus,"vir_pat_1",9); 
     
     /* prepara segundo patrón */
     lista_de_patrones[1].offset_start = -1;
     lista_de_patrones[1].pattern_size = 9;
     memcpy (lista_de_patrones[1].pattern," Knoppix ",9);
     memcpy (lista_de_patrones[1].nombre_virus,"vir_pat_2",9);
     
     /* prepara tercer patrón */
     lista_de_patrones[2].offset_start = 0;
     lista_de_patrones[2].pattern_size = 16;
     memcpy (lista_de_patrones[2].pattern,
         "\x7F\x45\x4c\x46\x01\x01\x01\x00\x00\x00\x00\x00",16);
     memcpy (lista_de_patrones[2].nombre_virus,"vir_pat_ls",10);
     
     /* establece número total de patrones*/
     num_patterns=3;
}

int revisaArchivo (char *nomarch)
{
   unsigned char filebuf [MAX_FILEBUF_SIZE];      
   int cont = 0;
   int cont2 = 0;
   int infectado;
   int bytesread;
   int result=0;	/*asume que no hay archivos infectados iunicialmente */
   FILE *fp;
   
   if ((fp=fopen(nomarch,"rb"))==NULL)
   {
      printf ("Error, no se puede abrir el archivo: %s\n",nomarch);
      return (0);
   }
   
   for (cont = 0; cont < num_patterns; cont++)
   {
      
      infectado=0;  /* asume que el archivo no está infectado hasta
                       demostrar lo contrario */
      for (cont2=0;cont2<MAX_FILEBUF_SIZE;cont2++)
      {
         /* limpia buffer */
         filebuf[cont2]='\0';
      }                 
      /* Si el offset del patrón es negativo, revisa todo el archivo */
      if ((lista_de_patrones[cont].offset_start) < 0) 
      {
         fseek (fp,0,SEEK_SET); /* apunta al inicio del archivo */
         bytesread= fread(filebuf,
                          sizeof(unsigned char),MAX_FILEBUF_SIZE,fp);
         /* busca el patrón de virus dentro del buffer */
         if (buscaPatron(lista_de_patrones[cont],filebuf))
         {
            infectado=1;
         }
         /* maneja bloques del archivo posteriores al primero*/
         while ( (!feof(fp))&&(!infectado)&&(bytesread!=0) )
         {
               /* retrocede (pattern_size-1) bytes para revisar empalme  
                  de bloques*/
            fseek (fp,(-1)*(lista_de_patrones[cont].pattern_size -1),
                   SEEK_CUR);
            fread (filebuf, sizeof(unsigned char), MAX_FILEBUF_SIZE, fp);
            if (buscaPatron((lista_de_patrones[cont]),filebuf))
            {
               infectado=1;
            }              
         }
      }      
      
      else    /* En caso contrario sólo revisa en el desplazamiento */
      {
         fseek (fp,lista_de_patrones[cont].offset_start,SEEK_SET);      
         fread (filebuf,sizeof(unsigned char),MAX_FILEBUF_SIZE,fp);
         if (buscaPatron((lista_de_patrones[cont]),filebuf))
         {
            infectado=1;
	      result=1;
         }
      }
      if (infectado)
      {
         printf ("[!] Archivo %s está infectado con VIRUS: %s \n",
                 nomarch,lista_de_patrones[cont].nombre_virus);
         infectados++;
      }
   }
   fclose (fp);
   return (result);
}

int revisaDirectorio (DIR *directorio, char *dirname)
{
   DIR *directorio_rec;
   struct dirent *direntry;
   char nomarch [200];
   int longitud;
   int result;
            /* Lee cada entrada en secuencia del directorio y 
               analiza los archivos */
   while ((direntry = readdir(directorio)) != NULL) 
   {
            /* Ignora dir. actual y anterior */
      if ((strcmp(direntry->d_name,".") &&  
           strcmp(direntry->d_name,"..")))
      {
         strcpy (nomarch, dirname);
         longitud = strlen(dirname);
         if (dirname[longitud-1] != '/')
         {
            strcat (nomarch, "/");
         }
         strcat (nomarch, direntry->d_name);
         if ((directorio_rec = opendir(nomarch)) == NULL) 
         {      
            /* Si no es un directorio, entonces es un archivo y lo 
               revisamos.*/            
            /* fprintf(stdout, "   Analizando: %s\n", nomarch);*/
            result=revisaArchivo(nomarch);
         }
         else
         {
            /* Si es un directorio, llama recursivamente a la función*/
            result = revisaDirectorio (directorio_rec,nomarch);         
         }
      }
   }
   return(result);
}

int main(int argc, char *argv[]) 
{
   DIR *dirp;
   char *dirname = argv[1];    /* Directorio para buscar archivos */
   int result = 0;
   if (argc!=2)
   {
      printf("Error, uso del programa: %s <directorio_de_inicio>\n",
             argv[0]);
      exit (1);
   }
   generaPatrones();    /* define cadenas de búsqueda de virus */
      /* Abre apuntador hacia estructura de directorio */
   if ((dirp = opendir(dirname)) == NULL) 
   {
      fprintf(stderr, "Error, no se puede abrir: %s\n", dirname);
      return (1);
   }
   result = revisaDirectorio (dirp,dirname);
   /* Cierra apuntador hactia estructura de directorio */
   closedir(dirp);
   if (infectados)
   {
      printf("\n\a[!] Se encontró al menos un archivo infectado.\n\n");
   }
   else
   {
      printf("\n NO se encontraron archivos infectados.\n\n");   
   }
   return (infectados);
}

