/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:58 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 20:40:02 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

static int	handle_list(t_token *tokens, char *input)
{
	if (!handle_pipe(tokens))
		return (0);
	if (!handle_redirection(tokens))
		return (0);
	if (!handle_quotes(input))
		return (0);
	return (1);
}

static int	process_token(t_token **tokens, char *input, int i, t_shell *shell)
{
	if (input[i] == 34)
		return (add_word_to_list(tokens, &input[i], DOUBLE_QUOTES, shell));
	if (input[i] == 39)
		return (add_word_to_list(tokens, &input[i], SINGLE_QUOTES, shell));
	if (is_word(input[i]))
		return (add_word_to_list(tokens, &input[i], WORD, shell));
	if (input[i] == '<' && input[i + 1] == '<')
		return (add_word_to_list(tokens, &input[i], HEREDOC, shell));
	if (input[i] == '<')
		return (add_word_to_list(tokens, &input[i], RED_IN, shell));
	if (input[i] == '>' && input[i + 1] == '>')
		return (add_word_to_list(tokens, &input[i], APPEND, shell));
	if (input[i] == '>')
		return (add_word_to_list(tokens, &input[i], RED_OUT, shell));
	if (input[i] == '|')
		return (add_word_to_list(tokens, &input[i], PIPE, shell));
	return (1);
}

t_token	*lexical(char	*input, t_shell	*shell)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		i += process_token(&tokens, input, i, shell);
	}
	if (!handle_list(tokens, input))
	{
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}
