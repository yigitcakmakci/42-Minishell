#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

void    add_list_str(t_token **tokens, char *content, t_token_type type)
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
    if (type == WORD)
    {
        if (*str == 34 || *str == 39)
        {
            len++;
            while (str[0] != str[len] && str[len])
                len++;
            add_list_str(tokens, ft_substr(str, 1, len-1), type);
        }
        else
        {
            while ((str[len] <= 'z' && str[len] >= 'a') || (str[len] <= 'Z' && str[len] >= 'A') || (str[len] <= '9' && str[len] >= '0'))
                len++;
            add_list_str(tokens, ft_substr(str, 0, len), type);
        }
    }
    else if (type == HEREDOC || type == APPEND)
    {
        len = 1;
        add_list_str(tokens, ft_substr(str, 0, 2), type);
    }
    
    else
        add_list_str(tokens, ft_substr(str, 0, 1), type);
    return (len);
}
