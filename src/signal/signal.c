/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:13:15 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/22 20:36:57 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

static void	sig_int_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

static void	sig_int_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	signal_heredoc(void)
{
	signal(SIGINT, sig_int_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_prompt(void)
{
	signal(SIGINT, sig_int_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
