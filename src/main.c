#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int g_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
	g_exit_status = 0;
	if (argc == 92989234)
	{
		printf("%s", argv[1]);
	}
	if (g_exit_status == 0)
	{
		printf("%d", g_exit_status);
	}
	t_token	*tokens;
	t_cmd	*cmds;
	char	*input;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (0);
		if (*input)
		{
			add_history(input);
			tokens = lexical(input);
			expander(tokens, envp);
			cmds = parser(tokens, envp);
			while (tokens != NULL)
			{
				printf("-------TOKENS-----\nVERİ: _%s_\nTÜR: _%d_\nRIF: _%d_\n+++++++TOKENS++++++\n", tokens-> value, tokens->type, tokens->rif);
				tokens = tokens -> next;
			}
			while (cmds != NULL)
			{
				int i = 0;
				printf("-------CMDS-----\nINFD: _%d_\nOUTFD: _%d_\n", cmds -> infd, cmds->outfd);
				while (cmds->args[i])
				{
					printf("ARGS[%d] = _%s_\n", i, cmds->args[i]);
					i++;
				}
				printf("+++++++CMDS++++++\n");
				cmds = cmds -> next;
			}
		}
		free(input);
	}
	return (0);
}
