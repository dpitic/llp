; This program displays the contents of the file 'test.txt' on the terminal.
; The implementation uses the mmap() system call to map the file into memory
; and then calls the print_string I/O library function to display the contents
; of that memory region on the terminal.

; From /usr/include/asm-generic/fcntl.h
%define O_RDONLY 0

; From /usr/include/asm-generic/mman-common.h
%define PROT_READ 0x1           ; page can be read
%define MAP_PRIVATE 0x02        ; Changes are private

section .data
fname: db 'test.txt', 0         ; File name of file to display

section .text
extern print_string             ; defined in external I/O library
;%include "lib.inc"              ; alternative using include file
global _start

_start:
  ; Open the file
  mov rax, 2                    ; open() syscall identifier
  mov rdi, fname                ; file name to open
  mov rsi, O_RDONLY             ; open in read only mode
  mov rdx, 0                    ; Irrelevant, not creating a file
  syscall                       ; rax = file descriptor

  ; Memory map the file
  mov r8, rax                   ; opened file descriptor
  mov rax, 9                    ; mmap() syscall identifier
  mov rdi, 0                    ; let OS choose starting address
  mov rsi, 4096                 ; use 4 KB page size
  mov rdx, PROT_READ            ; new memory region will be read only
  mov r10, MAP_PRIVATE          ; memory page will not be shared
  mov r9, 0                     ; offset in file (start at beginning)
  syscall                       ; rax points to newly allocated memory page

  ; Display the contents of the file from the memory map
  mov rdi, rax
  call print_string

  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; exit status = 0
  syscall
