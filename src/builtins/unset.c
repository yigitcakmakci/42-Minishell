/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:37 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:28 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

static void	remove_env_key(t_all *all, const char *key)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = all->env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				all->env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_all *all, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_key(all, cmd->args[i]);
		i++;
	}
	return (0);
}
