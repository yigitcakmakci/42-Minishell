/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 23:38:43 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*cd_target(t_cmd *cmd, t_shell *shell)
{
	char	*home;
	char	*rest;

	if (!cmd->args[1])
		return (env_get(shell->envp, "HOME"));
	if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		return (env_get(shell->envp, "OLDPWD"));
	if (cmd->args[1][0] == '~')
	{
		home = env_get(shell->envp, "HOME");
		if (!home)
			return (cmd->args[1]);
		rest = cmd->args[1] + 1;
		if (*rest == '\0')
			return (home);
		return (gc_strjoin(home, rest, &shell->gc));
	}
	return (cmd->args[1]);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target;
	char	*old;
	char	cwd[4096];

	target = cd_target(cmd, shell);
	if (!target)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	old = env_get(shell->envp, "PWD");
	if (old)
		env_set(&shell->envp, "OLDPWD", old, shell);
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(target);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->envp, "PWD", cwd, shell);
	return (0);
}

static int	is_numeric(char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
	{
		has_digit = 1;
		i++;
	}
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (has_digit && s[i] == '\0')
		return (1);
	return (0);
}

static void	exit_cleanup(t_shell *shell)
{
	gc_free_all(&shell->gc);
	if (shell->input)
		free(shell->input);
	rl_clear_history();
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	code;

	if (!cmd->args[1])
	{
		exit_cleanup(shell);
		exit(g_exit_status);
	}
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_cleanup(shell);
		exit(2);
	}
	if (cmd->args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	code = ft_atoi(cmd->args[1]);
	exit_cleanup(shell);
	exit((unsigned char)code);
}
