ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = hello hello_proper_exit print_rax print_call endianness strlen \
				strlen_bug1

all:	$(PROGS)

%:	%.asm
	$(AS) $(ASFLAGS) $@.asm
	$(LD) $@.o -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
