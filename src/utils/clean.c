/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:24 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:31 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <readline/readline.h>

char	*collector_dup(t_all *all, char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)safe_malloc(all, ft_strlen(line) + 1);
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	free(line);
	return (str);
}

void	reset_all(t_all *all, int status_type)
{
	clean_malloc(all);
	if (all->env)
	{
		free_env(all->env);
		all->env = NULL;
	}
	rl_clear_history();
	all->exit_status = status_type;
	exit(all->exit_status);
}

void	free_env(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
