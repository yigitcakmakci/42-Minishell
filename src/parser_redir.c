/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:04:17 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/03/31 16:12:38 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <stdlib.h>

/*
** Ctrl+C gelince g_exit_status=130 → 0 döner (iptal).
** Normal bitiş (delimiter veya Ctrl+D) → 1 döner.
*/
static int	read_heredoc(int tmp_fd, char *delimiter)
{
	char	*input;

	signal_heredoc();
	while (1)
	{
		input = readline("> ");
		if (g_exit_status == 130)
		{
			free(input);
			return (0);
		}
		if (!input)
			break ;
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1) != 0)
		{
			ft_putendl_fd(input, tmp_fd);
			free(input);
		}
		else
		{
			free(input);
			break ;
		}
	}
	return (1);
}

void	handle_heredoc(t_token **tokens, t_cmd *new_node)
{
	int		tmp_fd;
	char	*delimiter;

	tmp_fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	delimiter = ft_strdup((*tokens)->next->value);
	if (!read_heredoc(tmp_fd, delimiter))
	{
		close(tmp_fd);
		unlink(".heredoc_tmp");
		free(delimiter);
		new_node->infd = -1;
		*tokens = (*tokens)->next;
		signal_prompt();
		return ;
	}
	close(tmp_fd);
	new_node->infd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	free(delimiter);
	*tokens = (*tokens)->next;
}

void	convert_redirection(t_token **tokens, t_cmd *new_node)
{
	int	flags;

	flags = O_CREAT | O_TRUNC | O_RDWR;
	if ((*tokens)->type == RED_IN)
		new_node->infd = open((*tokens)->next->value, O_RDONLY, 0777);
	else if ((*tokens)->type == RED_OUT)
		new_node->outfd = open((*tokens)->next->value, flags, 0777);
	else if ((*tokens)->type == APPEND)
		new_node->outfd = open((*tokens)->next->value,
				O_CREAT | O_APPEND | O_WRONLY, 0777);
	else if ((*tokens)->type == HEREDOC)
		new_node->outfd = open((*tokens)->next->value,
				O_CREAT | O_APPEND | O_WRONLY, 0777);
	*tokens = (*tokens)->next;
}
