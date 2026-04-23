/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/24 00:37:18 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

static void	child_cleanup(t_shell *shell, char *path, int code)
{
	free(path);
	gc_free_all(&shell->gc);
	env_free(shell->envp);
	exit(code);
}

static void	child_exec(t_cmd *cmd, int in, int out, t_shell *shell)
{
	char	*path;

	signal_exec();
	setup_child_fds(cmd, in, out);
	if (is_builtin(cmd->args[0]))
		child_cleanup(shell, NULL, exec_builtin(cmd, shell));
	path = find_path(cmd->args[0], shell);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		child_cleanup(shell, NULL, 127);
	}
	execve(path, cmd->args, shell->envp);
	perror(cmd->args[0]);
	child_cleanup(shell, path, 126);
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

static void	parent_close(int *in, int p[2], t_cmd *cmds)
{
	if (*in != 0)
		close(*in);
	if (cmds->next)
	{
		close(p[1]);
		*in = p[0];
	}
}

void	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		p[2];
	int		in;
	pid_t	last;

	in = 0;
	last = -1;
	while (cmds)
	{
		if (cmds->next && pipe(p) < 0)
			return ;
		last = fork();
		if (last == 0 && cmds->next)
			child_exec(cmds, in, p[1], shell);
		else if (last == 0)
			child_exec(cmds, in, 1, shell);
		parent_close(&in, p, cmds);
		cmds = cmds->next;
	}
	g_exit_status = wait_all(last);
	signal_prompt();
}
