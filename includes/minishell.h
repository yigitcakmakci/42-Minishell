#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>
extern int g_exit_status;
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
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

//LEXICAL.C
t_token  *lexical(char *input);

//PARSER&EXPANDER.C
void    expander(t_token *tokens, char **envp);

//LIST_MANAGEMENT.C
int     add_word_to_list(t_token **tokens, char *str, t_token_type type);

//ITİLS.C
int is_word(char c);
int is_space(char c);

#endif