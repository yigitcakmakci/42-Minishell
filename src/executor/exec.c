/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/13 00:00:00 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	exec_pipeline(t_cmd *cmds, char ***envp);

/* ──────────────────────── Bellek temizleme ───────────────────────── */

/*
** Parser'ın oluşturduğu t_cmd listesini free'ler.
** args dizisini ve path string'ini serbest bırakır.
** infd / outfd'yi kapatır (0 ve 1 dışı fd'ler parser'da open() ile açılmıştı).
*/
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
static void	exec_single_builtin(t_cmd *cmd, char ***envp)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (cmd->infd != STDIN_FILENO)
		dup2(cmd->infd, STDIN_FILENO);
	if (cmd->outfd != STDOUT_FILENO)
		dup2(cmd->outfd, STDOUT_FILENO);
	g_exit_status = exec_builtin(cmd, envp);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

/*
** Genel giriş noktası.
**   – args[0] yoksa boş komut → atla.
**   – Tek built‑in → parent'ta çalıştır.
**   – Diğer her şey (tek external ya da pipeline) → exec_pipeline.
*/
void	exec(t_cmd *cmds, char ***envp)
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
		exec_single_builtin(cur, envp);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_pipeline(cmds, envp);
}
