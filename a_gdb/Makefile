ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = print_rax_2 call_stack

CFLAGS = -std=c11 -ggdb -Wall

all:	$(PROGS)

%:	%.asm
	$(AS) $(ASFLAGS) $@.asm
	$(LD) $@.o -o $@

%: %.c
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
