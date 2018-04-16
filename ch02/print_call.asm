; This program implements the hexadecimal print program using function calls

section .data

newline_char: db 10
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
  ret

; Function used to print the hexadecimal value
print_hex:
  mov rax, rdi

  mov rdi, 1
  mov rdx, 1
  mov rcx, 64                   ; amount used in shifting rax
iterate:
  push rax                      ; save initial state of rax
  sub rcx, 4
  sar rax, cl                   ; shift to 60, 56, 52, ... 4, 0
  and rax, 0xf                  ; clear all bits but the lowest four
  lea rsi, [codes + rax]        ; take a hexadecimal digit character code

  mov rax, 1                    ; write() syscall identifier

  push rcx                      ; syscall will break rcx
  syscall                       ; rax = 1 -- the write() identifier
                                ; rdi = 1 for stdout
                                ; rsi = address of a character
  pop rcx

  pop rax
  test rcx, rcx                 ; rcx == 0 when all digits are shown
  jnz iterate

  ret

_start:
  mov rdi, 0x1122334455667788
  call print_hex
  call print_newline

  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; exit(0) argument: 0
  syscall

