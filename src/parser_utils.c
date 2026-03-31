/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:07 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/03/31 16:12:05 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	is_word_token(t_token_type type)
{
	if (type == WORD || type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
		return (1);
	return (0);
}

t_cmd	*init_new_cmd(t_token *tokens)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->infd = 0;
	new_node->outfd = 1;
	new_node->next = NULL;
	new_node->args = malloc(sizeof(char *) * (count_cmds(tokens) + 1));
	return (new_node);
}

void	convert_pipe(t_cmd **cmds, t_cmd **last_cmd, t_cmd **new_node, int i)
{
	(*new_node)->args[i] = NULL;
	if (!*cmds)
		*cmds = *new_node;
	else
		(*last_cmd)->next = *new_node;
	*last_cmd = *new_node;
	*new_node = NULL;
}
