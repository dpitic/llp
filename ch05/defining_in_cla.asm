; This code snippet demonstrates conditional assembly based on definition of a
; macro identifier, which can be passed to nasm through the -d command line
; flag. Assemble the file using:
;
;  $ nasm -E -dFLAG defining_in_cla.asm
;
; to include the conditional code block. Otherwise it won't be included.

%ifdef FLAG
hellostring: db "Hello", 0
%endif
