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
	char	*input;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (0);
		if (*input)
		{
			add_history(input);
			printf("TEST96\n");
			tokens = lexical(input);
			printf("TEST97\n");
			expander(tokens, envp);
			printf("TEST98\n");
			parser(tokens, envp);
			printf("TEST99\n");
			while (tokens != NULL)
			{
				printf("-------TOKENS-----\nVERİ: _%s_\nTÜR: _%d_\nRIF: _%d_\n+++++++TOKENS++++++\n", tokens-> value, tokens->type, tokens->rif );
				tokens = tokens -> next;
			}
			printf("girilen komut : %s\n", input);
		}
		free(input);
	}
	return (0);
}
