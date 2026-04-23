/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:01 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 20:40:12 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	join_list(t_token **tokens, t_shell *shell)
{
	t_token	*tmp;
	t_token	*next_node;
	char	*new_val;

	tmp = *tokens;
	next_node = tmp->next;
	new_val = gc_strjoin(tmp->value, next_node->value, &shell->gc);
	tmp->rif = next_node->rif;
	tmp->next = next_node->next;
	tmp->value = new_val;
}

static void	add_node_back(t_token **tokens, t_token *new_node)
{
	t_token	*tmp;

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

int	add_word_to_list(t_token **tokens, char *str, t_token_type type,
		t_shell *shell)
{
	int		len;
	int		rif;
	t_token	*new;

	len = get_token_len(str, type);
	rif = 0;
	if ((type == SINGLE_QUOTES || type == DOUBLE_QUOTES || type == WORD)
		&& str[len] && !is_space(str[len]) && !is_operators(str[len]))
		rif = 1;
	new = gc_malloc(sizeof(t_token), &shell->gc);
	if (new)
	{
		new->type = type;
		new->value = gc_substr(str, 0, len, &shell->gc);
		new->rif = rif;
		new->next = NULL;
		add_node_back(tokens, new);
	}
	return (len);
}

void	free_token_list(t_token *tokens)
{
	(void)tokens;
}
