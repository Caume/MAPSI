/*
    Ejemplo de aplicación vulnerable ante ataques de desbordamiento 
    de memoria
*/
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #define MYPORT 10001    // puerto de conexión
    #define MAXBUFLEN 400
    void imprime_contenido (char *buf)
    {
    	char print_buffer[200];
	   strcpy(print_buffer,buf);
      printf("contenido del paquete:\n");
	   printf(print_buffer);
    }
    
    int main(void)
    {
   	int sockfd;
      struct sockaddr_in my_addr;    // información de IP local
      struct sockaddr_in their_addr; // información de IP remota
      int addr_len, numbytes;
      char buf[MAXBUFLEN];
      while (1)
      {
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        my_addr.sin_family = AF_INET;         // host byte order
        my_addr.sin_port = htons(MYPORT);     // network byte order
        my_addr.sin_addr.s_addr = INADDR_ANY; // IP local
        memset(&(my_addr.sin_zero), '\0', 8); // borra lo demás

        if (bind(sockfd, (struct sockaddr *)&my_addr,
            sizeof(struct sockaddr)) == -1)
        {
            perror("bind");
            exit(1);
        }
        printf ("\n --- esperando conexión ---\n");
        addr_len = sizeof(struct sockaddr);
        if ((numbytes=recvfrom(sockfd,buf, MAXBUFLEN-1, 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1)
        {
            perror("recvfrom");
            exit(1);
        }

        printf("Programa cliente en dirección %s\n",
               inet_ntoa(their_addr.sin_addr));
        printf("La longitud del transferencia es de %d bytes\n",
               numbytes);
        buf[numbytes] = '\0';
        imprime_contenido(buf);
        close(sockfd);
      }
      return 0;
    }

