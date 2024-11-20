/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:12:03 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:12:03 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	while (*s)
	{
		if (*s != c && start == 0)
		{
			i++;
			start = 1;
		}
		else if (*s == c)
			start = 0;
		s++;
	}
	return (i);
}

static int	word_size(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*build_str(char const *s, unsigned int start, unsigned int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(((end - start) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str_split;
	size_t	i;
	size_t	start;
	int		word;

	start = 0;
	word = 0;
	i = 0;
	str_split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !str_split)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			start = i;
			i += word_size(&s[i], c);
			str_split[word] = build_str(s, start, i);
			word++;
		}
	}
	str_split[word] = NULL;
	return (str_split);
}
