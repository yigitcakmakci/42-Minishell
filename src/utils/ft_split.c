/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burozdem <burozdem@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:08:31 by burozdem          #+#    #+#             */
/*   Updated: 2026/04/13 14:12:37 by burozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

static void	free_malloc(char **f, int k)
{
	while (k-- > 0)
		free(f[k]);
}

static int	word_count(const char *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		while (s[a] == c && s[a] != '\0')
			a++;
		if (s[a] != c && s[a] != '\0')
			b++;
		while (s[a] != c && s[a] != '\0')
			a++;
	}
	return (b);
}

static int	word_len(const char *s, char c)
{
	int	a;

	a = 0;
	while (s[a] && s[a] != c)
		a++;
	return (a);
}

static int	word_save(char **f, char const *s, char c, int i)
{
	int	b;
	int	k;

	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			b = word_len(&s[i], c);
			f[k] = (char *)malloc(sizeof(char) * (b + 1));
			if (!f[k])
			{
				free_malloc(f, k);
				return (1);
			}
			b = 0;
			while (s[i] && s[i] != c)
				f[k][b++] = s[i++];
			f[k++][b] = '\0';
		}
		else
			i++;
	}
	f[k] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c, t_all *all)
{
	char	**f;
	int		a;
	int		i;

	if (!s[0])
		return (NULL);
	i = 0;
	f = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!f)
		reset_all(all, EXIT_ALLOC_FAIL);
	a = word_save(f, s, c, i);
	if (a != 0)
	{
		free(f);
		reset_all(all, EXIT_ALLOC_FAIL);
	}
	return (f);
}
