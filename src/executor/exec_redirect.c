/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:47:23 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:08 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h>
#include <stdio.h>

int	handle_redir_out(t_redirect *redir, t_cmd *cmd)
{
	redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	if (cmd->redirect_count != 0 && !cmd->args[0])
	{
		close(redir->fd);
		return (0);
	}
	if (dup2(redir->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 for output");
		close(redir->fd);
		return (1);
	}
	close(redir->fd);
	return (0);
}

static void	handle_input_redirects(t_redirect *redir, int *heredoc_done)
{
	if (redir->type == R_IN)
	{
		if (handle_redir_in(redir))
			return ;
		*heredoc_done = 1;
	}
	else if (redir->type == HEREDOC)
	{
		if (*heredoc_done && redir->fd > 0)
		{
			close(redir->fd);
		}
		else if (redir->fd > 0)
		{
			if (dup2(redir->fd, STDIN_FILENO) == -1)
			{
				perror("dup2 for heredoc");
				exit(EXIT_FAILURE);
			}
			close(redir->fd);
			*heredoc_done = 1;
		}
	}
}

static void	process_single_redirect(t_redirect *redir,
	int *heredoc_done, t_cmd *cmd)
{
	if (redir->type == R_OUT || redir->type == R_APPEND)
		handle_output_redirects(redir, cmd);
	else if (redir->type == R_IN || redir->type == HEREDOC)
		handle_input_redirects(redir, heredoc_done);
}

void	handle_redirections(t_cmd *cmd)
{
	t_redirect	*redir;
	int			heredoc_done;

	heredoc_done = 0;
	redir = cmd->redirects;
	while (redir)
	{
		process_single_redirect(redir, &heredoc_done, cmd);
		redir = redir->next;
	}
}
