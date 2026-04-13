/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:52 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:11:39 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	handle_redir_append(t_redirect *redir, t_cmd *cmd)
{
	redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	if (cmd->redirect_count != 0 && !cmd->args[0])
	{
		close(redir->fd);
		return (0);
	}
	if (dup2(redir->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 for append");
		close(redir->fd);
		return (1);
	}
	close(redir->fd);
	return (0);
}

int	handle_redir_in(t_redirect *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd < 0)
	{
		printf("%s: No such file or directory\n", redir->filename);
		return (1);
	}
	if (dup2(redir->fd, STDIN_FILENO) == -1)
	{
		perror("dup2 for input");
		close(redir->fd);
		return (1);
	}
	close(redir->fd);
	return (0);
}

static int	count_env_vars(t_env *env)
{
	t_env	*current;
	int		count;

	current = env;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(t_env *env_node, t_all *all)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(env_node->key, "=", all);
	result = ft_strjoin(temp, env_node->value, all);
	free(temp);
	return (result);
}

char	**list_to_envp(t_all *all)
{
	t_env	*current;
	char	**envp;
	int		count;
	int		i;

	count = count_env_vars(all->env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		reset_all(all, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	current = all->env;
	i = 0;
	while (i < count)
	{
		envp[i] = create_env_string(current, all);
		current = current->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}
