ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = mappings_loop segfault_badaddr

all:	$(PROGS)

%:	%.asm
	$(AS) $(ASFLAGS) $@.asm
	$(LD) $@.o -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
