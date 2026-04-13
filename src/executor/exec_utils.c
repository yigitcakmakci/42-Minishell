/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:47:30 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:11 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>

char	*here_expand(char *str, t_all *all)
{
	int		i;
	char	open_quote;
	char	*new_str;

	i = 0;
	open_quote = '\0';
	while (str[i])
	{
		open_quote = is_char_quote(str[i], open_quote);
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			new_str = found_dollar(str, i, all);
			free(str);
			str = ft_strdup(new_str, all);
			i = -1;
		}
		i++;
	}
	return (str);
}

void	handle_output_redirects(t_redirect *redir, t_cmd *cmd)
{
	if (redir->type == R_OUT)
	{
		if (handle_redir_out(redir, cmd))
			exit(EXIT_FAILURE);
	}
	else if (redir->type == R_APPEND)
	{
		if (handle_redir_append(redir, cmd))
			exit(EXIT_FAILURE);
	}
}

void	set_pid(pid_t pid, t_all *all)
{
	t_clean_pid	*new_node;

	new_node = NULL;
	if (pid > 0)
	{
		new_node = safe_malloc(all, sizeof(t_clean_pid));
		if (!new_node)
			return ;
		new_node->pid = pid;
		new_node->next = all->clean_pids;
		all->clean_pids = new_node;
	}
}

void	wait_forks(t_all *all)
{
	t_clean_pid	*current;
	int			status;

	status = 0;
	current = all->clean_pids;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			all->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			all->exit_status = 128 + WTERMSIG(status);
		current = current->next;
	}
	all->clean_pids = NULL;
	reset_all(all, 1);
}
