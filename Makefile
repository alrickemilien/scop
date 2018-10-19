#
# Makefile only for Darwin / OSx
#

SCOP=scop

OS := $(shell uname -s)

ifneq ($(OS), Darwin)
	$(error OSX required ...)
endif

CCFLAGS= -Wall -Wextra -Werror

LIBS := -framework Cocoa -framework AppKit -framework OpenGL -lglew -lglfw
GLEW := external/glew/include
GLFW := external/glfw/include
C_INCLUDE_PATH := $(GLEW):$(GLFW)
GLEW_LIB := external/glew/lib
GLFW_LIB := external/glfw/lib
LIBRARY_PATH := $(GLEW_LIB):$(GLFW_LIB)

SRC=src/main.c \
	src/lib/create_triangle.c \
	src/lib/load_shaders.c \

OBJ=$(SRC:.c=.o)

INCLUDE=-I include

.PHONY: all clean fclean

all: $(SCOP)

$(SCOP): $(OBJ)
	LIBRARY_PATH=$(LIBRARY_PATH) gcc $^ -o $@ $(INCLUDE) $(LIBS)

%.o: %.c
	C_INCLUDE_PATH=$(C_INCLUDE_PATH) gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(SCOP)

re: fclean all