#
# Makefile only for Darwin / OSx
#

SCOP=../bin/scop

OS := $(shell uname -s)

ifneq ($(OS), Darwin)
$(error OSX required ...)
endif

# Choose compiler path when not set
ifeq ($(CC),)
CC=gcc
endif

BIN=$(PWD)/bin

# Choose cmake path when not set
ifeq ($(CMAKE),)
CMAKE=/usr/bin/cmake
endif

CCFLAGS= -Wall -Wextra -Werror

LIBS := -framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo -lglfw3 -lGLEW

GLEW := $(HOME)/.brew/include
GLFW := $(HOME)/.brew/include
C_INCLUDE_PATH := $(GLEW):$(GLFW)

GLEW_LIB := $(HOME)/.brew/lib
GLFW_LIB := $(HOME)/.brew/include
LIBRARY_PATH := $(GLEW_LIB):$(GLFW_LIB)

include scop.mk

OBJ=$(SRC:.c=.o)

.PHONY: all clean fclean

all: $(SCOP)

$(SCOP): $(OBJ)
	make -C ../src/libmatrix/make
	mkdir -p ../bin
	LIBRARY_PATH=$(LIBRARY_PATH) $(CC) $^ -o $@ $(INCLUDE) $(LIBS) $(CCFLAGS)

%.o: %.c
	C_INCLUDE_PATH=$(C_INCLUDE_PATH) $(CC) -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	make fclean -C ../src/libmatrix/make
	@rm -rf $(SCOP)

re: fclean all
