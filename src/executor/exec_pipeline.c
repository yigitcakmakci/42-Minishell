/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
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
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static void	child_exec(t_cmd *cmd, int in, int out, char ***envp)
{
	char	*path;

	signal_exec();
	if (in != 0)
		dup2(in, 0), close(in);
	if (out != 1)
		dup2(out, 1), close(out);
	if (cmd->infd > 2)
		dup2(cmd->infd, 0), close(cmd->infd);
	if (cmd->outfd > 2)
		dup2(cmd->outfd, 1), close(cmd->outfd);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, envp));
	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->args, *envp);
	ft_putendl_fd(strerror(errno), 2);
	exit(126);
}

static int	wait_all(pid_t last)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last)
			last_status = status;
		pid = wait(&status);
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (1);
}

void	exec_pipeline(t_cmd *cmds, char ***envp)
{
	int		p[2];
	int		in;
	pid_t	last;
	t_cmd	*cur;

	in = 0;
	last = -1;
	cur = cmds;
	while (cur)
	{
		if (cur->next && pipe(p) < 0)
			return ;
		last = fork();
		if (last == 0)
			child_exec(cur, in, cur->next ? p[1] : 1, envp);
		if (in != 0)
			close(in);
		if (cur->next)
			close(p[1]), in = p[0];
		cur = cur->next;
	}
	g_exit_status = wait_all(last);
	signal_prompt();
}
