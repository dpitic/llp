ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = float_reinterpret divisor is_fib

all:	$(PROGS)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
