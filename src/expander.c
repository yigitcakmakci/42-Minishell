/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:52 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 21:03:12 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static void	remove_quotes(t_token *tokens, t_shell *shell)
{
	t_token	*t;
	char	*n;
	int		i[2];
	char	q;

	t = tokens;
	while (t)
	{
		n = gc_malloc(ft_strlen(t->value) + 1, &shell->gc);
		i[0] = -1;
		i[1] = 0;
		q = 0;
		while (t->value && t->value[++i[0]])
		{
			if (!q && (t->value[i[0]] == 34 || t->value[i[0]] == 39))
				q = t->value[i[0]];
			else if (q && t->value[i[0]] == q)
				q = 0;
			else
				n[i[1]++] = t->value[i[0]];
		}
		n[i[1]] = '\0';
		t->value = n;
		t = t->next;
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

static t_token	*split_words(t_token *tmp, t_shell *shell)
{
	char	**words;
	t_token	*new_tok;
	int		i;

	words = gc_split(tmp->value, ' ', &shell->gc);
	if (!words || !words[0])
		return (tmp);
	tmp->value = words[0];
	i = 1;
	while (words[i])
	{
		new_tok = gc_malloc(sizeof(t_token), &shell->gc);
		new_tok->type = WORD;
		new_tok->value = words[i];
		new_tok->rif = 0;
		new_tok->next = tmp->next;
		tmp->next = new_tok;
		tmp = new_tok;
		i++;
	}
	return (tmp);
}

void	expander(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == DOUBLE_QUOTES)
			expand_token_value(tmp, shell);
		if (tmp->type == WORD && ft_strchr(tmp->value, ' '))
			tmp = split_words(tmp, shell);
		tmp = tmp->next;
	}
	remove_quotes(tokens, shell);
}
