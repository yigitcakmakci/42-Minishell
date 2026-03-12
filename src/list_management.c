#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

void    join_list(t_token **tokens)
{
    t_token *temp_token = *(tokens);
    char *new_dest = ft_strjoin(temp_token->value, temp_token->next->value);
    t_token *temp_end_token = temp_token->next->next;
    temp_token->rif = temp_token->next->rif;
    free(temp_token->next->value);
    free(temp_token->next);
    free(temp_token->value);
    temp_token->value = new_dest;
    temp_token->next = temp_end_token;
    printf("TESTEND_JOIN_LIST\n");
}

static void    add_list_str(t_token **tokens, char *content, t_token_type type, int rif)
{
    t_token *new_node;
    t_token *temp_token;
    new_node = malloc(sizeof(t_token));
    temp_token = *(tokens);
    new_node->type = type;
    new_node->value = content;
    new_node->rif = rif;
    new_node->next = NULL;
    if (*(tokens) == NULL)
        *(tokens) = new_node;
    else
    {
        while (temp_token -> next != NULL)
            temp_token = temp_token->next;
        temp_token -> next = new_node;
    }
}

int add_word_to_list(t_token **tokens, char *str, t_token_type type)
{
    int     len = 0;
    char    *token;
    int     rif = 0;

    if (type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
    {
        len++;
        while (str[len] && str[len] != str[0])
            len++;
        if (str[len] == str[0])
            len++;
        token = ft_substr(str, 0, len);
        if (str[len] && !is_space(str[len]) && !is_operators(str[len]))
            rif = 1;
        add_list_str(tokens, token, type, rif);
    }
    else if(type == WORD)
    {
        while (str[len] && is_word(str[len]))
            len++;
        token = ft_substr(str, 0, len);
        if (str[len] && !is_space(str[len]) && !is_operators(str[len]))
            rif = 1;
        add_list_str(tokens, token, type, rif);
    }
    else if (type == HEREDOC || type == APPEND)
    {
        len = 2;
        token = ft_substr(str, 0, len);
        add_list_str(tokens, token, type, rif);
    }
    else
    {
        len = 1;
        token =  ft_substr(str, 0, len);
        add_list_str(tokens, token, type, rif);
    }
    return (len);
}
