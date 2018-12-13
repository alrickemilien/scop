include libvec.mk

CCFLAGS= -Wall -Wextra -Werror -Wno-unused

OBJ=$(SRC:.c=.o)

NAME=libvec.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@rm -rf $(OBJ)

.PHONY: clean fclean

fclean: clean
	@rm -rf $(NAME)

re: fclean all
