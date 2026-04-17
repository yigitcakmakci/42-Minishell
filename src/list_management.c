/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:01 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/03/31 15:48:14 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

/*
** Her t_token node'unu ve içindeki value string'ini free'ler.
** Lexer'dan dönen liste, syntax error veya exec bittikten sonra bununla temizlenir.
*/
void	free_token_list(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void	join_list(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next_node;
	char	*new_val;

	tmp = *tokens;
	next_node = tmp->next;
	new_val = ft_strjoin(tmp->value, next_node->value);
	tmp->rif = next_node->rif;
	tmp->next = next_node->next;
	free(tmp->value);
	free(next_node->value);
	free(next_node);
	tmp->value = new_val;
}

static void	add_list_str(t_token **tokens, char *content, t_token_type type,
		int rif)
{
	t_token	*new_node;
	t_token	*tmp;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->type = type;
	new_node->value = content;
	new_node->rif = rif;
	new_node->next = NULL;
	if (*tokens == NULL)
		*tokens = new_node;
	else
	{
		tmp = *tokens;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

static int	get_token_len(char *str, t_token_type type)
{
	int	len;

	len = 0;
	if (type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
	{
		len++;
		while (str[len] && str[len] != str[0])
			len++;
		if (str[len] == str[0])
			len++;
	}
	else if (type == WORD)
	{
		while (str[len] && is_word(str[len]))
			len++;
	}
	else if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	return (len);
}

int	add_word_to_list(t_token **tokens, char *str, t_token_type type)
{
	int		len;
	char	*token;
	int		rif;

	rif = 0;
	len = get_token_len(str, type);
	token = ft_substr(str, 0, len);
	if ((type == SINGLE_QUOTES || type == DOUBLE_QUOTES || type == WORD)
		&& str[len] && !is_space(str[len]) && !is_operators(str[len]))
	{
		rif = 1;
	}
	add_list_str(tokens, token, type, rif);
	return (len);
}
