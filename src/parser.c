#include "../includes/minishell.h"
#include <stdio.h>

void    parser(t_token *tokens, char **envp)
{
    (void)envp;
    t_token *temp_tokens = tokens;
    while (temp_tokens != NULL)
    {
        if (temp_tokens->rif == 1)
            join_list(&temp_tokens);
        else
            temp_tokens = temp_tokens-> next;
    }
}