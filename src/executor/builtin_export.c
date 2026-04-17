/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	valid_id(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_one(char *arg, char ***envp)
{
	char	*eq;

	if (!valid_id(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
		env_set(envp, arg, NULL);
	else
	{
		*eq = '\0';
		env_set(envp, arg, eq + 1);
		*eq = '=';
	}
	return (0);
}

static int	export_print(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, char ***envp)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (export_print(*envp));
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (export_one(cmd->args[i], envp))
			ret = 1;
		i++;
	}
	return (ret);
}
