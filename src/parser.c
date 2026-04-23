/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:10 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/22 20:41:16 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	count_cmds(t_token *tokens)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (is_word_token(temp->type))
			i++;
		temp = temp->next;
	}
	return (i);
}

static int	is_redir_token(t_token_type type)
{
	if (type == RED_IN || type == RED_OUT || type == APPEND)
		return (1);
	return (0);
}

static void	handle_word(t_cmd *node, t_token *tok, int *i)
{
	if (tok->type != WORD || tok->value[0])
		node->args[(*i)++] = ft_strdup(tok->value);
}

void	convert_command(t_token *tokens, t_cmd **cmds, t_shell *shell)
{
	t_cmd	*new_node;
	t_cmd	*last_cmd;
	int		i;

	new_node = NULL;
	last_cmd = NULL;
	while (tokens)
	{
		if (!new_node)
		{
			new_node = init_new_cmd(tokens, shell);
			i = 0;
		}
		if (is_word_token(tokens->type))
			handle_word(new_node, tokens, &i);
		else if (is_redir_token(tokens->type))
			convert_redirection(&tokens, new_node, shell);
		else if (tokens->type == HEREDOC)
			handle_heredoc(&tokens, new_node, shell);
		else if (tokens->type == PIPE)
			convert_pipe(cmds, &last_cmd, &new_node, i);
		tokens = tokens->next;
	}
	if (new_node)
		convert_pipe(cmds, &last_cmd, &new_node, i);
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;
	t_token	*temp_tokens;

	cmds = NULL;
	temp_tokens = tokens;
	while (temp_tokens)
	{
		if (temp_tokens->rif == 1)
			join_list(&temp_tokens, shell);
		else
			temp_tokens = temp_tokens->next;
	}
	convert_command(tokens, &cmds, shell);
	return (cmds);
}
