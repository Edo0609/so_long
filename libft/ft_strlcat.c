/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:56:49 by epenaloz          #+#    #+#             */
/*   Updated: 2023/10/13 20:08:36 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	while (src[i] != '\0')
		i++;
	while (dst[j] != '\0')
		j++;
	if (j >= dstsize || dstsize == 0)
		return (dstsize + i);
	else
	{
		while (src[k] != '\0' && j < dstsize - 1)
		{
			dst[j] = src[k];
			j++;
			k++;
		}
		dst[j] = '\0';
		return (j + (i - k));
	}
}
