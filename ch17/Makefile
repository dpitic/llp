ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# GCC flags
CFLAGS = -Wall -g
# GCC linker flags
LDFLAGS = -Wl,-rpath=.,-I/lib64/ld-linux-x86-64.so.2
# GCC shared object flags
SOFLAGS = -fpic -shared

PROGS = pthread_create_mwe thread_join_mwe dist_fact_sp dist_fact_mp_simple \
	dist_fact_mp mutex_ex_counter_bad mutex_ex_counter_good condvar_mwe \
	semaphore_mwe reordering_cpu_mwe

all:	$(PROGS)

#-------------------------------------------------------------------------------
%:	%.c
	$(CC) $(CFLAGS) -pthread -o $@ $@.c
#-------------------------------------------------------------------------------
pthread_create_mwe:	pthread_create_mwe.c
	$(CC) $(CFLAGS) -O3 -pthread -o $@ $<
#-------------------------------------------------------------------------------
dist_fact_sp:	dist_fact_sp.c
	$(CC) $(CFLAGS) -O3 -std=c99 -o $@ $<
#-------------------------------------------------------------------------------
dist_fact_mp_simple:	dist_fact_mp_simple.c
	$(CC) $(CFLAGS) -O3 -pthread -std=c99 -o $@ $<
#-------------------------------------------------------------------------------
dist_fact_mp:	dist_fact_mp.c
	$(CC) $(CFLAGS) -O3 -std=c99 -pthread -o $@ $<
#-------------------------------------------------------------------------------
mutex_ex_counter_bad:	mutex_ex_counter_bad.c
	$(CC) $(CFLAGS) -O0 -pthread -std=c99 -o $@ $<
#-------------------------------------------------------------------------------
mutex_ex_counter_good:	mutex_ex_counter_good.c
	$(CC) $(CFLAGS) -O0 -pthread -std=c99 -o $@ $<
#-------------------------------------------------------------------------------
condvar_mwe:	condvar_mwe.c
	$(CC) $(CFLAGS) -pthread -std=c99 -o $@ $<
#-------------------------------------------------------------------------------
semaphore_mwe:	semaphore_mwe.c
	$(CC) $(CFLAGS) -pthread -std=c99 -o $@ $<
#-------------------------------------------------------------------------------
reordering_cpu_mwe:	reordering_cpu_mwe.c
	$(CC) $(CFLAGS) -pthread -O2 -o $@ $<
#-------------------------------------------------------------------------------
clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.so *.objdump

.PHONY:	clean
