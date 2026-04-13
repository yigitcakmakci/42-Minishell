/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:39 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:40 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

char	*ft_strdup(const char *s1, t_all *all)
{
	int		i;
	int		size;
	char	*s2;

	i = 0;
	size = ft_strlen(s1);
	s2 = malloc((size + 1) * sizeof(char));
	if (!s2)
		reset_all(all, EXIT_ALLOC_FAIL);
	while (s2 && size > i)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2, t_all *all)
{
	int		i;
	int		len1;
	int		len2;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
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
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_all *all)
{
	size_t	i;
	size_t	l;
	char	*sb;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	if (start > l)
		len = 0;
	else if (l < len + start)
		len = l - start;
	sb = (char *)malloc ((len * sizeof(char)) + 1);
	if (!sb)
		reset_all(all, EXIT_ALLOC_FAIL);
	while (len > i && s[i + start])
	{
		sb[i] = s[i + start];
		i++;
	}
	sb[i] = '\0';
	return (sb);
}

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n, t_all *all)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = count_digits(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		reset_all(all, EXIT_ALLOC_FAIL);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
