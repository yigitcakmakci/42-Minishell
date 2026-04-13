/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_clean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:58 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:47 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h>

void	cleanup_heredoc_fds(t_cmd *cmd)
{
	t_redirect	*redir;

	if (!cmd)
		return ;
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->fd > 0)
		{
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}

void	cleanup_all_heredoc_fds(t_all *all)
{
	t_cmd	*cmd;

	if (!all || !all->cmd)
		return ;
	cmd = all->cmd;
	while (cmd)
	{
		cleanup_heredoc_fds(cmd);
		cmd = cmd->next;
	}
}
