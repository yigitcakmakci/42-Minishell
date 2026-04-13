/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:00 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:21 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <readline/readline.h>

void	sig_cat_quit(int sig)
{
	g_signal = sig;
	printf("Quit (the core has been removed)\n");
}

void	sig_prompt(int sig)
{
	g_signal = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_exc(int sig)
{
	rl_event_hook = NULL;
	g_signal = sig;
	printf("\n");
}

void	sig_heredoc(int sig)
{
	g_signal = sig;
	rl_done = 1;
}
