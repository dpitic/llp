ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = mappings_loop segfault_badaddr
MMAP = mmap

all:	$(PROGS) $(MMAP)

%:	%.asm
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@

mmap:	mmap.asm $(LIBLLP)
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@ $(LDLIBS)

.PHONY:	clean
clean:
	rm -f $(PROGS) $(MMAP) $(TEMPFILES) *.o
