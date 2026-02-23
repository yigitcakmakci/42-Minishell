#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	if (argc == 92989234)
	{
		printf("%s", argv[1]);
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
			tokens = lexical(input);
			expander(tokens, envp);
			while (tokens != NULL)
			{
				printf("-------TOKENS-----\nVERİ: %s\nTÜR: %d\n", tokens-> value, tokens->type );
				tokens = tokens -> next;
			}
			printf("girilen komut : %s\n", input);
		}
		free(input);
	}
	return (0);
}


