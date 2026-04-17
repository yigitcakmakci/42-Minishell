/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static char	*build_entry(const char *key, const char *val)
{
	char	*tmp;
	char	*out;

	if (!val)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	out = ft_strjoin(tmp, val);
	free(tmp);
	return (out);
}

static char	**grow_env(char **old, char *entry)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (old && old[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
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

void	env_set(char ***envp, const char *key, const char *val)
{
	int		klen;
	int		i;
	char	*entry;

	klen = (int)ft_strlen(key);
	i = 0;
	while ((*envp) && (*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, klen) == 0
			&& ((*envp)[i][klen] == '=' || (*envp)[i][klen] == '\0'))
		{
			if (!val)
				return ;
			entry = build_entry(key, val);
			if (entry)
				free((*envp)[i]), (*envp)[i] = entry;
			return ;
		}
		i++;
	}
	entry = build_entry(key, val);
	if (entry)
		*envp = grow_env(*envp, entry);
}
