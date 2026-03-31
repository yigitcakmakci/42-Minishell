/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:52 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/03/31 15:58:50 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	fill_unquoted(char *new_val, char *old_val)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	while (old_val[i])
	{
		if (old_val[i] == 34 || old_val[i] == 39)
		{
			q = old_val[i++];
			while (old_val[i] && old_val[i] != q)
				new_val[j++] = old_val[i++];
			if (old_val[i])
				i++;
		}
		else
			new_val[j++] = old_val[i++];
	}
	new_val[j] = '\0';
}

static void	remove_quotes(t_token *tokens)
{
	t_token	*tmp;
	char	*new_val;

	tmp = tokens;
	while (tmp)
	{
		new_val = malloc(ft_strlen(tmp->value) - count_quotes(tmp->value) + 1);
		if (new_val)
			fill_unquoted(new_val, tmp->value);
		free(tmp->value);
		tmp->value = new_val;
		tmp = tmp->next;
	}
}

static int	handle_dollar(t_token *tmp, int i, char **envp)
{
	char	*new_val;

	if (tmp->value[i + 1] == '?')
	{
		new_val = ft_itoa(g_exit_status);
		printf("G_EXIT_STATUS : %s\n", new_val);
		free(new_val);
		return (0);
	}
	new_val = sandwich(tmp->value, i, envp);
	free(tmp->value);
	tmp->value = new_val;
	return (1);
}

static void	expand_token_value(t_token *tmp, char **envp)
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
			if (handle_dollar(tmp, i, envp))
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

void	expander(t_token *tokens, char **envp)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == DOUBLE_QUOTES)
			expand_token_value(tmp, envp);
		tmp = tmp->next;
	}
	remove_quotes(tokens);
}
