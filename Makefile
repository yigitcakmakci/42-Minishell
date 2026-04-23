NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READLINE_FLAGS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main.c src/lexical.c src/list_management.c src/expander.c src/parser.c \
	src/utils.c src/parser_utils.c src/expander_utils.c src/lexical_utils.c \
	src/parser_redir.c src/gc.c src/gc_utils.c src/gc_split.c \
	src/signal/signal.c \
	src/executor/env_manage.c src/executor/env_set.c src/executor/exec_path.c \
	src/executor/builtin_basic.c src/executor/builtin_cd_exit.c \
	src/executor/builtin_export.c src/executor/exec_builtin.c \
	src/executor/exec_pipeline.c src/executor/exec.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re