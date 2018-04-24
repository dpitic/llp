; This code snippet demonstrated how protected mode can be activated (assuming
; start32 is a label on 32 bit code start).

  ; The processor always starts in real mode.
  ; To enter protected more, have to create GDT and set up gdtr.
  ; Set a special bit in cr0.
  ; Make a far jump (segment or segment selector is explicitly given).

  lgdt cs:[_gdtr]               ; load global descriptor table register GDTR

  mov eax, cr0                  ; !! Privileged instruction
  or al, 1                      ; this bit is responsible for protected mode
  mov rc0, eax                  ; !! Privileged instruction

  jmp (0x1 << 3):start32        ; assign first segment selector to cs

  align 16
_gdtr:                          ; stores GDT's last entry index + GDT address
  dw 47
  dq _gdt

  align 16

  ; Global Descriptor Table (GDT)
_gdt:
  ; Null descriptor (should be present in any GDT)
  dd 0x00, 0x00
  ; x32 code descriptor
  db 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x9A, 0xCF,      0x00 ; differ by exec bit
  ; x32 data descriptor
  db 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x92, 0xCF,      0x00 ; execution off (0x92)
  ;  size  size  base  base  base  util  util|size  base

