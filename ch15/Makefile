ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# GCC linker flags
LDFLAGS = -Wl,-rpath=.
# GCC shared object flags
SOFLAGS = -fPIC -shared

PROGS = mainlib preload_launcher ex1-main ex2-main ex3-main ex4-main

all:	$(PROGS) prelib.so

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@
#-------------------------------------------------------------------------------
mainlib:	mainlib.c dynlib.so
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

dynlib.so:	dynlib.c
	$(CC) $(CFLAGS) $(SOFLAGS) -o $@ $<
#-------------------------------------------------------------------------------
# Custom puts() shared object library
prelib.so:	prelib.c
	$(CC) $(CFLAGS) $(SOFLAGS) -o $@ $<
#-------------------------------------------------------------------------------
# Dynamic library example in assembly
ex1-main:	ex1-main.o ex1-lib.so
	$(LD) -rpath=. -I/lib64/ld-linux-x86-64.so.2 -o $@ $?

ex1-lib.so:	ex1-lib.asm
	$(AS) $(ASFLAGS) $<
	$(LD) -shared -o $@ ex1-lib.o

ex1-main.o:	ex1-main.asm
	$(AS) $(ASFLAGS) $<
#-------------------------------------------------------------------------------
# 2nd dynamic library example in assembly
ex2-main:	ex2-main.o ex2-lib.so
	$(LD) -rpath=. -I/lib64/ld-linux-x86-64.so.2 -o $@ $?

ex2-lib.so:	ex2-lib.asm
	$(AS) $(ASFLAGS) $<
	$(LD) -shared -o $@ ex2-lib.o

ex2-main.o:	ex2-main.asm
	$(AS) $(ASFLAGS) $<
#-------------------------------------------------------------------------------
# 3rd dynamic library example in assembly
ex3-main:	ex3-main.o ex3-lib.so
	$(LD) -rpath=. -I/lib64/ld-linux-x86-64.so.2 -o $@ $?

ex3-lib.so:	ex3-lib.asm
	$(AS) $(ASFLAGS) $<
	$(LD) -shared -o $@ ex3-lib.o

ex3-main.o:	ex3-main.asm
	$(AS) $(ASFLAGS) $<
#-------------------------------------------------------------------------------
# 4th dynamic library example using C and assembly
ex4-main:	ex4-main.c ex4-lib.so
	gcc -v -Wl,-rpath=.,-I/lib64/ld-linux-x86-64.so.2 -o $@ $?

ex4-lib.so:	ex4-lib.asm
	$(AS) $(ASFLAGS) $<
	gcc -v -shared -o $@ ex4-lib.o
#-------------------------------------------------------------------------------
clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.so

.PHONY:	clean
