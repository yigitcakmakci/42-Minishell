/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:52 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/21 21:46:07 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	copy_without_quotes(char *new_val, char *old_val)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	q = 0;
	while (old_val && old_val[i])
	{
		if (!q && (old_val[i] == 34 || old_val[i] == 39))
			q = old_val[i];
		else if (q && old_val[i] == q)
			q = 0;
		else
			new_val[j++] = old_val[i];
		i++;
	}
	new_val[j] = '\0';
}

static void	remove_quotes(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;
	char	*new_val;

	tmp = tokens;
	while (tmp)
	{
		new_val = gc_malloc(ft_strlen(tmp->value)
				- count_quotes(tmp->value) + 1, &shell->gc);
		copy_without_quotes(new_val, tmp->value);
		tmp->value = new_val;
		tmp = tmp->next;
	}
}

static int	handle_dollar(t_token *tmp, int i, t_shell *shell)
{
	char	*new_val;

	if (tmp->value[i + 1] == '?')
	{
		expand_exit_status(tmp, i, shell);
		return (1);
	}
	if (!tmp->value[i + 1] || (!ft_isalnum(tmp->value[i + 1])
			&& tmp->value[i + 1] != '_'))
		return (0);
	new_val = sandwich(tmp->value, i, shell);
	free(tmp->value);
	tmp->value = new_val;
	return (1);
}

static void	expand_token_value(t_token *tmp, t_shell *shell)
{
	int	i;
	int	q_ctrl;

	i = 0;
	q_ctrl = 1;
	while (tmp->value && tmp->value[i])
	{
		if (tmp->value[i] == 34)
			q_ctrl *= -1;
		if (tmp->value[i] == '$')
		{
			if (handle_dollar(tmp, i, shell))
				continue ;
		}
		if (tmp->value[i] == 39 && q_ctrl == 1)
		{
			i++;
			while (tmp->value[i] && tmp->value[i] != 39)
				i++;
		}
		if (tmp->value[i])
			i++;
	}
}

void	expander(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == DOUBLE_QUOTES)
			expand_token_value(tmp, shell);
		tmp = tmp->next;
	}
	remove_quotes(tokens, shell);
}
