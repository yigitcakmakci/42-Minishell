#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

static void    add_list_str(t_token **tokens, char *content, t_token_type type)
{
    t_token *new_node;
    t_token *temp_token;
    new_node = malloc(sizeof(t_token));
    temp_token = *(tokens);
    new_node->type = type;
    new_node->value = content;
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

    if (type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
    {
        len++;
        while (str[len] && str[len] != str[0])
            len++;
        if (str[len] == str[0])
            len++;
        token = ft_substr(str, 0, len);
        add_list_str(tokens, token, type);
    }
    else if(type == WORD)
    {
        while (str[len] && is_word(str[len]))
            len++;
        token = ft_substr(str, 0, len);
        add_list_str(tokens, token, type);
    }
    else if (type == HEREDOC || type == APPEND)
    {
        len = 2;
        token = ft_substr(str, 0, len);
        add_list_str(tokens, token, type);
    }
    else
    {
        len = 1;
        token =  ft_substr(str, 0, len);
        add_list_str(tokens, token, type);
    }
    return (len);
}
