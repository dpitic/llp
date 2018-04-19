; Basic I/O library.

section .text

; Accepts a pointer in rdi to a string and returns its length in rax.
string_length:
  xor rax, rax                  ; initialise string length counter
.loop:
  cmp byte [rdi+rax], 0         ; check if reached null terminator
  je .end                       ; found null terminator
  inc rax                       ; increment string length counter
  jmp .loop                     ; else continue counting
.end:
  ret                           ; rax = string length

print_string:
    xor rax, rax
    ret


print_char:
    xor rax, rax
    ret

print_newline:
    xor rax, rax
    ret


print_uint:
    xor rax, rax
    ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    ret 

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 


string_copy:
    ret
