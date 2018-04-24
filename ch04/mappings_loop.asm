; This program enters an infinite loop and will be used to investigate its
; memory layout while it is running.
; Run this program in the background:
;   $ ./mappings_loop &
; The file /proc/PID/maps shows the memory map for the process with ID PID.
;   $ cat /proc/PID/maps

section .data
correct: dq -1

section .text
global _start

_start:
  jmp _start
