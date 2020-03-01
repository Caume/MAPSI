;EJCasm.asm
;Componente en ensamblador para ala aplicación EJCasm

section	.text
global ejemplo             ;Define como global la función para que pueda ser
                           ;vista desde el programa en C.
ejemplo:
f_ent:   push	ebp			; Guarda ebp anterior.
	 mov	ebp, esp		; Apunta ebp al contexto actual.

	 sub	esp, 8			; Reserva memoria de pila para 2 enteros (2x4)
	 mov	dword [ebp-4], 7	; b = 7
	 mov	dword [ebp-8], 10	; a = 10
         mov	eax, [ebp+8]		; eax = x (=1)
	 imul	eax, [ebp-4]	        ; eax = eax * b (1*7=7)
	 add	eax, [ebp+12]		; eax = eax + y (7+2=9)
	 add    eax, [ebp-8]            ; eax = eax + a (9+10=19)
	                                ; Resultado de función está en eax

f_sal:	 mov	esp, ebp		; Libera memoria de pila usada por función.
	 pop	ebp			; Restaura ebp anterior.
	 ret                            ; Regresa a la función main().

