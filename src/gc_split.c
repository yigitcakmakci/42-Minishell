/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:00:00 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/18 17:00:00 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static void	register_gc(void *ptr, t_list **gc)
{
	t_list	*node;

	if (!ptr)
		return ;
	node = ft_lstnew(ptr);
	if (!node)
		return ;
	ft_lstadd_back(gc, node);
}

char	**gc_split(char const *s, char c, t_list **gc)
{
	char	**result;
	int		i;

	result = ft_split(s, c);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
		register_gc(result[i++], gc);
	register_gc(result, gc);
	return (result);
}
