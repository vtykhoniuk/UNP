PROGS = begin_of_circle
BEGIN_OF_CICLE_OBJS = begin_of_circle.o
OBJS = $(BEGIN_OF_CICLE_OBJS)

include ../Make.bin

begin_of_circle: $(BEGIN_OF_CICLE_OBJS)
	$(CC) $(CFLAGS) -L$(LIBCHELPER_LIB) -L$(LIBCARRAY_LIB) -o $@ $? -l$(LIBCARRAY) -l$(LIBCHELPER)
