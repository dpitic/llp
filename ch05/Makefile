ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS = executable_object
MACRO_ARG = macro_arg_types
OBJS = symbols.o
OBJ_SRC = ${OBJS:.o=.asm}

all:	$(PROGS) $(MACRO_ARG) $(OBJS)

%:	%.asm
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@

macro_arg_types:	macro_arg_types.asm $(LIBLLP)
	$(AS) $(ASFLAGS) $<
	$(LD) $@.o -o $@ $(LDLIBS)

$(OBJS):	$(OBJ_SRC)
	$(AS) $(ASFLAGS) $<

executable_object:	executable_object.asm $(OBJS)
	$(AS) $(ASFLAGS) $<
	$(LD) symbols.o $@.o -o $@

.PHONY:	clean
clean:
	rm -f $(PROGS) $(MACRO_ARG) $(TEMPFILES) *.o
