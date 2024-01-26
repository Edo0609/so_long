/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:20:54 by epenaloz          #+#    #+#             */
/*   Updated: 2023/09/25 19:27:11 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned char	*fake_isspace(unsigned char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned char	*ptr;
	int				sign;
	int				num;

	sign = 1;
	ptr = (unsigned char *)str;
	num = 0;
	ptr = fake_isspace(ptr);
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		num = num * 10 + *ptr - '0';
		ptr++;
	}
	return (num * sign);
}
