; This code snippet demonstrates the difference between lea and mov
; lea means load effective address. It enables the calculation of an address of
; a memory cell to be stored somewhere.

; rsi <- contents (value) stored in rax
mov	rsi, rax

; Square brackets denotes indirect addressing; the address is written inside
; the brackets.
; rsi <- memory contents starting at address stored in rax
mov	rsi, [rax]

; rsi <- address of label 'codes', a number
mov	rsi, codes

; rsi <- memory contents starting at 'codes' address
; 8 consecutive bytes are taken because rsi is 8 bytes long
; [identifier] dereferences the pointer identifier
mov	rsi, [codes]

; rsi <- address of 'codes'
; in this case it is equivalent to mov rsi, codes
; in general the address can contain several components
lea	rsi, [codes]

; rsi <- memory contents starting at address (codes + rax)
mov	rsi, [codes + rax]

; rsi <- address of (codes + rax)
; equivalent of combination:
; 	mov rsi, codes
; 	add rsi, rax
; Can't do it with a signle mov
lea	rsi, [codes + rax]
