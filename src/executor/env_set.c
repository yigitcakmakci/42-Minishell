/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/24 00:37:18 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static char	*build_entry(const char *key, const char *val, t_shell *shell)
{
	char	*tmp;
	char	*result;

	(void)shell;
	if (!val)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, val);
	free(tmp);
	return (result);
}

static char	**grow_env(char **old, char *entry, t_shell *shell)
{
	char	**new_env;
	int		len;
	int		i;

	(void)shell;
	len = 0;
	while (old && old[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (old);
	i = 0;
	while (i < len)
	{
		new_env[i] = old[i];
		i++;
	}
	new_env[len] = entry;
	new_env[len + 1] = NULL;
	free(old);
	return (new_env);
}

static int	update_existing(char **envp, const char *key, const char *val,
		t_shell *shell)
{
	int		i;
	int		klen;
	char	*entry;

	(void)shell;
	klen = ft_strlen(key);
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], key, klen) == 0
			&& (envp[i][klen] == '=' || envp[i][klen] == '\0'))
		{
			if (!val)
				return (1);
			entry = build_entry(key, val, NULL);
			if (entry)
			{
				free(envp[i]);
				envp[i] = entry;
			}
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
	entry = build_entry(key, val, NULL);
	if (entry)
		*envp = grow_env(*envp, entry, shell);
}
