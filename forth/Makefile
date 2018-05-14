ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

all:	forthress

forthress:	forthress.o $(LIBLLP)
	$(LD) $@.o -o $@ $(LDLIBS)

forthress.o:	forthress.asm macro.inc words.inc
	$(AS) $(ASFLAGS) $<

clean:
	rm -f forthress $(TEMPFILES) *.o

.PHONY:	clean
