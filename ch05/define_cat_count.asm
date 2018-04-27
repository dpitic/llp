; This file is the input file used to demonstrate the operation of the nasm
; reprocess. The preprocessor is invoked with the -E command-line switch for
; nasm, which outputs the preprocessor results to stdout.

%define cat_count 42

  mov rax, cat_count
