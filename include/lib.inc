; Basic I/O library.

section .text

;;
;; @brief      Accepts a pointer in rdi to a null-terminated string and returns
;;             its length in rax.
;;
;; @param      rdi   Pointer to a null-terminated string.
;;
;; @return     rax   Length of the string.
;;
string_length:
  xor rax, rax                  ; initialise string length counter
.loop:
  cmp byte [rdi + rax], 0       ; check if reached null terminator
  je .end                       ; found null terminator
  inc rax                       ; increment string length counter
  jmp .loop                     ; else continue counting
.end:
  ret                           ; rax = string length

;;
;; @brief      Accepts a pointer in rdi to a null-terminated string and prints
;;             it to stdout.
;;
;; @param      rdi   Pointer to a null-terminated string.
;;
print_string:
  push rdi                      ; save address of string
  call string_length            ; rax = length of string
  pop rsi                       ; address of string to print
  mov rdx, rax                  ; string length
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  syscall
  ret

;;
;; @brief      Accepts a character code directly as the first argument in rdi
;;             and prints it to stdout.
;;
;; @param      rdi   Character code to print.
;;
print_char:
  push rdi                      ; save address of character
;  mov rdi, rsp
  call print_string             ; rax = length of string printed
  pop rdi
  ret

;;
;; @brief      Print a newline character (ASCII code 0xA).
;;
print_newline:
  mov rdi, `\n`
  jmp print_char

;;
;; @brief      Output an unsigned 8 byte integer in decimal format.
;;
;; @param      rdi   Unsigned 8 byte integer to print.
;;
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

;;
;; @brief      Output a signed 8 byte integer in rdi in decimal format.
;;
;; @param      rdi   Signed 8 byte integer to output.
;;
print_int:
  test rdi, rdi
  jns print_uint
  push rdi
  mov rdi, '-'
  call print_char
  pop rdi
  neg rdi
  jmp print_uint

;;
;; @brief      Accepts two pointers to strings in rdi and rsi and compares them.
;;
;; @details    This function compares strings by performing byte-by-byte
;;             comparison.
;;
;; @param      rdi   Pointer to 1st null-terminated string.
;; @param      rsi   Pointer to 2nd null-terminated string.
;;
;; @return     rax   1 if the strings are equal; otherwise 0.
;;
string_equals:
  mov al, byte [rdi]
  cmp al, byte [rsi]
  jne .no
  inc rdi
  inc rsi
  test al, al                   ; check if reached null terminator
  jnz string_equals             ; not reached end of strings
  mov rax, 1                    ; strings are equal
  ret                           ; rax = 1
  .no:
  xor rax, rax                  ; strings are not equal
  ret                           ; rax = 0

;;
;; @brief      Read one character from stdin and return it. If the end of input
;;             stream occurs, return 0 in rax.
;;
;; @details    This function uses the stack to allocate memory for the read
;;             buffer.
;;
;; @return     rax   Character read from stdin; 0 on EOF.
;;
read_char:
  push 0                        ; read buffer on stack
  xor rax, rax                  ; read() syscall identifier = 0
  xor rdi, rdi                  ; stdin file descriptor = 0
  mov rsi, rsp                  ; address of read buffer on stack
  mov rdx, 1                    ; size of read buffer = 1 byte
  syscall
  pop rax                       ; read buffer
  ret                           ; rax = character read 

;;
;; @brief      Read next word from stdin.
;;
;; @details    Accepts a buffer address and size as arguments, and reads the
;;             next word from stdin (skipping whitespaces) into buffer.
;;
;; @param      rsi   Address of buffer used to store word read from stdin.
;;
;; @return     0 if word is too big for buffer specified; otherwise returns a
;;             buffer address.
;;
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
  je .A                         ; skip space
  cmp al, 10
  je .A                         ; skip LF ('\n')
  cmp al, 13
  je .A                         ; skip CR ('\r')
  cmp al, 9
  je .A                         ; skip TAB ('\t')
  test al, al
  jz .C                         ; null terminator found

  .B:
  mov byte [rdi + r14], al
  inc r14

  push rdi
  call read_char
  pop rdi
  cmp al, ' '
  je .C                         ; skip space
  cmp al, 10
  je .C                         ; skip LF ('\n')
  cmp al, 13
  je .C                         ; skip CR ('\n')
  cmp al, 9
  je .C                         ; skip TAB ('\t')
  test al, al
  jz .C                         ; null terminator found
  cmp r14, r15
  je .D

  jmp .B

  .C:
  mov byte [rdi + r14], 0
  mov rax, rdi

  mov rdx, r14
  pop r15
  pop r14
  ret

  .D:
  xor rax, rax
  pop r15
  pop r14
  ret

;;
;; @brief      Accepts a null-terminated string and tries to parse an unsigned
;;             number from its start.
;;
;; @param      rdi   Pointer to null-terminated string.
;;
;; @return     rax   Parsed number. Length in rdx.
;;
parse_uint:
  mov r8, 10
  xor rax, rax                  ; initialise return number = 0
  xor rcx, rcx                  ; initialise string offset = 0
.loop:
  movzx r9, byte [rdi + rcx]
  cmp r9b, '0'
  jb .end                       ; negative number found: rax = 0, rcx = 0
  cmp r9b, '9'
  ja .end                       ; number greater than 9 found: rax = 0, rcx = 0
  xor rdx, rdx                  ; initialise string length length = 0
  mul r8
  and r9b, 0x0f
  add rax, r9
  inc rcx                       ; increment string offset
  jmp .loop
  .end:
  mov rdx, rcx                  ; rdx = length of string
  ret                           ; rax = number

;;
;; @brief      Accepts a null-terminated string and tries to parse a signed
;;             number from its start. No spaces between sign and digits are
;;             allowed.
;;
;; @param      rdi   Pointer to string.
;;
;; @return     rax   Number parsed. Length of string in rdx, including sign. 0
;;             otherwise in rax.
;;
parse_int:
  mov al, byte [rdi]
  cmp al, '-'
  je .signed                    ; found signed number (negative)
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

;;
;; @brief      Copy string to destination buffer.
;;
;; @details    Accepts a pointer to a string, pointer to a buffer, and buffer
;;             length. Copies string to destination. Destination address is
;;             returned if the string fits the buffer; otherwise zero is
;;             returned in rax.
;;
;; @param      rdi   Pointer to source string.
;; @param      rsi   Pointer to destination buffer.
;; @param      rdx   Destination buffer length.
;;
;; @return     Destination address is returned in rax if the string fits the
;;             buffer; orthewise return 0 in rax.
;;
string_copy:
  push rdi                      ; pointer to source string
  push rsi                      ; pointer to destination buffer
  push rdx                      ; destination buffer length
  call string_length            ; return: rax = string length
  pop rdx
  pop rsi
  pop rdi

  cmp rax, rdx                  ; check if destination buffer is big enough
  jae .too_long                 ; buffer needs to be length + 1 for null

  push rsi                      ; destination buffer address

    .loop:                      ; string copy loop
    mov dl, byte [rdi]          ; copy byte from source string
    mov byte [rsi], dl          ; into destination buffer
    inc rdi                     ; increment source string index
    inc rsi                     ; increment destination buffer index
    test dl, dl                 ; check if null terminator found
    jnz .loop

  pop rax                       ; rax = destination buffer address
  ret

  .too_long:
  xor rax, rax                  ; string too big for buffer, rax = 0
  ret
