/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:18:35 by epenaloz          #+#    #+#             */
/*   Updated: 2023/10/13 19:51:05 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))
		|| ((c >= 48) && (c <= 57)))
		return (1);
	else
		return (0);
}
