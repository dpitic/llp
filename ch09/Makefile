ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = sc_prod prime_chk union_example c_inclusion c_overload_11

all:	$(PROGS)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
