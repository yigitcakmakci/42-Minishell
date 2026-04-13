/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:42 by burozdem          #+#    #+#             */
/*   Updated: 2026/02/24 21:46:42 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	create_env(char *key, char *value, t_all *all)
{
	t_env	*new_env;
	t_env	*current;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		reset_all(all, EXIT_ALLOC_FAIL);
	
	new_env->key = ft_strdup(key, all);
	
	if (value)
		new_env->value = ft_strdup(value, all);
	else
		new_env->value = NULL;
	
	new_env->next = NULL;
	if (all->env == NULL)
		all->env = new_env;
	else
	{
		current = all->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_env;
	}
}

void	put_env(t_all *all, char **env_list)
{
	int		i;
	char	*key;
	char	*value;
	char	*equals_pos;

	i = 0;
	while (env_list[i])
	{
		equals_pos = ft_strchr(env_list[i], '=');
		if (equals_pos)
		{
			key = ft_substr(env_list[i], 0, equals_pos - env_list[i], all);
			value = ft_strdup(equals_pos + 1, all);
		}
		else
		{
			key = ft_strdup(env_list[i], all);
			value = NULL;
		}
		create_env(key, value, all); 
		free(key);
		free(value);
		i++;
	}
}
