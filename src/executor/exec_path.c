/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 20:32:14 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*check_dirs(char **dirs, char *cmd)
{
	char	*tmp;
	char	*full;
	int		i;

	i = -1;
	while (dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	**dirs;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = env_get(shell->envp, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	res = check_dirs(dirs, cmd);
	free_split(dirs);
	return (res);
}
