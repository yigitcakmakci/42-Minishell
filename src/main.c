/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:04 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 21:55:28 by burozdem         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.gc = NULL;
	shell.envp = env_copy(envp, &shell);
	signal_prompt();
	while (1)
	{
		input = readline("minishell:");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			process_input(input, &shell);
		free(input);
	}
	gc_free_all(&shell.gc);
	return (g_exit_status);
}
