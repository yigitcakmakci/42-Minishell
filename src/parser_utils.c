#include "../includes/minishell.h"
#include <fcntl.h>
#include <stdlib.h>

int is_word_token(t_token_type type)
{
    if (type == WORD || type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
        return (1);
    return (0);
}

t_cmd   *init_new_cmd(t_token *tokens)
{
    t_cmd   *new_node;

    new_node = malloc(sizeof(t_cmd));
    if (!new_node)
        return (NULL);
    new_node->infd = 0;
    new_node->outfd = 1;
    new_node->next = NULL;
    new_node->args = malloc(sizeof(char *) * (count_cmds(tokens) + 1));
    return (new_node);
}

void    convert_redirection(t_token **tokens, t_cmd *new_node)
{
    int flags;

    flags = O_CREAT | O_TRUNC | O_RDWR;
    if ((*tokens)->type == RED_IN)
        new_node->infd = open((*tokens)->next->value, O_RDONLY, 0777);
    else if ((*tokens)->type == RED_OUT)
        new_node->outfd = open((*tokens)->next->value, flags, 0777);
    *tokens = (*tokens)->next;
}

void    convert_pipe(t_cmd **cmds, t_cmd **last_cmd, t_cmd **new_node, int i)
{
    (*new_node)->args[i] = NULL;
    if (!*cmds)
        *cmds = *new_node;
    else
        (*last_cmd)->next = *new_node;
    *last_cmd = *new_node;
    *new_node = NULL;
}