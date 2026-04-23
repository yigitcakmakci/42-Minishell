/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:49 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 20:16:49 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

char	*get_env_val(char *var_name, t_shell *shell)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	while (shell->envp[i])
	{
		if (ft_strncmp(var_name, shell->envp[i], len) == 0
			&& shell->envp[i][len] == '=')
			return (gc_strdup(shell->envp[i] + len + 1, &shell->gc));
		i++;
	}
	return (gc_strdup("", &shell->gc));
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
		return (gc_strdup(str, &shell->gc));
	v_name = gc_substr(str, ch_addr + 1, v_end - (ch_addr + 1), &shell->gc);
	val = get_env_val(v_name, shell);
	p[0] = gc_substr(str, 0, ch_addr, &shell->gc);
	p[1] = gc_strdup(str + v_end, &shell->gc);
	p[2] = gc_strjoin(p[0], val, &shell->gc);
	return (gc_strjoin(p[2], p[1], &shell->gc));
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
	char	*tmp_itoa;

	tmp_itoa = ft_itoa(g_exit_status);
	exit_str = gc_strdup(tmp_itoa, &shell->gc);
	free(tmp_itoa);
	prefix = gc_substr(tmp->value, 0, i, &shell->gc);
	suffix = gc_strdup(tmp->value + i + 2, &shell->gc);
	new_val = gc_strjoin(prefix, exit_str, &shell->gc);
	tmp->value = gc_strjoin(new_val, suffix, &shell->gc);
}

void	write_expanded_line(int fd, char *line, t_shell *shell)
{
	char	*expanded;
	int		i;

	expanded = gc_strdup(line, &shell->gc);
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
	free(line);
}
