/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:02:58 by epenaloz          #+#    #+#             */
/*   Updated: 2023/10/13 20:46:46 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	int_size(long n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 9)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static void	rev_str(char *str)
{
	int		start;
	int		end;
	char	temp;

	end = ft_strlen(str) - 1;
	start = 0;
	if (str[start] == '-')
		start++;
	while (end > start)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

static void	c_assign(char	*str, long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		str[i] = '0';
		i++;
	}
	else
	{
		if (n < 0)
		{
			n *= -1;
			str[i] = '-';
			i++;
		}
		while (n > 0)
		{
			str[i] = (n % 10) + 48;
			i++;
			n /= 10;
		}
	}
	str[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*n_str;
	int		size;

	size = int_size((long)n);
	n_str = (char *)malloc(sizeof(char) * size + 1);
	if (n_str == NULL)
		return (NULL);
	c_assign(n_str, (long)n);
	rev_str(n_str);
	return (n_str);
}
