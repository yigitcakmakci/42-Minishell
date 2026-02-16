#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>

typedef enum e_token_tpye
{
    WORD,
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
t_token  *lexical();

//LIST_MANAGEMENT
int     add_word_to_list(t_token **tokens, char *str, t_token_type type);

#endif