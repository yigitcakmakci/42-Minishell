/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 06:51:13 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/23 20:52:16 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <stdlib.h>

static int	heredoc_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	return (1);
}

static int	end_heredoc(int fd, char *in, char *delim)
{
	int	ret;

	ret = 1;
	if (!in && g_exit_status == 130)
		ret = 0;
	else if (!in)
		ret = heredoc_error(delim);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (in)
		free(in);
	return (ret);
}

static int	read_heredoc(int tmp_fd, char *delim, t_shell *shell, int expand)
{
	char	*in;
	int		fd;

	fd = dup(STDIN_FILENO);
	signal_heredoc();
	while (1)
	{
		in = readline("> ");
		if (!in || ft_strncmp(in, delim, ft_strlen(delim) + 1) == 0)
			break ;
		if (expand)
			write_expanded_line(tmp_fd, in, shell);
		else
		{
			ft_putendl_fd(in, tmp_fd);
			free(in);
		}
	}
	return (end_heredoc(fd, in, delim));
}

void	handle_heredoc(t_token **tokens, t_cmd *new_node, t_shell *shell)
{
	int		tmp_fd;
	char	*delimiter;
	int		expand;

	expand = 1;
	if ((*tokens)->next->type == SINGLE_QUOTES
		|| (*tokens)->next->type == DOUBLE_QUOTES)
		expand = 0;
	tmp_fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	delimiter = ft_strdup((*tokens)->next->value);
	if (!read_heredoc(tmp_fd, delimiter, shell, expand))
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

void	convert_redirection(t_token **tokens, t_cmd *new_node, t_shell *shell)
{
	int	flags;

	(void)shell;
	flags = O_CREAT | O_TRUNC | O_RDWR;
	if ((*tokens)->type == RED_IN && new_node->infd > 2)
		close(new_node->infd);
	if (((*tokens)->type == RED_OUT || (*tokens)->type == APPEND)
		&& new_node->outfd > 2)
		close(new_node->outfd);
	if ((*tokens)->type == RED_IN)
		new_node->infd = open((*tokens)->next->value, O_RDONLY, 0777);
	else if ((*tokens)->type == RED_OUT)
		new_node->outfd = open((*tokens)->next->value, flags, 0777);
	else if ((*tokens)->type == APPEND)
		new_node->outfd = open((*tokens)->next->value,
				O_CREAT | O_APPEND | O_WRONLY, 0777);
	*tokens = (*tokens)->next;
}
