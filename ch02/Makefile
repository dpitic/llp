ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = hello hello_proper_exit

all:	$(PROGS)

%:	%.asm
	$(NASM) $(ASM_FLAGS) $@.asm
	$(LD) $@.o -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
