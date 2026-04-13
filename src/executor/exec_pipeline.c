/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:47:20 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:05 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int	init_pipeline_vars(t_all *all, t_cmd **cmd, int *prev_fd)
{
	if (!all->cmd->args[0] && all->cmd->redirects->type == HEREDOC)
	{
		cleanup_all_heredoc_fds(all);
		clean_malloc(all);
		return (1);
	}
	*cmd = all->cmd;
	*prev_fd = -1;
	return (0);
}

static int	process_single_cmd(t_cmd *cmd, t_all *all, int *prev_fd, int len)
{
	int		pipefd[2];

	if (process_builtin_cmd(cmd, all, *prev_fd, len))
		return (1);
	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next && pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	process_fork_cmd(cmd, all, prev_fd, pipefd);
	return (0);
}

void	exec_signal_wait(t_all *all)
{
	int	status;

	status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			all->exit_status = WEXITSTATUS(status);
			all->exit_flag = 1;
		}
		else if (WIFSIGNALED(status))
		{
			all->exit_status = 128 + WTERMSIG(status);
			all->exit_flag = 1;
		}
	}
}

int	cmd_len(t_cmd *cmd)
{
	int		len;
	t_cmd	*temp;

	len = 0;
	temp = cmd;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

int	exec(t_all *all)
{
	t_cmd	*cmd;
	int		prev_fd;
	int		len;
	int		is_pipeline;

	if (init_pipeline_vars(all, &cmd, &prev_fd))
		return (0);
	is_pipeline = (cmd && cmd->next != NULL);
	len = cmd_len(cmd);
	while (cmd)
	{
		if (process_single_cmd(cmd, all, &prev_fd, len))
			break ;
		cleanup_heredoc_fds(cmd);
		cmd = cmd->next;
	}
	if (prev_fd != -1)
	{
		close(prev_fd);
		prev_fd = -1;
	}
	exec_signal_wait(all);
	return (all->exit_flag);
}
