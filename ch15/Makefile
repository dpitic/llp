ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# GCC linker flags
LDFLAGS = -Wl,-rpath=.
# GCC shared object flags
SOFLAGS = -fPIC -shared

PROGS = mainlib preload_launcher

all:	$(PROGS) prelib.so

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

mainlib:	mainlib.c dynlib.so
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

dynlib.so:	dynlib.c
	$(CC) $(CFLAGS) $(SOFLAGS) -o $@ $<

# Custom puts() shared object library
prelib.so:	prelib.c
	$(CC) $(CFLAGS) $(SOFLAGS) -o $@ $<

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.so

.PHONY:	clean
