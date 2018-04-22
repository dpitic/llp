; Snippet to demonstrate some jumps.

  mov		rax, -1
  mov		rdx, 2

  cmp		rax, rdx
  jg		location                ; comparison for signed numbers
  ja		location                ; different logic: comparison for unsigned

  cmp		rax, rdx
  je		location                ; if rax equals rdx
  jne		location                ; if rax is not equal to rdx
