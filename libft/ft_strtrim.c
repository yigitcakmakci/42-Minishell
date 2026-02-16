/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:12:47 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/06/29 16:22:17 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	in_s1_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_s1_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && in_s1_set(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	trimmed = (char *)malloc(end - start + 2);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start <= end)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}
