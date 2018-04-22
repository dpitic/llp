; This program demonstrates how to display a message on stdout using the write()
; system call. NOTE: this program will display the message on the terminal and
; subsequently crash, because program termination is not implemented.

global _start

; .data section is used for global variables.
section .data
; Labels are used to abstract out address values to make programs more readable.
; The db directive is used to create byte data.
message: db 'hello, world!', 10 ; 10 is new line ASCII code for LF ('\n')

; .text section is used for for program instructions.
section .text
_start:                         ; Entry point. First instruction to be executed.
  ; The write() system call writes a given amount of bytes from memory starting
  ; at the given address, to a file with the given file descriptor.
	mov		rax, 1                  ; system call number should be stored in rax
	mov		rdi, 1                  ; argument #1 in rdi: write file descriptor
	mov		rsi, message            ; argument #2 in rsi: start of string buffer
	mov		rdx, 14                 ; argument #3 in rdx: number bytes to write
	syscall                       ; invokes the system call
  ; There is nothing after the syscall to signify the end of the program. The
  ; next instruction pointed to by rip will be executed, which will most likely
  ; result in a segmentation fault causing the program to crash. Normally the
  ; exit() system call is used to cleanly terminate the program.
