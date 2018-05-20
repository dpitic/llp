ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = sc_prod prime_chk

all:	$(PROGS)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
