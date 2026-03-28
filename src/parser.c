#include "../includes/minishell.h"
#include "../libft/libft.h"

int count_cmds(t_token *tokens)
{
    int     i;
    t_token *temp;

    i = 0;
    temp = tokens;
    while (temp && temp->type != PIPE)
    {
        temp = temp->next;
        i++;
    }
    return (i);
}

void    convert_command(t_token *tokens, t_cmd **cmds)
{
    t_cmd   *new_node;
    t_cmd   *last_cmd;
    int     i;

    new_node = NULL;
    last_cmd = NULL;
    while (tokens)
    {
        if (!new_node)
        {
            new_node = init_new_cmd(tokens);
            i = 0;
        }
        if (is_word_token(tokens->type))
            new_node->args[i++] = ft_strdup(tokens->value);
        else if (tokens->type == RED_IN || tokens->type == RED_OUT)
            convert_redirection(&tokens, new_node);
        else if (tokens->type == PIPE)
            convert_pipe(cmds, &last_cmd, &new_node, i);
        tokens = tokens->next;
    }
    if (new_node)
        convert_pipe(cmds, &last_cmd, &new_node, i);
}

t_cmd   *parser(t_token *tokens, char **envp)
{
    t_cmd   *cmds;
    t_token *temp_tokens;

    (void)envp;
    cmds = NULL;
    temp_tokens = tokens;
    while (temp_tokens)
    {
        if (temp_tokens->rif == 1)
            join_list(&temp_tokens);
        else
            temp_tokens = temp_tokens->next;
    }
    convert_command(tokens, &cmds);
    return (cmds);
}