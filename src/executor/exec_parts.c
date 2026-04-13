/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:47:13 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:57 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

static void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static void	exec_with_redirect(t_cmd *cmd, t_all *all)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	handle_redirections(cmd);
	if (exec_builtin(all, cmd, 1))
		all->exit_status = EXIT_FAILURE;
	restore_fds(saved_stdin, saved_stdout);
}

void	exec_builtin_single(t_cmd *cmd, t_all *all, int prev_fd)
{
	int	saved_stdin;

	saved_stdin = -1;
	if (prev_fd != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->redirects)
		exec_with_redirect(cmd, all);
	else
	{
		if (exec_builtin(all, cmd, 1))
		{
			all->exit_status = EXIT_FAILURE;
			all->exit_flag = 1;
		}
	}
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

void	directory_checker(t_cmd *cmd, t_all *all)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) == 0)
	{
		printf("minishell: %s: is a directory\n", cmd->args[0]);
		reset_all(all, 126);
	}
	printf("%s: No such file or directory\n", cmd->args[0]);
	reset_all(all, 127);
}

void	path_error(t_cmd *cmd, t_all *all)
{
	if (cmd->args[0][0] == '/' && cmd->args[0][1] == '\0')
	{
		printf("minishell: %s: is a directory\n", cmd->args[0]);
		reset_all(all, 126);
	}
	else if ((cmd->args[0][0] == '.' && cmd->args[0][1] == '/'
		&& cmd->args[0][2] == '\0'))
	{
		printf("minishell: %s: is a directory\n", cmd->args[0]);
		reset_all(all, 126);
	}
	else if (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0')
	{
		printf("minishell: %s: filename argument required\n", cmd->args[0]);
		reset_all(all, 2);
	}
	else
	{
		printf("%s: command not found\n", cmd->args[0]);
		reset_all(all, EXIT_COMMAND_NOT_FOUND);
	}
}
