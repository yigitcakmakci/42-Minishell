/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/13 00:00:00 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

/*
** Prompt modunda Ctrl+C basılınca:
**   – mevcut satırı sil, yeni prompt göster
**   – g_exit_status = 130 (bash standardı: 128 + SIGINT)
** rl_replace_line / rl_on_new_line / rl_redisplay çağrıları
** readline kütüphanesinin bu amaçla sağladığı signal‑safe fonksiyonlardır.
*/
static void	sig_int_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

/*
** Heredoc modu: Ctrl+C basılınca readline'ı hemen bitir ve g_exit_status=130.
** rl_done = 1 → readline mevcut buffer'ı (boş string) döndürür;
** read_heredoc bunu g_exit_status üzerinden iptal olarak yorumlar.
*/
static void	sig_int_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
}

/*
** Heredoc okuma modu: SIGINT → readline'ı kes  |  SIGQUIT → yoksay
** handle_heredoc başında çağrılır, bitince signal_prompt() ile onarılır.
*/
void	signal_heredoc(void)
{
	signal(SIGINT, sig_int_heredoc);
	signal(SIGQUIT, SIG_IGN);
}


/*
** Prompt modu:  SIGINT → satırı sıfırla  |  SIGQUIT → yoksay
** Her yeni prompt döngüsünde çağrılır.
*/
void	signal_prompt(void)
{
	signal(SIGINT, sig_int_prompt);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Çalıştırma modu (child process içinde çağrılır):
** Sinyalleri varsayılana döndür; böylece Ctrl+C/\ child'ı doğrudan keser.
*/
void	signal_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
