NAME = minishell

SRC = src/main.c src/lexical.c

OBJ = $(SRC:.c=.o)

READLINE_FLAGS = -lreadline

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_FLAGS) -o $(NAME)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re