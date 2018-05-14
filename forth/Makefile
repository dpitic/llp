ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

all:	forthress

pp:	forthress.pp.asm

forthress:	forthress.o $(LIBLLP)
	$(LD) $@.o -o $@ $(LDLIBS)

forthress.o:	forthress.asm macro.inc words.inc
	$(AS) $(ASFLAGS) $<

forthress.pp.asm:	forthress.asm macro.inc words.inc
	$(AS) $(ASFLAGS) $< -E -o $@

clean:
	rm -f forthress forthress.pp.asm $(TEMPFILES) *.o

.PHONY:	clean
