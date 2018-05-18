#
# Include makefile for libllp
# This makefile provides the rule definition for building the I/O library. It
# should be included at the end of all makefiles in source directories where
# there are dependencies on the I/O library. This enables make to be run inside
# those directories and the library will be correctly built.

$(LIBLLP):
	(cd $(ROOT)/lib && $(MAKE))
