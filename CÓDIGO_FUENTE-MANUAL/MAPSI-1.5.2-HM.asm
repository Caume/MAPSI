;HM.asm
;VERSIÓN PARA LINUX DE HOLA MUNDO EN NASM
section	.text
global _start			      ;debe declararse para enlazador (ld)
msg	db	'Hola, mundo!',0xa	;Cadena a imprimirse en pantalla
len	equ	$ - msg			;Longitud de la cadena
_start:					;Etiqueta que indica punto de entrada 
                                    ;al programa 
					      ;(declarada como global arriba)
	mov	edx,len		;carga longitud del mensaje
	mov	ecx,msg		;carga apuntador a mensaje
	mov	ebx,1			;carga descriptor de archive (stdout)
	mov	eax,4			;carga número de función (sys_write)
	int	0x80			;realiza llamada al kernel
	mov	eax,1			;carga Nuevo número de función (sys_exit)
	int	0x80			;realiza llamada al kernel
