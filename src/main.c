/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:04 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/13 00:00:00 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	g_exit_status = 0;

static void	process_input(char *input, char ***my_env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(input);
	tokens = lexical(input);
	if (!tokens)
		return ;
	expander(tokens, *my_env);
	cmds = parser(tokens, *my_env);
	free_token_list(tokens);
	if (!cmds)
		return ;
	exec(cmds, my_env);
	free_cmds(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = env_copy(envp);
	signal_prompt();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			process_input(input, &my_env);
		free(input);
	}
	env_free(my_env);
	return (g_exit_status);
}
