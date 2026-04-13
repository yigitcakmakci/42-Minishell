/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:46:33 by burozdem          #+#    #+#             */
/*   Updated: 2026/02/26 20:03:51 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <unistd.h> // getcwd için gerekli
#include <stdio.h>  // printf ve perror için

int	ft_pwd(t_all *all, t_cmd *cmd)
{
	char	cwd[1024];

	(void)all;
	(void)cmd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd error");
		return (1);
	}
}
