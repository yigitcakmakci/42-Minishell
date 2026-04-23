/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:00:00 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/18 17:00:00 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

static void	*register_ptr(void *ptr, t_list **gc)
{
	t_list	*node;

	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(gc, node);
	return (ptr);
}

char	*gc_strdup(const char *s, t_list **gc)
{
	if (!s)
		return (NULL);
	return (register_ptr(ft_strdup(s), gc));
}

char	*gc_substr(char const *s, unsigned int start,
			size_t len, t_list **gc)
{
	return (register_ptr(ft_substr(s, start, len), gc));
}

char	*gc_strjoin(char const *s1, char const *s2, t_list **gc)
{
	return (register_ptr(ft_strjoin(s1, s2), gc));
}

char	*gc_itoa(int n, t_list **gc)
{
	return (register_ptr(ft_itoa(n), gc));
}
