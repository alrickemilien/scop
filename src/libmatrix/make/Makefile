include libmatrix.mk

CCFLAGS= -Wall -Wextra -Werror

OBJ=$(SRC:.c=.o)

ROOT=../

NAME=$(ROOT)/libmatrix.a

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
	@rm -rf $(patsubst %.c,%,$(TEST_SRC))

re: fclean all
