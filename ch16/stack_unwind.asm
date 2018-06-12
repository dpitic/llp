;; This code provides the implementation of the unwind() function called from
;; the main program.

extern printf
extern fptr                     ; pointer to local variable in main
global unwind                   ; exported function

section .rodata
format: db "%x ", 10, 0

section .code
unwind:
  push rbx

  ; while (rbx > fptr) {
  ;   print rbx;
  ;   rbx = [rbx]
  ; }
  mov rbx, rbp
.loop:
  cmp rbx, [rel fptr wrt ..got] ; check if pointing fptr or lower
  jc .end
  mov rdi, format
  mov rsi, rbx
  call printf wrt ..plt
  mov rbx, [rbx]
  jmp .loop
.end:
  pop rbx
  ret
