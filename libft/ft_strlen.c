/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:34:50 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/06/25 00:35:57 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

size_t	ft_strlen(const char *s)
{
	size_t	str_len;

	str_len = 0;
	while (s[str_len])
	{
		str_len++;
	}
	return (str_len);
}
