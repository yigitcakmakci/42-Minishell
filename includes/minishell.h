/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:50:31 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 20:51:23 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include "../libft/libft.h"

extern int			g_exit_status;

typedef enum e_token_type
{
	WORD,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	PIPE,
	RED_IN,
	RED_OUT,
	APPEND,
	HEREDOC,
}					t_token_type;

typedef struct s_cmd
{
	char			**args;
	char			*path;
	int				infd;
	int				outfd;
	int				expand_heredoc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				rif;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			**envp;
	t_list			*gc;
}					t_shell;

/* GC */
void				*gc_malloc(size_t size, t_list **gc);
void				gc_free_all(t_list **gc);
char				*gc_strdup(const char *s, t_list **gc);
char				*gc_substr(char const *s, unsigned int start,
						size_t len, t_list **gc);
char				*gc_strjoin(char const *s1, char const *s2,
						t_list **gc);
char				*gc_itoa(int n, t_list **gc);
char				**gc_split(char const *s, char c, t_list **gc);

/* LEXICAL_UTILS.C */
int					handle_pipe(t_token *tokens);
int					handle_redirection(t_token *tokens);
int					handle_quotes(char *str);

/* LEXICAL.C */
t_token				*lexical(char *input, t_shell *shell);
void				free_token_list(t_token *tokens);

/* EXPANDER_UTILS.C */
char				*get_env_val(char *var_name, t_shell *shell);
char				*sandwich(char *str, int ch_addr, t_shell *shell);
int					count_quotes(char *str);
void				expand_exit_status(t_token *tmp, int i,
						t_shell *shell);
void				write_expanded_line(int fd, char *line,
						t_shell *shell);

/* EXPANDER.C */
void				expander(t_token *tokens, t_shell *shell);

/* PARSER_REDIR.C */
void				convert_redirection(t_token **tokens,
						t_cmd *new_node, t_shell *shell);
void				handle_heredoc(t_token **tokens,
						t_cmd *new_node, t_shell *shell);

/* PARSER_UTILS.C */
t_cmd				*init_new_cmd(t_token *tokens, t_shell *shell);
int					is_word_token(t_token_type type);
void				convert_pipe(t_cmd **cmds, t_cmd **last_cmd,
						t_cmd **new_node, int i);

/* PARSER.C */
t_cmd				*parser(t_token *tokens, t_shell *shell);
int					count_cmds(t_token *tokens);

/* LIST_MANAGEMENT.C */
int					add_word_to_list(t_token **tokens, char *str,
						t_token_type type, t_shell *shell);
void				join_list(t_token **dest_token, t_shell *shell);

/* UTILS.C */
int					is_word(char c);
int					is_space(char c);
int					is_operators(char c);
int					is_quotes(char c);

/* SIGNAL.C */
void				signal_prompt(void);
void				signal_exec(void);
void				signal_heredoc(void);

/* EXECUTOR/ENV_MANAGE.C */
char				**env_copy(char **envp, t_shell *shell);
void				env_free(char **envp);
char				*env_get(char **envp, const char *key);

/* EXECUTOR/ENV_SET.C */
void				env_set(char ***envp, const char *key,
						const char *val, t_shell *shell);
void				env_unset(char ***envp, const char *key);

/* EXECUTOR/EXEC_PATH.C */
char				*find_path(char *cmd, t_shell *shell);

/* EXECUTOR/EXEC_BUILTIN.C */
int					is_builtin(char *name);
int					exec_builtin(t_cmd *cmd, t_shell *shell);

/* EXECUTOR/EXEC_PIPELINE.C */
void				exec_pipeline(t_cmd *cmds, t_shell *shell);

/* EXECUTOR/EXEC.C */
void				exec(t_cmd *cmds, t_shell *shell);
void				close_cmd_fds(t_cmd *cmds);

/* EXECUTOR/BUILTIN_BASIC.C */
int					builtin_echo(t_cmd *cmd);
int					builtin_pwd(void);
int					builtin_env(char **envp);
int					builtin_unset(t_cmd *cmd, t_shell *shell);

/* EXECUTOR/BUILTIN_CD_EXIT.C */
int					builtin_cd(t_cmd *cmd, t_shell *shell);
int					builtin_exit(t_cmd *cmd);

/* EXECUTOR/BUILTIN_EXPORT.C */
int					builtin_export(t_cmd *cmd, t_shell *shell);

#endif
