/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 20:37:48 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	exec_pipeline(t_cmd *cmds, t_shell *shell);

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;
	int		i;

	while (cmds)
	{
		next = cmds->next;
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
				free(cmds->args[i++]);
			free(cmds->args);
		}
		free(cmds->path);
		if (cmds->infd > 2)
			close(cmds->infd);
		if (cmds->outfd > 2)
			close(cmds->outfd);
		free(cmds);
		cmds = next;
	}
}

/* ──────────────────── Tek komut / built‑in çalıştır ─────────────── */

/*
** Tek komutsa VE built‑in ise parent process'te çalıştır.
** (cd, export, unset gibi built‑in'lerin shell'i etkilemesi gerekir.)
** Yine de infd/outfd yönlendirmesi uygulanır; sonra orijinale döner.
*/
static void	exec_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (cmd->infd != STDIN_FILENO)
		dup2(cmd->infd, STDIN_FILENO);
	if (cmd->outfd != STDOUT_FILENO)
		dup2(cmd->outfd, STDOUT_FILENO);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_putendl_fd("exit", 2);
	g_exit_status = exec_builtin(cmd, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	close_cmd_fds(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->infd > 2)
			close(cmds->infd);
		if (cmds->outfd > 2)
			close(cmds->outfd);
		cmds = cmds->next;
	}
}

void	exec(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		if (cur->infd == -1)
			return ;
		cur = cur->next;
	}
	cur = cmds;
	while (cur && (!cur->args || !cur->args[0]))
		cur = cur->next;
	if (!cur)
		return ;
	if (!cur->next && is_builtin(cur->args[0]))
	{
		exec_single_builtin(cur, shell);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_pipeline(cmds, shell);
}
