; Calculate the length of a string.
global _start

section .data
test_string:  db  "abcdef", 0

section .text

strlen:
  ; By convention, the first and the only argument is taken from rdi
  xor rax, rax                    ; rax will hold string length; initialise 0

.loop:                            ; main loop starts here
  cmp byte [rdi+rax], 0           ; check if current symbol is null-terminator
                                  ; Need the 'byte' modifier since the left
                                  ; and right part of cmp should be the same
                                  ; size. Right operand is immediate and
                                  ; holds no information about its size, hence
                                  ; we don't know how many bytes should be
                                  ; taken from memory and compared to zero.
  je  .end                        ; Jump if we found null-terminator
  inc rax                         ; Else process next symbol & increment count
  jmp .loop

.end:
  ret                             ; return value rax = length of string.

_start:
  mov rdi, test_string
  call strlen                     ; return: rax = string length
  mov rdi, rax                    ; rdi = string length
                                  ; this will be the exit code
  mov rax, 60                     ; exit() syscall number
  syscall
