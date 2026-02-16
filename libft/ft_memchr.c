/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:51:05 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/06/25 00:03:20 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*hold;
	unsigned char		target;

	i = 0;
	hold = (const unsigned char *)s;
	target = (unsigned char)c;
	while (i < n)
	{
		if (hold[i] == target)
			return ((void *)&hold[i]);
		i++;
	}
	return (NULL);
}
