#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

static char *sandwich(char *str, int cheese_adress, char **envp)
{
    int     i = 0;
    int     j = 0;
    int     len = cheese_adress;
    char    *real_cheese;
    int     str_len = 0;
    int     envp_len = 0;
    char    *sandwich;
    sandwich = ft_strdup("");
    while (str[str_len])
        str_len++;
    while (str[len] != '\0' && str[len] != ' ' && str[len] != '\t')
        len++;
    real_cheese = ft_substr(str,cheese_adress + 1,len);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(real_cheese, envp[i], len - 1) == 0)
        {
            sandwich = ft_strjoin(sandwich, ft_substr(str, 0, cheese_adress));
            while (envp[i][j] && envp[i][j] != '=')
            {
                j++;
            }
            while (envp[i][envp_len])
                envp_len++;
            sandwich = ft_strjoin(sandwich, ft_substr(envp[i],j + 1, envp_len));
            sandwich = ft_strjoin(sandwich, ft_substr(str, len, str_len));
            return (sandwich);
        }
        i++;
    }
    return (NULL);
}

void    expander(t_token *tokens, char **envp)
{
    int     i = 0;
    char    *temp_str;
    t_token *temp_token = tokens;
    while (temp_token != NULL)
    {
        if (temp_token->type == WORD || temp_token->type == DOUBLE_QUOTES)
        {
            i = 0;
            temp_str = NULL;
            temp_str = temp_token->value;
            while (temp_str[i])
            {
                if (temp_str[i] == '$')
                {
                    if (temp_str[i + 1] == '?')
                    {
                        printf("'$?' YAPIM AŞAMASINDA\n");
                    }
                    else
                    {
                        temp_str = sandwich(temp_str, i, envp);
                        temp_token-> value = temp_str;
                        printf("TOKENS İLK VALUE = %s\n", tokens->value);
                        printf("TEMP_STR = %s\n", temp_str);
                    }
                }
                i++;
            }
        }
        temp_token = temp_token->next;
    }
    
}