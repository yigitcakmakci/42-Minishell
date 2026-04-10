/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:11:15 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/06/29 15:50:05 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	n_length(long n)
{
	int	n_len;

	if (n == 0)
		return (1);
	n_len = 0;
	if (n < 0)
		n_len++;
	while (n != 0)
	{
		n /= 10;
		n_len++;
	}
	return (n_len);
}

char	*ft_itoa(int n)
{
	char	*ito_a;
	int		n_len;
	long	n_long;

	n_long = n;
	n_len = n_length(n_long);
	ito_a = malloc((n_len + 1) * sizeof(char));
	if (!ito_a)
		return (NULL);
	ito_a[n_len] = '\0';
	if (n < 0)
	{
		ito_a[0] = '-';
		n_long = -n_long;
	}
	if (n_long == 0)
	{
		ito_a[0] = '0';
	}
	while (n_long > 0)
	{
		ito_a[--n_len] = (n_long % 10) + '0';
		n_long /= 10;
	}
	return (ito_a);
}
