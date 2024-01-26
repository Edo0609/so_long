/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:28:43 by epenaloz          #+#    #+#             */
/*   Updated: 2023/10/16 18:08:00 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*destiny;
	unsigned char	*source;

	destiny = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (destiny == source)
		return (dst);
	else if (destiny < source || destiny >= source + len)
	{
		while (len--)
			*destiny++ = *source++;
	}
	else
	{
		destiny += len;
		source += len;
		while (len--)
			*(--destiny) = *(--source);
	}
	return (dst);
}
