ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = hello hello_proper_exit print_rax print_call

all:	$(PROGS)

%:	%.asm
	$(ASM) $(ASM_FLAGS) $@.asm
	$(LD) $@.o -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
