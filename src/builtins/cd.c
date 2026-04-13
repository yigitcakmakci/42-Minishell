/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:01 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:07 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

static char	*resolve_cd_path(t_cmd *cmd)
{
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		return (getenv("HOME"));
	return (cmd->args[1]);
}

static int	print_cd_home_error(void)
{
	printf("cd: HOME not set\n");
	return (1);
}

static void	update_env_pwd(t_all *all, char *oldpwd)
{
	char	cwd[1024];

	if (oldpwd)
		add_or_update_env(all, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		add_or_update_env(all, "PWD", cwd);
}

int	ft_cd(t_all *all, t_cmd *cmd)
{
	char	*path;
	char	cwd[1024];
	char	*oldpwd;

	if (cmd->args[1] && cmd->args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	path = resolve_cd_path(cmd);
	if (!path)
		return (print_cd_home_error());
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("cd: getcwd"), 1);
	oldpwd = ft_strdup(cwd, all);
	if (chdir(path) != 0)
	{
		free(oldpwd);
		printf("cd: No such file or directory\n");
		return (1);
	}
	update_env_pwd(all, oldpwd);
	free(oldpwd);
	return (0);
}
