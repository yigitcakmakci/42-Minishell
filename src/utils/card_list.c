/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   card_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:15 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:08:15 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	create_card(t_all *all, char *card)
{
	t_card	*new_card;
	t_card	*current;

	new_card = (t_card *) safe_malloc(all, sizeof(t_card));
	new_card->value = collector_dup(all, card);
	new_card->type = -1;
	new_card->here_flag = 0;
	new_card->next = NULL;
	if (all->card == NULL)
		all->card = new_card;
	else
	{
		current = all->card;
		while (current->next != NULL)
			current = current->next;
		current->next = new_card;
	}
}

void	create_collector(t_all *all, void *address)
{
	t_collector	*new_card;
	t_collector	*current;

	current = all->collector;
	new_card = (t_collector *) ft_calloc(sizeof(t_collector), 1);
	if (new_card == NULL)
		reset_all(all, EXIT_ALLOC_FAIL);
	new_card->value = address;
	new_card->next = NULL;
	if (all->collector == NULL)
		all->collector = new_card;
	else
	{
		current = all->collector;
		while (current->next != NULL)
			current = current->next;
		current->next = new_card;
	}
}

void	*safe_malloc(t_all *all, int size)
{
	char	*str;

	str = ft_calloc(size, 1);
	if (str == NULL)
		reset_all(all, EXIT_ALLOC_FAIL);
	create_collector(all, str);
	return (str);
}

int	clean_malloc(t_all *all)
{
	t_collector	*current;
	t_collector	*temp;

	current = all->collector;
	temp = NULL;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	all->collector = NULL;
	all->card = NULL;
	all->cmd = NULL;
	return (1);
}
