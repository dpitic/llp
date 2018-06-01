ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = div_cb

all:	$(PROGS) stack.o

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

stack.o:	stack.c stack.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
