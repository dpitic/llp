; Basic I/O library.

section .text

; Accepts a pointer in rdi to a null-terminated string and returns its length 
; in rax.
string_length:
  xor rax, rax                  ; initialise string length counter
.loop:
  cmp byte [rdi+rax], 0         ; check if reached null terminator
  je .end                       ; found null terminator
  inc rax                       ; increment string length counter
  jmp .loop                     ; else continue counting
.end:
  ret                           ; rax = string length

; Accepts a pointer in rdi to a null-terminated string and prints it to stdout.
print_string:
  push rdi                      ; save address of string
  call string_length            ; rax = length of string printed
  pop rsi                       ; address of string to print
  mov rdx, rax                  ; string length
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  syscall
  ret

; Accepts a character code directly as first argument in rdi and prints it to
; stdout.
print_char:
  push rdi                      ; save address of character
;  mov rdi, rsp
  call print_string             ; rax = length of string printed
  pop rdi
  ret

; Print a character with code 0xA.
print_newline:
  mov rdi, `\n`
  jmp print_char
  ret

; Output an unsigned 8 byte integer in rdi in decimal format.
print_uint:
  mov rax, rdi
  mov rdi, rsp
  push 0
  sub rsp, 16

  dec rdi
  mov r8, 10

.loop:
  xor rdx, rdx
  div r8
  or dl, 0x30
  dec rdi
  mov [rdi], dl
  test rax, rax
  jnz .loop

  call print_string

  add rsp, 24
  ret

; Output a signed 8 byte integer in rdi in decimal format.
print_int:
  test rdi, rdi
  jns print_uint
  push rdi
  mov rdi, '-'
  call print_char
  pop rdi
  neg rdi
  jmp print_uint
  ret

; Accepts two pointers to strings in rdi and rsi and compares them. Return 1 if
; they are equal, otherwiae 0 in rax.
string_equals:
  mov al, byte [rdi]
  cmp al, byte [rsi]
  jne .no
  inc rdi
  inc rsi
  test al, al
  jnz string_equals
  mov rax, 1                    ; strings are equal
  ret
  .no:
  xor rax, rax                  ; strings are not equal
  ret

; Read one character from stdin and return it. If the end of input stream
; occurs, return 0 in rax.
read_char:
  push 0                        ; read buffer on stack
  xor rax, rax                  ; read() syscall identifier = 0
  xor rdi, rdi                  ; stdin file descriptor = 0
  mov rsi, rsp                  ; address of read buffer on stack
  mov rdx, 1                    ; size of read buffer = 1 byte
  syscall
  pop rax                       ; read buffer
  ret                           ; rax = character read 

; Accepts a buffer address and size as arguments. Reads next word from stdin
; (skipping whitespaces into buffer). Stops and returns 0 if word is too big
; for the buffer specified; otherwise returns a buffer address.
read_word:
  push r14
  push r15
  xor r14, r14
  mov r15, rsi
  dec r15

  .A:
  push rdi
  call read_char
  pop rdi
  cmp al, ' '
  je .A                         ; skip space into buffer
  cmp al, 10
  je .A                         ; skip LF ('\n') into buffer
  cmp al, 13
  je .A                         ; skip CR ('\r') into buffer
  cmp al, 9
  je .A                         ; skip TAB ('\t') into buffer
  test al, al
  jz .C                         ; null terminator found

  .B:
  mov byte [rdi + r14], al
  inc r14

  push rdi
  call read_char
  pop rdi
  cmp al, ' '
  je .C                         ; skip space into buffer
  cmp al, 10
  je .C                         ; skip LF ('\n') into buffer
  cmp al, 13
  je .C                         ; skip CR ('\n') into buffer
  cmp al, 9
  je .C                         ; skip TAB ('\t') into buffer
  test al, al
  jz .C                         ; nul terminator found
  cmp r14, r15
  je .D

  jmp .B

  .C:
  mov byte [rdi + r14], 0
  mov rax, rdi

  mov rdx r14
  pop r15
  pop r14
  ret

  .D
  xor rax, rax
  pop r15
  pop r14
  ret

; Accepts a null-terminated string and tries to parse an unsigned number from
; its start.
; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
  mov r8, 10
  xor rax, rax                  ; initialise return number = 0
  xor rcx, rcx                  ; initialise return length = 0
.loop:
  movzx r9, byte [rdi + rcx]
  cmp r9b, '0'
  jb .end                       ; negative number found
  cmp r9b, '9'
  ja .end                       ; number greater than 9 found
  xor rdx, rdx
  mul r8
  and r9b, 0x0f
  add rax, r9
  inc rcx                       ; increment length counter
  jmp .loop
  .end:
  mov rdx, rcx                  ; rdx = length of string
  ret                           ; rax = number

; Accepts a null-terminated string and tries to parse a signed number from its
; start. Returns the number parsed in rax; its characters count in rdx
; including sign if any; otherwise zero is returned in rax. No spaces between 
; sign and digits are allowed.
; rdi points to a string
; returns rax: number, rdx : length
parse_int:
  mov al, byte [rdi]
  cmp al, '-'
  je .signed                    ; found signed (negative)
  jmp parse_uint
.signed:
  inc rdi                       ; next byte
  call parse_int
  neg rax
  test rdx, rdx
  jz .error

  inc rdx                       ; increment length counter
  ret 

  .error:
  xor rax, rax                  ; error: rax = 0
  ret

; Accepts a pointer to a string, pointer to a buffer, and buffer length. Copies
; string to destination. The destination address is returned if the string fits
; the buffer; otherwise zero is returned in rax.
; rdi = source
; rsi = dest
; rdx = dest length
string_copy:
  push rdi
  push rsi
  push rdx
  call string_length            ; rax = string length
  pop rdx
  pop rsi
  pop rdi

  cmp rax, rdx
  jae .too_long                 ; also need to store null terminator

  push rsi                      ; destination buffer

    .loop:
    mov dl, byte [rdi]
    mov byte [rsi], dl
    inc rdi
    inc rsi
    test dl, dl
    jnz .loop

  pop rax                       ; rax = destination address
  ret

  .too_long:
  xor rax, rax                  ; string too big for buffer, rax = 0
  ret
