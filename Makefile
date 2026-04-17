NAME = minishell

SRC = src/main.c src/lexical.c src/list_management.c src/expander.c src/parser.c \
	src/utils.c src/parser_utils.c src/expander_utils.c src/lexical_utils.c \
	src/parser_redir.c \
	src/signal/signal.c \
	src/executor/env_manage.c src/executor/env_set.c src/executor/exec_path.c \
	src/executor/builtin_basic.c src/executor/builtin_cd_exit.c \
	src/executor/builtin_export.c src/executor/exec_builtin.c \
	src/executor/exec_pipeline.c src/executor/exec.c \
	libft/ft_substr.c libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_itoa.c \
	libft/ft_isalnum.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_putendl_fd.c \
	libft/ft_atoi.c libft/ft_split.c libft/ft_strchr.c libft/ft_putstr_fd.c \
	libft/ft_putchar_fd.c libft/ft_isdigit.c libft/ft_isalpha.c

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