; This code snippet demonstrates a loader fragment from Pure64 open source OS.
; It is executed before the operating system.

  align 16                      ; Ensures that the next command or data element
                                ; is stored starting at an address divisible by
                                ; 16 (even if some bytes are skipped).

  ; The following will be copied to GDTR via LGDTR instruction:

GDTR64:                         ; Global Descriptor Table Register
  dw gdt64_end - gdt64 - 1      ; limit of GDT (size minus one)
  dq 0x0000000000001000         ; linear address of GDT

  ; This structure is copied to 0x0000000000001000
gdt64:
  SYS64_NULL_SEL equ $-gdt64    ; Null segment
  dq 0x0000000000000000
  ; Code segment, read/exec, nonconforming
  SYS64_CODE_SEL equ $-gdt64
  dq 0x0020980000000000         ; 0x00209A0000000000
  ; Data segment, read/write, expand down
  SYS64_DATA_SEL equ $-gdt64
  dq 0x0000900000000000         ; 0x0020920000000000
gdt64_end:

  ; Dollar sign denotes the current memory address, so $-gdt64 means an offset
  ; from 'gdt64' label in bytes.
