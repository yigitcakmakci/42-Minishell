/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 00:51:35 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	builtin_pwd(void)
{
	char	buf[4096];

	if (!getcwd(buf, sizeof(buf)))
		return (1);
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
		env_unset(&shell->envp, cmd->args[i++]);
	return (0);
}
