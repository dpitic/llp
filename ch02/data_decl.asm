section .data
	example1: db 5, 16, 8, 4, 2, 1		; data bytes (1 byte = 8 bits)
	example2: times 999 db 42			; repeat cmd n times
	example3: dw 999					; data word (2 bytes = 16 bits)
										; dd = double word (4 bytes = 32 bits)
										; dq = quad word (8 bytes = 64 bits)