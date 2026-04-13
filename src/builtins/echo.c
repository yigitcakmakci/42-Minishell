/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:09 by burozdem          #+#    #+#             */
/*   Updated: 2026/02/26 19:50:59 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"
#include <stdio.h>

static void	print_echo_args(char **args, int start)
{
	while (args[start])
	{
		printf("%s", args[start]);
		if (args[start + 1])
			printf(" ");
		start++;
	}
}

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_echo_flags(char **args, int *newline)
{
	int	i;

	i = 1;
	*newline = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		*newline = 0;
		i++;
	}
	return (i);
}

int	ft_echo(t_all *all, t_cmd *cmd)
{
	int	i;
	int	newline;

	(void)all;
	if (!cmd->args || !cmd->args[0])
	{
		printf("\n");
		return (0);
	}
	i = parse_echo_flags(cmd->args, &newline);
	if (!cmd->args[i])
	{
		if (newline)
			printf("\n");
		return (0);
	}
	print_echo_args(cmd->args, i);
	if (newline)
		printf("\n");
	return (0);
}
