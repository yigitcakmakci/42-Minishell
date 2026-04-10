/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:03:50 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/06/25 00:08:13 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_un;
	const unsigned char	*s2_un;
	size_t				i;

	s1_un = (const unsigned char *)s1;
	s2_un = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_un[i] != s2_un[i])
			return (s1_un[i] - s2_un[i]);
		i++;
	}
	return (0);
}
