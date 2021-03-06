; Basic I/O library implementation.

section .text

;;
;; @brief      Accepts a pointer in rdi to a null-terminated string and returns
;;             its length in rax.
;;
;; @param      rdi   Pointer to a null-terminated string.
;;
;; @return     rax   Length of the string.
;;
global string_length:function
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
global print_string:function
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
;; @brief      Write string to stderr.
;;
;; @details    Accepts a pointer in rdi to a null-terminated error string and
;;             writes it to stderr.
;;
;; @param      rdi is pointer to null-terminated error string.
;;
global print_error:function
print_error:
  push rdi                      ; save address of string
  call string_length            ; rax = length of string
  pop rsi                       ; address of string to print
  mov rdx, rax                  ; string length
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 2                    ; stderr file descriptor
  syscall
  ret

;;
;; @brief      Accepts a character code directly as the first argument in rdi
;;             and prints it to stdout.
;;
;; @param      rdi   Character code to print.
;;
global print_char:function
print_char:
  push rdi                      ; save address of character
  mov rdi, rsp
  call print_string             ; rax = length of string printed
  pop rdi
  ret

;;
;; @brief      Print a newline character (ASCII code 0xA).
;;
global print_newline:function
print_newline:
  mov rdi, `\n`                 ; ASCII 10
  jmp print_char

;;
;; @brief      Output an unsigned 8 byte integer in decimal format.
;;
;; @param      rdi   Unsigned 8 byte integer to print.
;;
global print_uint:function
print_uint:
  mov rax, rdi
  mov rdi, rsp
  push 0
  sub rsp, 16                   ; allocate 16 bytes on the stack

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
global print_int:function
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
global string_equals:function
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
;; @return     rax   Character read; 0 on EOF.
;;
global read_char:function
read_char:
  push 0                        ; read buffer on stack
  xor rax, rax                  ; read() syscall identifier = 0
  xor rdi, rdi                  ; stdin file descriptor = 0
  mov rsi, rsp                  ; address of read buffer on stack
  mov rdx, 1                    ; size of read buffer = 1 byte
  syscall
  pop rax                       ; 0 for EOF or character read
  ret                           ; rax = character read or 0 for EOF

;;
;; @brief      Read next word from stdin.
;;
;; @details    Accepts a buffer address and size as arguments, and reads the
;;             next word from stdin (skipping whitespaces) into buffer.
;;
;; @param      rdi   Address of buffer used to store word read from stdin.
;;             rsi   Size of read buffer.
;;
;; @return     rax   0 if word is too big for buffer specified; otherwise
;;                   pointer to buffer address.
;;             rdx   Length of word (bytes).
;;
global read_word:function
read_word:
  push r14                      ; buffer index (offset)
  push r15                      ; max. string length
  xor r14, r14                  ; initialise index in buffer
  mov r15, rsi                  ; r15 = size of read buffer
  dec r15                       ; allow for null terminator

.A:                             ; read first character, skipping white spaces
  push rdi
  call read_char                ; rax = character read from stdin
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

.B:                             ; read subsequent characters, not white space
  mov byte [rdi + r14], al
  inc r14                       ; increment index in buffer

  push rdi
  call read_char                ; rax = character read from stdin
  pop rdi
  cmp al, ' '                   ; any white space character == end of word
  je .C                         ; found space at end of word
  cmp al, 10
  je .C                         ; found LF ('\n') at end of word
  cmp al, 13
  je .C                         ; found CR ('\r') at end of word
  cmp al, 9
  je .C                         ; found TAB ('\t') at end of word
  test al, al
  jz .C                         ; null terminator found
  cmp r14, r15                  ; check if buffer is full
  je .D

  jmp .B                        ; read next character

.C:                             ; end of word string, null or white space found
  mov byte [rdi + r14], 0       ; null terminate buffer
  mov rax, rdi                  ; pointer to buffer

  mov rdx, r14                  ; rdx = length of word (bytes)
  pop r15
  pop r14
  ret                           ; rax = pointer to buffer read

.D:                             ; buffer is full
  xor rax, rax                  ; string is too long for buffer, rax == 0
  pop r15
  pop r14
  ret                           ; rax == 0, string too long for buffer

;;
;; @brief      Read next word from stdin.
;;
;; @details    Read word from stdin (skipping whitespaces) into buffer of fixed
;;             size 254 bytes. This is an alternative and simplified
;;             implementation of read_word function.
;;
;; @param      rdi   Address of buffer used to store word read from stdin.
;;
;; @return     rax   Pointer to buffer address.
;;             rdx   Length of word (bytes).
;;
global read_word_fb:function
read_word_fb:
  push r14                      ; buffer index (offset)
  xor r14, r14                  ; initialise index in buffer

.A:                             ; read first character, skipping white spaces
  push rdi
  call read_char                ; rax = character read from stdin
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

.B:                             ; read subsequent characters, not white space
  mov byte [rdi + r14], al
  inc r14                       ; increment index in buffer

  push rdi
  call read_char                ; rax = character read from stdin
  pop rdi
  cmp al, ' '                   ; any white space character == end of word
  je .C                         ; found space at end of word
  cmp al, 10
  je .C                         ; found LF ('\n') at end of word
  cmp al, 13
  je .C                         ; found CR ('\r') at end of word
  cmp al, 9
  je .C                         ; found TAB ('\t') at end of word
  test al, al
  jz .C                         ; null terminator found
  cmp r14, 254                  ; check if buffer is full
  je .C

  jmp .B                        ; read next character

.C:                             ; end of word string, null or white space found
  mov byte [rdi + r14], 0       ; null terminate buffer
  mov rax, rdi                  ; pointer to buffer

  mov rdx, r14                  ; rdx = length of word (bytes)
  pop r14
  ret                           ; rax = pointer to buffer read

;;
;; @brief      Accepts a null-terminated string and tries to parse an unsigned
;;             number from its start.
;;
;; @param      rdi   Pointer to null-terminated string.
;;
;; @return     rax   Parsed number. Length in rdx.
;;
global parse_uint:function
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
;; @param      rdi   Pointer to null-terminated string.
;;
;; @return     rax   Number parsed on success, otherwise 0.
;;             rdx   Length of string, including sign.
;;
global parse_int:function
parse_int:
  mov al, byte [rdi]            ; read first string byte to see if negative
  cmp al, '-'
  je .signed                    ; found signed number (negative)
  jmp parse_uint                ; not signed number
.signed:
  inc rdi                       ; next byte
  call parse_uint               ; just parse as unsigned number
  neg rax
  test rdx, rdx
  jz .error

  inc rdx                       ; increment length counter
  ret                           ; rax = number

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
global string_copy:function
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

.loop:                          ; string copy loop
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

;;
;; @brief      Copy string to destination buffer.
;;
;; @details    Copy source string to destination buffer.
;;
;; @param      rdi   Pointer to source string.
;; @param      rsi   Pointer to destination buffer.
;;
global str_cpy:function
str_cpy:
  mov dl, byte [rdi]            ; copy byte from source string
  mov byte [rsi], dl            ; into destination buffer
  inc rdi                       ; increment source string index
  inc rsi                       ; increment destination buffer index
  test dl, dl                   ; check if null terminator found
  jnz str_cpy
  ret

;;
;; @brief      Exit process.
;;
;; @details    Accept exit status in rdi and calls exit() system call to
;;             terminate the process.
;;
;; @param      rdi contains the exit status passed to exit() system call.
;;
;; @return     rdi contains the exit status returned to the calling process.
;;
global exit:function
exit:
  mov rax, 60                   ; exit() syscall identifier
  syscall
