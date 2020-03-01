/*
	Manual de Actividades - Lecciones de Seguridad en C�mputo
	simple_nIDS - detector de intrusos de red primitivo, (c) 2005 por Omar
	Herrera
 */

#include <stdio.h>
#include <unistd.h>
#include <pcap.h>
#include <signal.h>

#define dispRed			"eth0"		// dispositivo de red para captura
#define CAPTURABYTES 	65000 		// N�m. m�x. de bytes por paquete
#define PROMISCUO 		1				// Activa modo promiscuo
#define TIMEOUT 			500 			// Timeout (es ignorado en Linux)

int loop;

// --- Rutina que maneja se�ales SIGINT (CTRL+C), con esto cambiamos una
// 	 bandera que indica que debe finalizar el ciclo de captura.
void cleanup (int signo)
{
	loop = 0;
	printf ("Se�al de interrupci�n detectada...espere un momento\n");
}

// --- Programa principal
int main (int argc, char **argv)
{
	u_int cont,cont2,cont3,encontrado;  	// Contadores y banderas
	char *patronBusqueda;						// Apuntador al patr�n de b�squeda
	pcap_t *pcapDesc; 							// Descriptor pcap
	u_char *paquete;								// Apuntador a paquete de red
	struct pcap_pkthdr pcapPkthdr;			// Estructura de encabezado de paquete
	struct pcap_stat pcapStat; 				// Estructura de estad�sticas pcap
	struct sigaction action;					// Estructura para manejo de se�ales
	char errBuff [PCAP_ERRBUF_SIZE]; 		// B�ffer de errores pcap
	char ipSrc [17];								// Estructuras para direcciones IP
	char ipDst [17];								// (en texto:  xxx.xxx.xxx.xxx)
		
	loop = 1;						// Bandera de ciclo de captura
	patronBusqueda = NULL;
	
	// --- Procesa par�metros de l�nea de comando
	while ((cont = getopt (argc,argv, "p:")) != EOF)
	{
		switch (cont)
		{
			case 'p':
				patronBusqueda = optarg;
				break;
			default:
				break;
		}
	}
	
	if (patronBusqueda == NULL)	// Error si no hay par�metro -p
	{
		printf ("ERROR: falta par�metro -p <patr�n de b�squeda>\n");
		exit (1);
	}
	else
	{
		printf ("Iniciando simple_nIDS con patr�n de b�squeda:\n %s \n",
		patronBusqueda);
	}
	
	// --- Activa descriptor para captura de paquetes
	pcapDesc = pcap_open_live (dispRed, CAPTURABYTES, PROMISCUO, TIMEOUT,
				  errBuff);  
	if (pcapDesc == NULL)
	{
		printf ("Error en pcap_open_live: %s",errBuff);
		exit (1);
	}
	
	// --- Activa manejador de SIGINT (CTRL+C)
	action.sa_handler = cleanup;
	sigemptyset (&action.sa_mask);
	action.sa_flags=0;
	if (sigaction (SIGINT,&action, NULL) == -1)
	{
		printf ("Error: no se puede instalar manejador de interrupci�n\n");
	}
	
	// --- Ciclo de captura de paquetes y b�squeda de patrones
	while (loop == 1) 	
	{	
		// --- Captura el siguiente paquete y guarda su contenido.
		paquete = (u_char *)pcap_next (pcapDesc, &pcapPkthdr);		
		cont = 0;
		encontrado = 0;
		
		// --- Ciclo para buscar el patr�n en el la estructura 'paquete' 
		if (paquete != NULL)
		{
			while (cont < (pcapPkthdr.caplen - strlen(patronBusqueda)))
			{
				// --- Busca coincidencia de primer elemento
				if ( (char)paquete[cont] == (char) patronBusqueda[0])
				{
					cont2 = cont+1;
					cont3 = 1;

					// --- Valida que todo el patr�n est� en esta ubicaci�n
					while (cont3 <= strlen(patronBusqueda))
					{
						if ((char)paquete[cont2] == (char)patronBusqueda[cont3])
						{
							cont2++;
							cont3++;
						}
						else 
						{
							break;
						}
					} 
					if (cont3 >= strlen(patronBusqueda))
					{
						encontrado = 1;	// Indica que se ha encontrado el patr�n.
					}				
				}

				// --- Imprime alerta con ip.origen->ip.destino de los paquetes
				//     que contienen el patr�n.
				if (encontrado == 1)
				{
					sprintf (ipSrc,"%d.%d.%d.%d",(paquete[26]&255),
							  (paquete[27]&255),(paquete[28]&255),(paquete[29]&255));
					sprintf (ipDst,"%d.%d.%d.%d",(paquete[30]&255),
							  (paquete[31]&255),(paquete[32]&255),(paquete[33]&255));			
					printf ("*** Alerta, patr�n detectado ***\n");
					printf (" %s -> %s\n\n",ipSrc,ipDst);
					break;
				}
				else
				{
					cont++;
				}
			}
		}
		
	}
   	
	// --- Imprime estad�sticas al terminar el ciclo de captura (CTRL+C)
	if (pcap_stats(pcapDesc, &pcapStat) != -1)
	{
		printf ("Paquetes recibidos: \t%6d\n"
				  "Paquetes descartados: \t%6d\n",pcapStat.ps_recv, pcapStat.ps_drop);
	}
	pcap_close(pcapDesc);
	printf ("Cerrando captura...programa finalizado \n"); 
	exit (0);
}
