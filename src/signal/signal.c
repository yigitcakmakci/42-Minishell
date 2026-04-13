/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:08 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:24 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

int	g_signal = 0;

int	do_nothing(void)
{
	return (0);
}

void	sig_pipe(int sig)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
	g_signal = sig;
}

void	signal_switch(int status)
{
	g_signal = 0;
	if (status == 1)
	{
		rl_event_hook = NULL;
		signal(SIGINT, sig_prompt);
		signal(SIGPIPE, sig_pipe);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 2)
	{
		rl_event_hook = NULL;
		signal(SIGINT, sig_exc);
		signal(SIGPIPE, sig_pipe);
		signal(SIGQUIT, sig_cat_quit);
	}
	else if (status == 3)
	{
		rl_event_hook = do_nothing;
		signal(SIGPIPE, sig_pipe);
		signal(SIGINT, sig_heredoc);
	}
}
