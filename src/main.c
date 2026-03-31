/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:04 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/03/31 16:15:49 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int			g_exit_status = 0;

static void	debug_prints(t_token *tokens, t_cmd *cmds)
{
	int	i;

	while (tokens)
	{
		printf("-------TOKENS-----\nVERİ: _%s_\nTÜR: _%d_\nRIF: _%d_\n",
			tokens->value, tokens->type, tokens->rif);
		printf("+++++++TOKENS++++++\n");
		tokens = tokens->next;
	}
	while (cmds)
	{
		i = 0;
		printf("-------CMDS-----\nINFD: _%d_\nOUTFD: _%d_\n", cmds->infd,
			cmds->outfd);
		while (cmds->args && cmds->args[i])
		{
			printf("ARGS[%d] = _%s_\n", i, cmds->args[i]);
			i++;
		}
		printf("+++++++CMDS++++++\n");
		cmds = cmds->next;
	}
}

static void	process_input(char *input, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(input);
	tokens = lexical(input);
	if (!tokens)
		return ;
	expander(tokens, envp);
	cmds = parser(tokens, envp);
	debug_prints(tokens, cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			process_input(input, envp);
		free(input);
	}
	return (0);
}
