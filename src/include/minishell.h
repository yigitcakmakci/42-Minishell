/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:12:31 by burozdem          #+#    #+#             */
/*   Updated: 2026/02/24 22:12:31 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>

# define PIPE 0
# define R_APPEND 1
# define R_OUT 2
# define HEREDOC 3
# define R_IN 4
# define WORD 5

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EXIT_FAILURE 1
# define EXIT_ALLOC_FAIL 12
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_CTRL_C 130

typedef struct s_collector
{
	void				*value;
	struct s_collector	*next;
}	t_collector;

typedef struct s_card
{
	int				type;
	int				here_flag;
	char			*value;
	struct s_card	*next;
}	t_card;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirect
{
	int					type;
	char				*filename;
	int					fd;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**args;
	int				args_count;
	int				redirect_count;
	t_redirect		*redirects;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_clean_pid
{
	pid_t					pid;
	struct s_clean_pid		*next;
}	t_clean_pid;

typedef struct s_all
{
	t_collector		*collector;
	t_card			*card;
	t_cmd			*cmd;
	t_env			*env;
	t_clean_pid		*clean_pids;
	int				exit_flag;
	int				exit_status;
}	t_all;

extern int	g_signal;

int		parser(t_all *all);
int		exec(t_all *all);
void	create_card(t_all *all, char *card);
int		expander(t_all *all);
int		lexer(char *line, t_all *all);
void	put_env(t_all *all, char **env_list);
void	*safe_malloc(t_all *all, int size);
int		clean_malloc(t_all *all);
char	*collector_dup(t_all *all, char *line);
int		exec_builtin(t_all *all, t_cmd *cmd, int flag);
int		is_builtin(char *cmd);
void	create_env(char **env_line, t_all *all);
char	*expend_join(char *s1, char *s2, t_all *all);
void	reset_all(t_all *all, int status_type);
void	free_env(t_env *env_list);
void	free_split(char **split);

int		ft_pwd(t_all *all, t_cmd *cmd);
int		ft_cd(t_all *all, t_cmd *cmd);
int		ft_echo(t_all *all, t_cmd *cmd);
int		ft_export(t_all *all, t_cmd *cmd);
int		ft_unset(t_all *all, t_cmd *cmd);
int		ft_env(t_all *all, t_cmd *cmd);
void	print_sorted_env(t_all *all);
int		ft_exit(t_all *all, t_cmd *cmd, int flag);
t_env	*find_env_by_key(t_env *env_list, const char *key);
void	add_or_update_env(t_all *all, const char *key, const char *value);
char	*found_dollar(char *line, int dollar_place, t_all *all);
char	is_char_quote(char value, char quote_type);
char	*handle_exit_status(t_all *all, int dollar, char *before, char *line);
int		syntax_checker(t_all *all);
void	signal_switch(int status);

char	*path_find(char *cmd, t_all *all);
char	**list_to_envp(t_all *all);
char	*here_expand(char *str, t_all *all);
void	handle_redirections(t_cmd *cmd);
int		handle_redir_append(t_redirect *redir, t_cmd *cmd);
int		handle_redir_in(t_redirect *redir);
void	handle_output_redirects(t_redirect *redir, t_cmd *cmd);

void	process_fork_cmd(t_cmd *cmd, t_all *all, int *prev_fd, int pipefd[2]);
int		process_builtin_cmd(t_cmd *cmd, t_all *all, int prev_fd, int len);
void	exec_builtin_single(t_cmd *cmd, t_all *all, int prev_fd);
void	exec_child_process(t_cmd *cmd, t_all *all, int prev_fd, int pipefd[2]);
void	directory_checker(t_cmd *cmd, t_all *all);
void	path_error(t_cmd *cmd, t_all *all);

void	del_quote(t_all *all);
void	put_title(t_all *all);
void	delim_node(t_all *all, t_card *node);
void	check_node(t_card *card, t_card *prev);
char	*ft_getenv(t_env *env, char *key);
int		handle_redir_out(t_redirect *redir, t_cmd *cmd);
int		is_redir(int type);
t_cmd	*init_cmd(t_cmd *head_cmd, t_card *cursor, t_all *all);

int		is_space(char c);
int		special_case(char c, char next, int *place);
int		is_operator(char c, char next);
void	insert_node_at(t_all *all, t_card **pos, char *str);
int		handle_all_heredocs_for_cmd(t_cmd *cmd, t_all *all);

int		ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1, t_all *all);
char	*ft_strjoin(char const *s1, char const *s2, t_all *all);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_all *all);
char	**ft_split(char const *s, char c, t_all *all);
char	*ft_itoa(int n, t_all *all);
int		ft_atoi(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	set_redir(t_all *all, t_cmd *current_cmd, t_card *card, int type);
void	put_redir(t_redirect *redir, t_cmd *current_cmd, t_redirect *tmp);
void	put_node(t_cmd **head_cmd, t_cmd *new_cmd);

int		preprocess_heredocs(t_all *all);
int		read_heredoc_input(int *quoted_and_pipe, char *delimiter, t_all *all);
void	cleanup_heredoc_fds(t_cmd *cmd);
void	cleanup_all_heredoc_fds(t_all *all);
void	wait_forks(t_all *all);
void	set_pid(pid_t pid, t_all *all);

void	sig_exc(int sig);
void	sig_prompt(int sig);
void	sig_cat_quit(int sig);
void	sig_heredoc(int sig);
#endif