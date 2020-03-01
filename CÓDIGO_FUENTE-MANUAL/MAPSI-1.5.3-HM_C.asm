;HM_C.asm

global	main		;Declara pública la función main.
	extern	printf	;Declara externa la función printf (C).

	section .text
main:
	push	dword mensaje	;Pasa apuntador a mensaje como parámetro
	call	printf		;en pila y llama a printf.
	add	esp, 4		;Libera memoria (apuntador de parámetro).
	ret				;Sale del programa
mensaje:
	db	'Hola, mundo!',0xa,0   ;Cadena terminada en cero (printf)

