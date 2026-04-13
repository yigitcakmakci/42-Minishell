/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:47:01 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:50 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <readline/readline.h>
#include <unistd.h>
#include <signal.h>

int	handle_heredoc_eof(char *eof)
{
	write(STDERR_FILENO, "minishell: warning: here-document ", 34);
	write(STDERR_FILENO, "delimited by end-of-file (wanted `", 35);
	write(STDERR_FILENO, eof, ft_strlen(eof));
	write(STDERR_FILENO, "')\n", 3);
	return (0);
}

static char	*expand_heredoc_line(char *line, t_all *all, int quoted)
{
	char	*expanded;
	char	*line_copy;

	if (quoted)
		expanded = ft_strdup(line, all);
	else
	{
		line_copy = ft_strdup(line, all);
		expanded = here_expand(line_copy, all);
	}
	return (expanded);
}

static int	write_line_to_pipe(char *line, int write_fd)
{
	if (write_fd >= 0)
	{
		if (write(write_fd, line, ft_strlen(line)) == -1)
			return (-1);
		if (write(write_fd, "\n", 1) == -1)
			return (-1);
	}
	return (0);
}

int	process_heredoc_line(char *line, char *eof,
			t_all *all, int *quoted_and_pipe)
{
	char	*expanded_line;
	int		ret;

	if (ft_strcmp(line, eof) == 0)
	{
		free(line);
		return (1);
	}
	expanded_line = expand_heredoc_line(line, all, quoted_and_pipe[0]);
	free(line);
	if (!expanded_line)
		return (-1);
	ret = write_line_to_pipe(expanded_line, quoted_and_pipe[1]);
	free(expanded_line);
	if (ret == -1)
		return (-1);
	return (0);
}

int	read_heredoc_input(int *quoted_and_pipe, char *delimiter, t_all *all)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			handle_heredoc_eof(delimiter);
			break ;
		}
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
			return (130);
		}
		ret = process_heredoc_line(line, delimiter, all, quoted_and_pipe);
		if (ret == 1)
			break ;
		else if (ret == -1)
			return (1);
	}	
	return (0);
}
