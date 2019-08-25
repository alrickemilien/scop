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

TEST_SRC += ../test/test_multiply_mat4.c \
../test/test_pmat4.c

TEST_PKG += ../test/test_package.c

test: $(patsubst %.c,%,$(TEST_SRC))

$(patsubst %.c,%,$(TEST_SRC)): %: %.c
	@gcc -o $@ $< $(TEST_PKG) $(TEST_INCLUDE) -lm -lmatrix -L ../ $(CCFLAGS)
