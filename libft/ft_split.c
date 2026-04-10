/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:20:33 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/07/05 17:33:31 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_count(const char *s, char c)
{
	int		in_word;
	int		w_count;

	in_word = 0;
	w_count = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			w_count++;
			in_word = 1;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (w_count);
}

static char	*get_word(const char *start, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_style(char **result, int last_index)
{
	while (last_index--)
	{
		free(result[last_index]);
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	const char		*start;
	int				len;
	int				j;

	j = 0;
	result = malloc((word_count(s, c) + 1) * sizeof(char *));
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		start = s;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
			result[j++] = get_word(start, len);
		if (result[j - 1] == NULL)
			return (free_style(result, j), NULL);
	}
	result[j] = NULL;
	return (result);
}
