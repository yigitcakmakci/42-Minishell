/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 20:22:31 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static void	free_partial(char **copy, int i)
{
	while (i > 0)
		free(copy[--i]);
	free(copy);
}

char	**env_copy(char **envp, t_shell *shell)
{
	char	**copy;
	int		len;
	int		i;

	len = 0;
	while (envp && envp[len])
		len++;
	copy = gc_malloc(sizeof(char *) * (len + 1), &shell->gc);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (free_partial(copy, i), NULL);
		ft_lstadd_back(&shell->gc, ft_lstnew(copy[i]));
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	env_free(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

char	*env_get(char **envp, const char *key)
{
	int	klen;
	int	i;

	if (!envp || !key)
		return (NULL);
	klen = (int)ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, klen) == 0 && envp[i][klen] == '=')
			return (envp[i] + klen + 1);
		i++;
	}
	return (NULL);
}

void	env_unset(char ***envp, const char *key)
{
	int	i;
	int	j;
	int	klen;

	if (!envp || !*envp || !key)
		return ;
	klen = (int)ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, klen) == 0
			&& ((*envp)[i][klen] == '=' || (*envp)[i][klen] == '\0'))
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}
