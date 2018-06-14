ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# GCC linker flags
LDFLAGS = -Wl,-rpath=.,-I/lib64/ld-linux-x86-64.so.2
# GCC shared object flags
SOFLAGS = -fpic -shared

PROGS = stack_unwind_main tail_rec_example_list prefetch_binsearch simd_main

all:	$(PROGS)

#-------------------------------------------------------------------------------
stack_unwind_main:	stack_unwind_main.o stack_unwind.so
	$(CC) $(LDFLAGS) -o $@ $?

stack_unwind_main.o:	stack_unwind_main.c
	$(CC) $(CFLAGS) -c -O0 -o $@ $<

stack_unwind.so:	stack_unwind.asm
	$(AS) $(ASFLAGS) $<
	$(CC) $(SOFLAGS) -o $@ stack_unwind.o
#-------------------------------------------------------------------------------
tail_rec_example_list:	tail_rec_example_list.c
	$(CC) $(CFLAGS) -Os -o $@ $<
#-------------------------------------------------------------------------------
prefetch_binsearch: prefetch_binsearch.c
	$(CC) $(CFLAGS) -O3 -o $@ $<
#-------------------------------------------------------------------------------
simd_main:	simd_main.c simd_sse.o
	$(CC) $(CFLAGS) -o $@ $?

simd_sse.o:	simd_sse.asm
	$(AS) $(ASFLAGS) $<
#-------------------------------------------------------------------------------
clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.so *.objdump

.PHONY:	clean
