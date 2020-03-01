;HM_C.asm

global	main		;Declara p�blica la funci�n main.
	extern	printf	;Declara externa la funci�n printf (C).

	section .text
main:
	push	dword mensaje	;Pasa apuntador a mensaje como par�metro
	call	printf		;en pila y llama a printf.
	add	esp, 4		;Libera memoria (apuntador de par�metro).
	ret				;Sale del programa
mensaje:
	db	'Hola, mundo!',0xa,0   ;Cadena terminada en cero (printf)

