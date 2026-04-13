/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:55 by burozdem          #+#    #+#             */
/*   Updated: 2026/02/24 21:46:55 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static void	handle_pipe_parent(t_cmd *cmd, int *prev_fd, int pipefd[2])
{
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (cmd->next)
	{
		*prev_fd = pipefd[0];
	}
	else
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
	}
}

int	process_builtin_cmd(t_cmd *cmd, t_all *all, int prev_fd, int len)
{
	if (!cmd->args[0])
	{
		handle_redirections(cmd);
		return (1);
	}
	if ((is_built(cmd->args[0]) && cmd->next == NULL)
		|| (len == 1 && ft_strcmp(cmd->args[0], "exit") == 0))
	{
		exec_builtin_single(cmd, all, prev_fd);
		return (1);
	}
	return (0);
}

void	exec_parent_process(t_cmd *cmd, t_all *all, int *prev_fd, pid_t pid)
{
	int	status;

	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next == NULL)
	{
		waitpid(pid, &status, 0);
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

void	fork_fail(t_all *all, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	perror("fork");
	wait_forks(all);
}

void	process_fork_cmd(t_cmd *cmd, t_all *all, int *prev_fd, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	signal_switch(2);
	if (pid == -1)
	{
		fork_fail(all, prev_fd, pipefd);
		return ;
	}
	else if (pid == 0)
		exec_child_process(cmd, all, *prev_fd, pipefd);
	else
	{
		set_pid(pid, all);
		exec_parent_process(cmd, all, prev_fd, pid);
		handle_pipe_parent(cmd, prev_fd, pipefd);
	}
}
