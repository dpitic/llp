extern string_equals            ; defined in I/O library

section .rodata                 ; read only data
msg_noword: db "No such word", 0

section .text                   ; machine instructions

;;
;; @brief      Find given word in the dictionary.
;;
;; @details    This function accepts a pointer in rdi with the address of a
;;             null-terminated string representing the word key to find in the
;;             dictionary. It loops through the whole dictionary comparing the
;;             key word with each key in the dictionary.
;;
;; @param      rdi is pointer to null-terminated string for key word to find.
;;             rsi is pointer to last word
;;
;; @return     rax = 0 if word is not found; otherwise address of record.
;;
global find_word:function
find_word:
  xor rax, rax                  ; initialise return (0 = word not found)
.loop:
  test rsi, rsi                 ; check if ptr to last word is null
  jz .end
  push rdi                      ; save pointer to word to look for
  push rsi                      ; save pointer to last word
  add rsi, 8                    ; address of dictionary key
  call string_equals            ; rax = 1 if strings are equal, 0 otherwise
  pop rsi
  pop rdi
  test rax, rax
  jnz .found
  mov rsi, [rsi]
  jmp .loop
.found:
  mov rax, rsi                  ; address of dictionary key for word found
.end:
  ret                           ; word not found: rax = 0
