#
# Makefile for I/O library
#
ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LIBLLP = libllp.a
PROGS = libllp
OBJS = ${PROGS:=.o}

all:	$(LIBLLP)

$(LIBLLP):	$(OBJS)
	$(AR) rv $(LIBLLP) $?
	$(RANLIB) $(LIBLLP)

%.o:	%.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f *.o a.out core temp.* $(LIBLLP)

.PHONOY:	clean
