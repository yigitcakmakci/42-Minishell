/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 20:19:38 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

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

static int	export_one(char *arg, t_shell *shell)
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
		env_set(&shell->envp, arg, NULL, shell);
	else
	{
		*eq = '\0';
		env_set(&shell->envp, arg, eq + 1, shell);
		*eq = '=';
	}
	return (0);
}

static void	sort_env(char **tab, int env_len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < env_len - 1)
	{
		j = 0;
		while (j < env_len - i - 1)
		{
			if (ft_strncmp(tab[j], tab[j + 1], ft_strlen(tab[j]) + 1) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	export_print(char **envp, t_shell *shell)
{
	int		i;
	int		len;
	char	**sorted;
	char	*eq;

	len = 0;
	while (envp[len])
		len++;
	sorted = gc_malloc(sizeof(char *) * (len + 1), &shell->gc);
	i = -1;
	while (++i < len)
		sorted[i] = envp[i];
	sorted[len] = NULL;
	sort_env(sorted, len);
	i = -1;
	while (sorted[++i])
	{
		eq = ft_strchr(sorted[i], '=');
		if (eq)
			printf("declare -x %.*s\"%s\"\n", (int)(eq - sorted[i] + 1),
				sorted[i], eq + 1);
		else
			printf("declare -x %s\n", sorted[i]);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (export_print(shell->envp, shell));
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (export_one(cmd->args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
