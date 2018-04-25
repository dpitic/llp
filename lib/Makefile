#
# Makefile for I/O library
#
ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LIBLLP = libllp.a
PROGS = lib.inc

all:	$(LIBLLP)

$(LIBLLP):	libllp.o
	$(AR) rv $(LIBLLP) libllp.o
	$(RANLIB) $(LIBLLP)

libllp.o:	lib.inc
	$(AS) $(ASFLAGS) -o libllp.o lib.inc

clean:
	rm -f *.o a.out core temp.* $(LIBLLP)

.PHONOY:	clean
