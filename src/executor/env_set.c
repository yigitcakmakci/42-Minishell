/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 20:40:41 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static char	*build_entry(const char *key, const char *val, t_shell *shell)
{
	char	*tmp;

	if (!val)
		return (gc_strdup(key, &shell->gc));
	tmp = gc_strjoin(key, "=", &shell->gc);
	if (!tmp)
		return (NULL);
	return (gc_strjoin(tmp, val, &shell->gc));
}

static char	**grow_env(char **old, char *entry, t_shell *shell)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (old && old[len])
		len++;
	new_env = gc_malloc(sizeof(char *) * (len + 2), &shell->gc);
	i = 0;
	while (i < len)
	{
		new_env[i] = old[i];
		i++;
	}
	new_env[len] = entry;
	new_env[len + 1] = NULL;
	return (new_env);
}

static int	update_existing(char **envp, const char *key, const char *val,
		t_shell *shell)
{
	int		i;
	int		klen;
	char	*entry;

	klen = ft_strlen(key);
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], key, klen) == 0
			&& (envp[i][klen] == '=' || envp[i][klen] == '\0'))
		{
			if (!val)
				return (1);
			entry = build_entry(key, val, shell);
			if (entry)
				envp[i] = entry;
			return (1);
		}
	}
	return (0);
}

void	env_set(char ***envp, const char *key, const char *val, t_shell *shell)
{
	char	*entry;

	if (update_existing(*envp, key, val, shell))
		return ;
	entry = build_entry(key, val, shell);
	if (entry)
		*envp = grow_env(*envp, entry, shell);
}
