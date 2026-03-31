/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:56 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/03/31 15:47:30 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	print_syntax_error(char *token_val)
{
	printf("syntax error near unexpected token '%s'\n", token_val);
	return (0);
}

int	is_redir(t_token_type type)
{
	return (type == RED_IN || type == RED_OUT || type == APPEND
		|| type == HEREDOC);
}

int	handle_pipe(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp)
		return (1);
	if (tmp->type == PIPE)
		return (print_syntax_error(tmp->value));
	while (tmp->next)
	{
		if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (print_syntax_error(tmp->next->value));
		tmp = tmp->next;
	}
	if (tmp->type == PIPE)
		return (print_syntax_error(tmp->value));
	return (1);
}

int	handle_redirection(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp)
		return (1);
	while (tmp->next)
	{
		if (is_redir(tmp->type) && tmp->next->type != WORD)
			return (print_syntax_error(tmp->next->value));
		tmp = tmp->next;
	}
	if (is_redir(tmp->type))
		return (print_syntax_error("newline"));
	return (1);
}

int	handle_quotes(char *str)
{
	int	i;
	int	q_idx;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			q_idx = i++;
			while (str[i] && str[i] != str[q_idx])
				i++;
			if (!str[i])
			{
				printf("-------QUOTES ERROR!-------\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
