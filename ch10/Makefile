ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = main_square main_ext main_printer_new main_ldd

all:	$(PROGS)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

main_square:	square.o
	$(CC) $(CFLAGS) $@.c $< -o $@

square.o:	square.c
	$(CC) $(CFLAGS) -c $<

main_ext:	main_ext.o square_ext.o
	$(CC) $(CFLAGS) $? -o $@

main_ext.o:	main_ext.c
	$(CC) $(CFLAGS) -c $<

square_ext.o:	square_ext.c
	$(CC) $(CFLAGS) -c $<

main_printer_new:	main_printer_new.c printer.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

.PHONY:	clean
