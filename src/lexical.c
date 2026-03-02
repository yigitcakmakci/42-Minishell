#include <stdio.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int handle_pipe(t_token *tokens)
{
    t_token *temp_token = tokens;
    if (temp_token -> type == PIPE)
    {
        printf("syntax error near unexpected token '%s'", temp_token->value);
        return (0);
    }
    while (temp_token -> next != NULL)
    {
        if (temp_token ->type == PIPE && temp_token -> next -> type == PIPE)
        {
            printf("syntax error near unexpected token '%s'", temp_token->next->value);
            return (0);
        }
        temp_token = temp_token->next;
    }
    if (temp_token -> type == PIPE)
    {
        printf("syntax error near unexpected token '%s'", temp_token->value);
        return(0);
    }
    return(1);
}

int handle_redirection(t_token *tokens)
{
    t_token *temp_token = tokens;
    while (temp_token -> next != NULL)
    {
        if ((temp_token -> type == RED_IN || temp_token -> type == RED_OUT || temp_token -> type == APPEND || temp_token -> type == HEREDOC) && (temp_token -> next -> type != WORD))
        {
            printf("syntax error near unexpected token '%s'", temp_token->next->value);
            return (0);
        }
        temp_token = temp_token -> next;
    }
    if (temp_token -> type == RED_IN || temp_token -> type == RED_OUT || temp_token -> type == APPEND || temp_token -> type == HEREDOC)
    {
        printf("syntax error near unexpected token '%s'", temp_token->value);
        return(0);
    }
    return(1);
}

static  int handle_quotes(char *str)
{
    int i = 0;
    int temp_quote_index;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
        {
            temp_quote_index = i;
            i++;
            while (str[temp_quote_index] != str[i] && str[i])
                i++;
            if (!str[i])
            {
                printf("-------QUOTES ERROR!-------");
                return(0);
            }
        }
        i++;
    }
    return(1);
}

static int handle_list(t_token  *tokens, char *input)
{
    if (!handle_pipe(tokens))
        return(0);
    if (!handle_redirection(tokens))
        return(0);
    if (!handle_quotes(input))
        return(0);
    
    return(1);
}

t_token *lexical(char *input)
{
    t_token *tokens = NULL;
    int i = 0;
    
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if (!input[i]) // Sona ulaştıysak döngüyü kır
            break ;

        if (input[i] == 34)
            i += add_word_to_list(&tokens, &input[i], DOUBLE_QUOTES);
        else if (input[i] == 39)
            i += add_word_to_list(&tokens, &input[i], SINGLE_QUOTES);
        else if (is_word(input[i]))
            i += add_word_to_list(&tokens, &input[i], WORD);
        else if (input[i] == '<' && input[i + 1] == '<')
            i += add_word_to_list(&tokens, &input[i], HEREDOC);
        else if (input[i] == '<')
            i += add_word_to_list(&tokens, &input[i], RED_IN);
        else if (input[i] == '>' && input[i + 1] == '>')
            i += add_word_to_list(&tokens, &input[i], APPEND);
        else if (input[i] == '>')
            i += add_word_to_list(&tokens, &input[i], RED_OUT);
        else if (input[i] == '|')
            i += add_word_to_list(&tokens, &input[i], PIPE);
        else
            i++; // Hiçbirine uymazsa (örneğin tanımsız bir sembol), sonsuz döngü olmasın diye atla
    }
    
    if(!handle_list(tokens, input))
        printf("\n<<<<<<<GEÇERSİZ ARGÜMAN>>>>>>>>\n");
    return (tokens);
}