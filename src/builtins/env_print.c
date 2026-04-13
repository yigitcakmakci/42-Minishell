/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:13 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:15 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>

int	cmp_env(const void *a, const void *b)
{
	const char	*s1;
	const char	*s2;

	s2 = *(const char **)b;
	s1 = *(const char **)a;
	return (ft_strcmp(s1, s2));
}

int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	ft_sort(char **keys, int size)
{
	int		j;
	char	*temp;

	j = 0;
	while (0 < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(keys[j], keys[j + 1]) > 0)
			{
				temp = keys[j];
				keys[j] = keys[j + 1];
				keys[j + 1] = temp;
			}
			j++;
		}
		size--;
	}
}

static char	**get_sorted_keys(t_all *all)
{
	int		size;
	char	**keys;
	t_env	*current;
	int		i;

	current = all->env;
	i = 0;
	size = env_list_size(all->env);
	keys = malloc(sizeof(char *) * (size + 1));
	if (!keys)
		reset_all(all, EXIT_ALLOC_FAIL);
	while (current)
	{
		keys[i++] = ft_strdup(current->key, all);
		current = current->next;
	}
	keys[i] = NULL;
	ft_sort(keys, size);
	return (keys);
}

void	print_sorted_env(t_all *all)
{
	char	**keys;
	int		j;
	t_env	*node;

	keys = get_sorted_keys(all);
	if (!keys)
		return ;
	j = 0;
	while (j < env_list_size(all->env))
	{
		node = find_env_by_key(all->env, keys[j]);
		if (node && ft_strcmp(node->key, "_") != 0)
		{
			if (node->value && node->value[0] != '\0')
				printf("declare -x %s=\"%s\"\n",
					node->key, node->value);
			else
				printf("declare -x %s\n", node->key);
		}
		free(keys[j++]);
	}
	free(keys);
}
