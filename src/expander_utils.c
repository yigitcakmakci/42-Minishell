/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:49 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 20:38:00 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

char	*get_env_val(char *var_name, t_shell *shell)
{
	int		i;
	int		len;
	char	**envp;

	envp = shell->envp;
	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(var_name, envp[i], len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*sandwich(char *str, int ch_addr, t_shell *shell)
{
	int		v_end;
	char	*v_name;
	char	*val;
	char	*p[3];

	v_end = ch_addr + 1;
	while (str[v_end] && (ft_isalnum(str[v_end]) || str[v_end] == '_'))
		v_end++;
	if (v_end - (ch_addr + 1) == 0)
		return (ft_strdup(str));
	v_name = ft_substr(str, ch_addr + 1, v_end - (ch_addr + 1));
	val = get_env_val(v_name, shell);
	p[0] = ft_substr(str, 0, ch_addr);
	p[1] = ft_strdup(str + v_end);
	p[2] = ft_strjoin(p[0], val);
	str = ft_strjoin(p[2], p[1]);
	free(v_name);
	free(val);
	free(p[0]);
	free(p[1]);
	free(p[2]);
	return (str);
}

int	count_quotes(char *str)
{
	int		i;
	int		count;
	char	q;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			q = str[i++];
			count += 2;
			while (str[i] && str[i] != q)
				i++;
			if (!str[i])
				break ;
		}
		i++;
	}
	return (count);
}

void	expand_exit_status(t_token *tmp, int i, t_shell *shell)
{
	char	*exit_str;
	char	*prefix;
	char	*suffix;
	char	*new_val;

	(void)shell;
	exit_str = ft_itoa(g_exit_status);
	prefix = ft_substr(tmp->value, 0, i);
	suffix = ft_strdup(tmp->value + i + 2);
	new_val = ft_strjoin(prefix, exit_str);
	free(prefix);
	prefix = ft_strjoin(new_val, suffix);
	free(new_val);
	free(exit_str);
	free(suffix);
	free(tmp->value);
	tmp->value = prefix;
}

void	write_expanded_line(int fd, char *line, t_shell *shell)
{
	char	*expanded;
	int		i;

	expanded = ft_strdup(line);
	i = 0;
	while (expanded && expanded[i])
	{
		if (expanded[i] == '$' && expanded[i + 1]
			&& (ft_isalnum(expanded[i + 1]) || expanded[i + 1] == '_'))
		{
			expanded = sandwich(expanded, i, shell);
			continue ;
		}
		i++;
	}
	ft_putendl_fd(expanded, fd);
	free(expanded);
	free(line);
}
