ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

MAIN = test_dict

all:	$(MAIN) $(LIBLLP)

test_dict:	test_dict.o dict.o
	$(LD) -o $@ $^ $(LDLIBS)

test_dict.o:	test_dict.asm colon.inc words.inc
	$(AS) $(ASFLAGS) $<

dict.o:	dict.asm
	$(AS) $(ASFLAGS) $<

.PHONY:	clean
clean:
	rm -f $(MAIN) $(TEMPFILES) *.o
