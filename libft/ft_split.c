/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:41:00 by epenaloz          #+#    #+#             */
/*   Updated: 2023/10/17 18:48:18 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	*ft_free_all(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (NULL);
}

static int	assign(char **array, char *str, char delim)
{
	size_t	i;
	size_t	start;
	size_t	pos;

	i = 0;
	start = 0;
	pos = 0;
	while (str[pos] != '\0')
	{
		while (str[pos] == delim)
			pos++;
		start = pos;
		while (str[pos] != delim && str[pos] != '\0')
			pos++;
		if (str[pos] == delim || pos > start)
		{
			array[i] = ft_substr(str, start, pos - start);
			if (array[i] == NULL)
				return (1);
			i++;
		}
	}
	array[i] = NULL;
	return (0);
}

static size_t	count_words(char const *str, char delim)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == delim)
			str++;
		if (*str != '\0' && *str != delim)
			count++;
		while (*str != delim && *str != '\0')
			str++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	if (assign(split, (char *)s, c) == 1)
		return (ft_free_all(split));
	return (split);
}
