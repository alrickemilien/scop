#
# Makefile only for Darwin / OSx
#

SCOP=scop

OS := $(shell uname -s)

ifneq ($(OS), Darwin)
$(error OSX required ...)
endif

# Choose compiler path when not set
ifeq ($(CC),)
CC=gcc
endif

# Choose cmake path when not set
ifeq ($(CMAKE),)
CMAKE=/usr/bin/cmake
endif

CCFLAGS= -Wall -Wextra -Werror

LIBS := -framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo -lglfw3 -lGLEW

GLEW := $(HOME)/.brew/include
GLFW := external/glfw/include
C_INCLUDE_PATH := $(GLEW):$(GLFW)

GLEW_LIB := $(HOME)/.brew/lib
GLFW_LIB := external/glfw/src
LIBRARY_PATH := $(GLEW_LIB):$(GLFW_LIB)

include scop.mk

OBJ=$(SRC:.c=.o)

.PHONY: all clean fclean

all: gitsubmodule $(SCOP)

$(SCOP): $(OBJ)
	make -C src/libft
	make -C src/libmatrix
	#make -C src/libvec
	LIBRARY_PATH=$(LIBRARY_PATH) $(CC) $^ -o $@ $(INCLUDE) $(LIBS)

%.o: %.c
	C_INCLUDE_PATH=$(C_INCLUDE_PATH) $(CC) -o $@ -c $< $(INCLUDE) $(CCFLAGS)

gitsubmodule:
	# git submodule init
	# git submodule update --remote
	make -C external/glew
	(cd external/glfw && $(CMAKE) .)
	make -C external/glfw

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(SCOP)

re: fclean all
