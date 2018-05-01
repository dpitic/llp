; This launcher is used to test the dictionary function. It reads the input
; string in a buffer of maximum 255 characters, and tries to find this key in
; the dictionary. If found, it prints the corresponding value, otherwise it
; prints an error message.

section .text
%include "colon.inc"

extern read_word
extern find_word
extern print_newline
extern print_string
extern print_error
extern string_length
extern exit

global _start

section .rodata                 ; read only data
msg_noword: db "No such word", 0

%include "words.inc"

section .text                   ; machine instructions
_start:
  push rbp
  mov rbp, rsp
  sub rsp, 256                  ; string buffer + null terminator
  mov rdi, rsp                  ; rdi = address of string buffer to read
  call read_word                ; rax = address of buffer read
  mov rsi, lw                   ; address of word in dictionary
  call find_word                ; rax = address of record if found
  test rax, rax                 ; rax = 0 if not found
  jz .bad

  ; Found key word in dictionary
  add rax, 8                    ; rax now points to dictionary value
  push rax
  mov rax, [rsp]
  mov rdi, rax                  ; rax = address of dictionary value
  call string_length
  pop rdi
  add rdi, rax
  inc rdi                       ; address of dictionary value
  call print_string
  call print_newline
  mov rsp, rbp
  pop rbp
  mov rdi, 0                    ; exit status
  call exit

.bad:                           ; word not found in dictionary
  mov rdi, msg_noword
  call print_error
  call print_newline

  mov rsp, rbp
  pop rbp
  mov rdi, 0                    ; exit status
  call exit
