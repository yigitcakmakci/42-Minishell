#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int main(void)
{
	char	*input;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (0);
		if (*input)
		{
			add_history(input);
			lexical(input);
			printf("girilen komut : %s\n", input);
		}
		free(input);
	}
	return (0);
}


