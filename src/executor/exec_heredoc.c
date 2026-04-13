/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:47:05 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:54 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h>
#include <stdio.h>

static int	handle_heredoc_error(int heredoc_pipe[2], int ret)
{
	if (heredoc_pipe[0] != -1)
		close(heredoc_pipe[0]);
	if (heredoc_pipe[1] != -1)
		close(heredoc_pipe[1]);
	return (ret);
}

int	search_here_flag(t_card *card, char *eof)
{
	t_card	*current;

	current = card;
	while (current)
	{
		if (current->here_flag == 1 && ft_strcmp(current->value, eof) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

static int	process_single_heredoc(t_redirect *redir, t_all *all)
{
	int		heredoc_pipe[2];
	int		quoted_and_pipe[2];
	int		ret;

	if (pipe(heredoc_pipe) == -1)
	{
		perror("pipe for heredoc");
		return (1);
	}
	quoted_and_pipe[1] = heredoc_pipe[1];
	quoted_and_pipe[0] = search_here_flag(all->card, redir->filename);
	ret = read_heredoc_input(quoted_and_pipe, redir->filename, all);
	if (ret != 0)
		return (handle_heredoc_error(heredoc_pipe, ret));
	close(heredoc_pipe[1]);
	redir->fd = heredoc_pipe[0];
	return (0);
}

int	around_redirects(t_redirect *redir, t_redirect *last, t_all *all, int ret)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			ret = process_single_heredoc(redir, all);
			if (ret != 0)
				return (ret);
			if (redir != last && redir->fd > 0)
			{
				close(redir->fd);
				redir->fd = -1;
			}
		}
		redir = redir->next;
	}
	return (0);
}

int	handle_all_heredocs_for_cmd(t_cmd *cmd, t_all *all)
{
	t_redirect	*redir;
	t_redirect	*last_heredoc;
	int			ret;

	ret = 0;
	redir = cmd->redirects;
	last_heredoc = NULL;
	while (redir)
	{
		if (redir->type == HEREDOC)
			last_heredoc = redir;
		redir = redir->next;
	}
	if (!last_heredoc)
		return (0);
	redir = cmd->redirects;
	ret = around_redirects(redir, last_heredoc, all, ret);
	if (ret != 0)
		return (ret);
	return (0);
}
