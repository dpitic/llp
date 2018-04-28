ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = 
MACRO_ARG = macro_arg_types

all:	$(PROGS) $(MACRO_ARG)

%:	%.asm
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@

macro_arg_types:	macro_arg_types.asm $(LIBLLP)
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@ $(LDLIBS)

.PHONY:	clean
clean:
	rm -f $(PROGS) $(MMAP) $(TEMPFILES) *.o
