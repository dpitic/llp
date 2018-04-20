; This program implements the hexadecimal print program using function calls.
; It is used to demonstrate function call convention.

section .data

; newline_char: db 10             ; ASCII 10 is LF character '\n'
newline_char: db `\n`             ; alternative LF character
codes: db '0123456789abcdef'

section .text
global _start

; Function used to print a new line character.
print_newline:
  mov	rax, 1                    ; write() syscall identifier
  mov	rdi, 1                    ; stdout file descriptor
  mov rsi, newline_char         ; address of new line character
  mov rdx, 1                    ; number of bytes to write
  syscall
  ret                           ; print_newline

; Function used to print the hexadecimal value passed in through rdi
print_hex:
  mov rax, rdi                  ; rdi contains argument, save in rax

  mov rdi, 1                    ; stdout file descriptor
  mov rdx, 1                    ; number of bytes to write()
  mov rcx, 64                   ; amount used in shifting rax
iterate:
  push rax                      ; save initial state of rax
  sub rcx, 4
  sar rax, cl                   ; shift to 60, 56, 52, ... 4, 0
  and rax, 0xf                  ; clear all bits but the lowest four
  lea rsi, [codes + rax]        ; take a hexadecimal digit character code

  mov rax, 1                    ; write() syscall identifier

  push rcx                      ; syscall will modify rcx
  syscall                       ; rax = 1: the write() identifier
                                ; rdi = 1: stdout file descriptor
                                ; rdx = 1: number of bytes to write()
                                ; rsi = address of a character
  pop rcx
  pop rax
  test rcx, rcx                 ; rcx == 0 when all digits are shown
  jnz iterate
  ret                           ; print_hex

_start:
  mov rdi, 0x1122334455667788   ; 1st function argument for print_hex
  call print_hex
  call print_newline

  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; exit(0) argument: 0
  syscall
