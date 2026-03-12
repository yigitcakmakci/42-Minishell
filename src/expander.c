#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static char *sandwich(char *str, int cheese_adress, char **envp)
{
    int     i = 0;
    int     var_end = cheese_adress + 1;
    char    *real_cheese;
    char    *sandwich;

    while (str[var_end] && (ft_isalnum(str[var_end]) || str[var_end] == '_'))
        var_end++;

    int var_len = var_end - (cheese_adress + 1);
    if (var_len == 0)
        return (ft_strdup(str));

    real_cheese = ft_substr(str, cheese_adress + 1, var_len);

    while (envp[i])
    {
        int env_name_len = 0;
        while (envp[i][env_name_len] && envp[i][env_name_len] != '=')
            env_name_len++;

        if (var_len == env_name_len && ft_strncmp(real_cheese, envp[i], var_len) == 0)
        {
            char *part1 = ft_substr(str, 0, cheese_adress);
            char *value = ft_strdup(envp[i] + env_name_len + 1);
            char *part2 = ft_strdup(str + var_end);
            
            char *tmp1 = ft_strjoin(part1, value);
            sandwich = ft_strjoin(tmp1, part2);

            free(part1);
            free(value);
            free(part2);
            free(tmp1);
            free(real_cheese);
            return (sandwich);
        }
        i++;
    }
    char *part1 = ft_substr(str, 0, cheese_adress);
    char *part2 = ft_strdup(str + var_end);
    sandwich = ft_strjoin(part1, part2);

    free(part1);
    free(part2);
    free(real_cheese);
    return (sandwich);
}

static int  count_quotes(char *t_token_value)
{
    int     i = 0;
    int     quotes_count = 0;
    int     quotes_index = 0;
    while (t_token_value[i])
        {
            if (t_token_value[i] == 34 || t_token_value[i] == 39)
            {
                quotes_count += 2;
                quotes_index = i;
                while (t_token_value[i] && t_token_value[quotes_index] != t_token_value[i])
                    i++;
            }
            i++;
        }
    return  (quotes_count);
}

static void remove_quotes(t_token *tokens)
{
    t_token *temp_token = tokens;
    char *t_token_value;
    char *new_token_value;
    char quotes_type;
    int i = 0;
    int j = 0;
    while (temp_token)
    {
        i = 0;
        j = 0;
        t_token_value = temp_token -> value;
        new_token_value = malloc(ft_strlen(t_token_value) - count_quotes(t_token_value) + 1);
        while (t_token_value[i])
        {
            while (t_token_value[i] && t_token_value[i] != 34 && t_token_value[i] != 39)
            {
                new_token_value[j] = t_token_value[i];
                i++;
                j++;
            }
            if (t_token_value[i] && (t_token_value[i] == 34 || t_token_value[i] == 39))
            {
                quotes_type = t_token_value[i++];
                while (t_token_value[i] && t_token_value[i] != quotes_type)
                    new_token_value[j++] = t_token_value[i++];
                if (t_token_value[i])
                    i++;
            }
        }
        if (new_token_value)
            new_token_value[j] = '\0';
        else
            new_token_value = ft_strdup("");
        free(temp_token->value);
        temp_token -> value = new_token_value;
        temp_token = temp_token->next;
    }
}

void    expander(t_token *tokens, char **envp)
{
    int     quotes_ctrl = 1;
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
                if (temp_str[i] == 34)
                    quotes_ctrl *= -1;
                if (temp_str[i] == '$')
                {
                    if (temp_str[i + 1] == '?')
                    {
                        printf("G_EXIT_STATUS : %s\n", ft_itoa(g_exit_status));
                    }
                    else
                    {
                       temp_str = sandwich(temp_str, i, envp);
                       temp_token-> value = temp_str;
                    }
                }
                if (temp_str[i] && temp_str[i] == 39 && quotes_ctrl == 1)
                {
                    i++;
                    while (temp_str[i] != 39)
                        i++;
                }
                i++;
            }
        }
        temp_token = temp_token->next;
    }
    remove_quotes(tokens);
}