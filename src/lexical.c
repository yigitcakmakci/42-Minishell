#include <stdio.h>
#include <stdlib.h>
#include "../includes/minishell.h"

void    lexical(char *input)
{
    t_token *tokens = NULL;
    int i = 0;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] <= 'z' && input[i] >= 'a') || (input[i] <= 'Z' && input[i] >= 'A') || (input[i] <= '9' && input[i] >= '0') || (input[i] == 34 || input[i] == 39))
        {
            i+=add_word_to_list(&tokens, &input[i], WORD);
        }
        if (input[i] == '<')
            add_word_to_list(&tokens, &input[i], RED_IN);
        else if (input[i] == '>')
            add_word_to_list(&tokens, &input[i], RED_OUT);
        else if (input[i] == '|')
            add_word_to_list(&tokens, &input[i], PIPE);
        i++;
    }
    while (tokens != NULL)
    {
        printf("KELİME: %s\nTYPE: %d\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
}