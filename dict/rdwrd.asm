section .text
extern read_char                ; defined in I/O library

;;
;; @brief      Read next word from stdin.
;;
;; @details    Accepts a buffer address and reads the next word from stdin
;;             (skipping whitespaces) into buffer. This function is an
;;             alternative implementation for testing purposes.
;;
;; @param      rdi   Address of buffer used to store word read from stdin.
;;
;; @return     rax   0 if owrd is too big for buffer specified; otherwise
;;                   pointer to buffer address.
;;
global read_word_2:function
read_word_2:
  push r14                      ; buffer index (offset)
  xor r14, r14                  ; initialise buffer index

.A:                             ; read first character, skipping white spaces
  push rdi
  call read_char                ; rax = character read
  pop rdi

  cmp al, ' '
  je .A                         ; skip space
  cmp al, 10
  je .A                         ; skip LF ('\n')
  cmp al, 13
  je .A                         ; skip CR ('\r')
  cmp al, 9
  je .A                         ; skip TAB ('\t')

.B:                             ; read subsequent characters, not white space
  mov byte [rdi + r14], al
  inc r14

  push rdi
  call read_char
  pop rdi
  cmp al, ' '                   ; white space means end of word
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

  jmp .B                        ; continue reading next character

.C:                             ; end of word
  mov byte [rdi + r14], 0       ; add null terminator to buffer
  mov rax, rdi                  ; rax = address of string buffer

  pop r14
  ret
