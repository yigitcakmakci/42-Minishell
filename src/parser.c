/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:45:10 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/04/10 09:58:39 by ycakmakc         ###   ########.fr       */
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

void	convert_command(t_token *tokens, t_cmd **cmds)
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
			new_node = init_new_cmd(tokens);
			i = 0;
		}
		if (is_word_token(tokens->type))
			new_node->args[i++] = ft_strdup(tokens->value);
		else if (is_redir_token(tokens->type))
			convert_redirection(&tokens, new_node);
		else if (tokens->type == HEREDOC)
			handle_heredoc(&tokens, new_node);
		else if (tokens->type == PIPE)
			convert_pipe(cmds, &last_cmd, &new_node, i);
		tokens = tokens->next;
	}
	if (new_node)
		convert_pipe(cmds, &last_cmd, &new_node, i);
}

t_cmd	*parser(t_token *tokens, char **envp)
{
	t_cmd	*cmds;
	t_token	*temp_tokens;

	(void)envp;
	cmds = NULL;
	temp_tokens = tokens;
	while (temp_tokens)
	{
		if (temp_tokens->rif == 1)
			join_list(&temp_tokens);
		else
			temp_tokens = temp_tokens->next;
	}
	convert_command(tokens, &cmds);
	return (cmds);
}
