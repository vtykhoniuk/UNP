PROGS = rotate_matrix
ROTATE_MATRIX_OBJS = rotate_matrix.o
OBJS = $(ROTATE_MATRIX_OBJS)

include ../Make.bin

rotate_matrix: $(ROTATE_MATRIX_OBJS)
	$(CC) $(CFLAGS) -L$(LIBCHELPER_LIB) -L$(LIBCARRAY_LIB) -o $@ $? -l$(LIBCHELPER) -l$(LIBCARRAY)
