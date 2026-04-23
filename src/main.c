/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:04 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/23 21:15:09 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	g_exit_status = 0;

static void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(input);
	tokens = lexical(input, shell);
	if (!tokens)
		return ;
	expander(tokens, shell);
	cmds = parser(tokens, shell);
	if (!cmds)
		return ;
	exec(cmds, shell);
	close_cmd_fds(cmds);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->gc = NULL;
	shell->input = NULL;
	shell->envp = env_copy(envp, shell);
	signal_prompt();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		input = readline("minishell:");
		shell.input = input;
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			process_input(input, &shell);
		free(input);
		shell.input = NULL;
	}
	gc_free_all(&shell.gc);
	rl_clear_history();
	return (g_exit_status);
}
