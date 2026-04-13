/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:57 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:46 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expend_join(char *s1, char *s2, t_all *all)
{
	int		i;
	int		len1;
	int		len2;
	char	*dst;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = malloc(((len1 + len2) * sizeof(char)) + 1);
	if (!dst)
		reset_all(all, EXIT_ALLOC_FAIL);
	while (i < len1)
	{
		dst[i] = s1[i];
		i++;
	}
	while (i < (len1 + len2))
	{
		dst[i] = s2[i - len1];
		i++;
	}
	dst[i] = '\0';
	free(s1);
	free(s2);
	return (dst);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	byte;
	char	*x;

	i = 0;
	byte = nmemb * size;
	if (size && (byte / size != nmemb))
		return (0);
	x = (char *)malloc(byte);
	if (!x)
		return (0);
	while (byte > 0)
	{
		x[i] = 0;
		i++;
		byte--;
	}
	return ((void *)x);
}

int	ft_isalnum(int c)
{
	if ((c > 47 && c < 58) || (c > 96 && c < 123) || (c > 64 && c < 91)
		|| (c == '_'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
