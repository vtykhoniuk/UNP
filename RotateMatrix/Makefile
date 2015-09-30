PROGS = rotate_matrix
ROTATE_MATRIX_OBJS = rotate_matrix.o
OBJS = $(ROTATE_MATRIX_OBJS)

include ../Make.bin

rotate_matrix: $(ROTATE_MATRIX_OBJS)
	$(CC) $(CFLAGS) -o $@ $? $(LIBCERROR_STATIC) $(LIBCWRAPERUNIX_STATIC) $(LIBCARRAY_STATIC)
