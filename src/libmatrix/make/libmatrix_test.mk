ifndef TEST_SRC
	TEST_SRC :=
endif

ifndef TEST_PKG
	TEST_PKG :=
endif

ifndef TEST_INCLUDE
	TEST_INCLUDE :=
endif

TEST_INCLUDE += $(INCLUDE) -I test

TEST_SRC += test/test_new_matrix.c \
						test/test_delete_matrix.c \
						test/test_multiply_matrix_with_scalar.c \
						test/test_multiply_matrix.c \
						test/test_new_matrix_from_raw.c \
						test/test_fill_matrix.c \
						test/test_pmatrix.c

TEST_PKG += test/test_package.c

test: $(patsubst %.c,%,$(TEST_SRC))

$(patsubst %.c,%,$(TEST_SRC)): %: %.c
	@gcc -o $@ $< $(TEST_PKG) $(TEST_INCLUDE) -lm -lmatrix -L . $(CCFLAGS)
