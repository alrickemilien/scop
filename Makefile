#
# Makefile only for Darwin / OSx
#

SCOP=scop

OS := $(shell uname -s)

ifneq ($(OS), Darwin)
	$(error OSX required ...)
endif

# Choose compiler path when not set
ifndef $(CC)
	CC=gcc
endif

# Choose cmake path when not set
ifndef $(CMAKE)
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

SRC=src/main.c \
	src/lib/create_triangle.c \
	src/lib/load_shaders.c \

OBJ=$(SRC:.c=.o)

INCLUDE=-I include

.PHONY: all clean fclean

all: gitsubmodule $(SCOP)

$(SCOP): $(OBJ)
	LIBRARY_PATH=$(LIBRARY_PATH) $(CC) $^ -o $@ $(INCLUDE) $(LIBS)

%.o: %.c
	C_INCLUDE_PATH=$(C_INCLUDE_PATH) $(CC) -o $@ -c $< $(INCLUDE) $(CCFLAGS)

gitsubmodule:
	git submodule init
	git submodule update
	# make -C external/glew
	(cd external/glfw && $(CMAKE) .)
	make -C external/glfw

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(SCOP)

re: fclean all
