/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:47:23 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/23 22:52:18 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	*gc_malloc(size_t size, t_list **gc_list)
{
	void	*ptr;
	t_list	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(gc_list, new_node);
	return (ptr);
}

void	gc_free_all(t_list **gc_list)
{
	t_list	*tmp;
	t_list	*next;

	if (!gc_list || !*gc_list)
		return ;
	tmp = *gc_list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = next;
	}
	*gc_list = NULL;
}
