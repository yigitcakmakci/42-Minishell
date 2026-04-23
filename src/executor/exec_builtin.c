/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 19:49:46 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "exit", 5) == 0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(shell->envp));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd, shell));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(cmd, shell));
	return (127);
}
