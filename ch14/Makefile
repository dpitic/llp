ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = maximum maximum.s vararg volatile_ex printf_vuln

all:	$(PROGS)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

maximum.s:	maximum.c
	$(CC) $(CFLAGS) -S -masm=intel -fno-stack-protector $<

volatile_ex:	volatile_ex.c
	$(CC) $(CFLAGS) -O2 -S -masm=intel $<
	$(CC) $(CFLAGS) -O2 $< -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
