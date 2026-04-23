/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:47:23 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/22 20:50:37 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

/*
** gc_malloc: Standart malloc yerine kullanılacak olan sarmalayıcı fonksiyon.
** 1. İstenen boyutta belleği ayırır.
** 2. Ayrılan bu adres için yeni bir bağlı liste düğümü (node) oluşturur.
** 3. Düğümü gc_list isimli ana toplayıcı listeye ekler.
*/
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
