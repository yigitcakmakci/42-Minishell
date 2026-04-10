/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:44:58 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/10 09:58:39 by ycakmakc         ###   ########.fr       */
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

static int	process_token(t_token **tokens, char *input, int i)
{
	if (input[i] == 34)
		return (add_word_to_list(tokens, &input[i], DOUBLE_QUOTES));
	if (input[i] == 39)
		return (add_word_to_list(tokens, &input[i], SINGLE_QUOTES));
	if (is_word(input[i]))
		return (add_word_to_list(tokens, &input[i], WORD));
	if (input[i] == '<' && input[i + 1] == '<')
		return (add_word_to_list(tokens, &input[i], HEREDOC));
	if (input[i] == '<')
		return (add_word_to_list(tokens, &input[i], RED_IN));
	if (input[i] == '>' && input[i + 1] == '>')
		return (add_word_to_list(tokens, &input[i], APPEND));
	if (input[i] == '>')
		return (add_word_to_list(tokens, &input[i], RED_OUT));
	if (input[i] == '|')
		return (add_word_to_list(tokens, &input[i], PIPE));
	return (1);
}

t_token	*lexical(char *input)
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
		i += process_token(&tokens, input, i);
	}
	if (!handle_list(tokens, input))
	{
		printf("\n<<<<<<<GEÇERSİZ ARGÜMAN>>>>>>>>\n");
		return (NULL);
	}
	return (tokens);
}
