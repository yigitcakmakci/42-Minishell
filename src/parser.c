#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int     count_cmds(t_token *tokens)
{
    int i = 0;
    t_token *temp_token = tokens;
    while (temp_token)
    {
        temp_token = temp_token->next;
        //if (temp_token->type == RED_IN || temp_token->type == RED_OUT)
        //    i--;
        i++;
    }
    return (i);// '+' for test->!!!
}

/*char    **add_commands(t_token *tokens)
{
    char **cmds;
    int i = 0;
    int cmds_len = count_cmds(tokens);
    cmds = malloc(sizeof(char *) * (cmds_len + 1));
    while (tokens && tokens-> type == WORD)
    {
        cmds[i] = ft_strdup(tokens->value);
        tokens = tokens->next;
        i++;
    }
    cmds[i] = NULL;
    return cmds;
}*/

void    convert_command(t_token *tokens, t_cmd  **cmds)
{
    t_token *temp_token = tokens;
    t_cmd   *temp_cmd = *(cmds);
    t_cmd   *new_node = malloc(sizeof(t_cmd));
    int     i = 0;
    new_node->infd = 0;
    new_node->outfd = 1;
    new_node->next = NULL;
    new_node->args = malloc(sizeof(char *) * (count_cmds(tokens) + 1));
    while (temp_token)
    {
        if (temp_token->type == WORD || temp_token -> type == SINGLE_QUOTES || temp_token -> type == DOUBLE_QUOTES)
        {
            new_node->args[i] = ft_strdup(temp_token->value);
            i++;
        }
        else if (temp_token->type == RED_IN)
        {
            new_node->infd = open(temp_token->next->value, O_RDWR, 0777);
            temp_token = temp_token->next;
        }
        else if (temp_token->type == RED_OUT)
        {
            new_node->outfd = open(temp_token->next->value, O_CREAT | O_TRUNC | O_RDWR, 0777);
            temp_token = temp_token->next;
        }
        temp_token = temp_token->next;
    }
    new_node->args[i] = NULL;
    if (!temp_cmd)
        *(cmds) = new_node;
    else
        temp_cmd -> next = new_node;
}

t_cmd    *parser(t_token *tokens, char **envp)
{
    (void)envp;
    t_cmd   *cmds = NULL;
    t_token *temp_tokens = tokens;
    while (temp_tokens != NULL)
    {
        if (temp_tokens->rif == 1)
            join_list(&temp_tokens);
        else
            temp_tokens = temp_tokens-> next;
    }
    convert_command(tokens, &cmds);
    return cmds;
}
