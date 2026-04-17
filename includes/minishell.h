/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:50:31 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/10 10:20:58 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

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
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				rif;
	struct s_token	*next;
}					t_token;

// LEXICAL_UTILS.C
int					handle_pipe(t_token *tokens);
int					handle_redirection(t_token *tokens);
int					handle_quotes(char *str);

// LEXICAL.C
t_token				*lexical(char *input);

// EXPANDER_UTILS.C
char				*get_env_val(char *var_name, char **envp);
char				*sandwich(char *str, int ch_addr, char **envp);
int					count_quotes(char *str);
void				expand_exit_status(t_token *tmp, int i);

// EXPANDER.C
void				expander(t_token *tokens, char **envp);

// PARSER_REDIR.C
void				convert_redirection(t_token **tokens, t_cmd *new_node);
void				handle_heredoc(t_token **tokens, t_cmd *new_node);

// PARSER_UTILS.C
t_cmd				*init_new_cmd(t_token *tokens);
int					is_word_token(t_token_type type);
void				convert_pipe(t_cmd **cmds, t_cmd **last_cmd,
						t_cmd **new_node, int i);

// PARSER.C
t_cmd				*parser(t_token *tokens, char **envp);
int					count_cmds(t_token *tokens);

// LIST_MANAGEMENT.C
int					add_word_to_list(t_token **tokens, char *str,
						t_token_type type);
void				join_list(t_token **dest_token);

// UTİLS.C
int					is_word(char c);
int					is_space(char c);
int					is_operators(char c);
int					is_quotes(char c);

// LIST_MANAGEMENT.C (ek)
void					free_token_list(t_token *tokens);

// SIGNAL.C
void					signal_prompt(void);
void					signal_exec(void);
void					signal_heredoc(void);

// EXECUTOR/EXEC_ENV.C
char					**env_copy(char **envp);
void					env_free(char **envp);
char					*env_get(char **envp, const char *key);
void					env_set(char ***envp, const char *key, const char *val);
void					env_unset(char ***envp, const char *key);
char					*find_path(char *cmd, char **envp);

// EXECUTOR/EXEC_BUILTIN.C
int						is_builtin(char *name);
int						exec_builtin(t_cmd *cmd, char ***envp);

// EXECUTOR/EXEC.C
void					exec(t_cmd *cmds, char ***envp);
void					free_cmds(t_cmd *cmds);

#endif