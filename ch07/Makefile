ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =
ITC = itc

all:	$(PROGS) $(ITC)

$(ITC):	itc.asm $(LIBLLP)
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@ $(LDLIBS)

.PHONY:	clean
clean:
	rm -f $(PROGS) $(ITC) $(TEMPFILES) *.o *.so

# This include file enables building the target and I/O library dependency from
# inside the source directory.
include $(ROOT)/Make.libllp.inc
