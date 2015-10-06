#PROGS = rotate_matrix snakeprint_matrix
PROGS = rotate_matrix
ROTATE_MATRIX_OBJS = rotate_matrix.o
#SNAKEPRINT_MATRIX_OBJS = snakeprint_matrix.o
OBJS = $(ROTATE_MATRIX_OBJS)
#OBJS = $(ROTATE_MATRIX_OBJS) $(SNAKEPRINT_MATRIX_OBJS)

include ../Make.bin

rotate_matrix: $(ROTATE_MATRIX_OBJS)
	$(CC) $(CFLAGS) -L$(LIBCHELPER_LIB) -L$(LIBCARRAY_LIB) -o $@ $? -l$(LIBCARRAY) -l$(LIBCHELPER)

#snakeprint_matrix: $(SNAKEPRINT_MATRIX_OBJS)
#	$(CC) $(CFLAGS) -L$(LIBCHELPER_LIB) -L$(LIBCARRAY_LIB) -o $@ $? -l$(LIBCARRAY) -l$(LIBCHELPER)
