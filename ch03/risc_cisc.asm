; This code snippet shows effects of writing data into various registers.

  mov rax, 0x1111222233334444   ; rax = 0x1111222233334444
  mov eax, 0x55556666           ; rax = 0x0000000055556666
                                ; writing 32 bit part fills upper half of wide
                                ; register with zero bits.

  mov rax, 0x1111222233334444   ; rax = 0x1111222233334444
  mov ax, 0x7777                ; rax = 0x1111222233337777
                                ; writing 8 or 16 bit part leaves the rest of
                                ; the bits intact.

  mov rax, 0x1111222233334444   ; rax = 0x1111222233334444
  xor eax, eax                  ; rax = 0x0000000000000000
                                ; writing 32 bit part leaves the rest of
                                ; the bits intact.
