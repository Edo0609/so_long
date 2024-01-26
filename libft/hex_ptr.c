/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:40:16 by epenaloz          #+#    #+#             */
/*   Updated: 2023/11/28 18:45:44 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	pf_puthex(unsigned long n, int count, int mode)
{
	char	*base;
	char	str[25];
	int		i;

	i = 0;
	if (mode == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n == 0)
		count = pf_putchar('0', count);
	else
	{
		while (n != 0)
		{
			str[i++] = base[n % 16];
			n /= 16;
		}
		i--;
		while (i >= 0 && count != -1)
			count = pf_putchar(str[i--], count);
	}
	return (count);
}

int	pf_putptr(unsigned long n, int count)
{
	char	*base;
	char	str[25];
	int		i;

	i = 0;
	base = "0123456789abcdef";
	count = pf_putstr("0x", count);
	if (n == 0 && count != -1)
		count = pf_putchar('0', count);
	else
	{
		while (n != 0)
		{
			str[i++] = base[n % 16];
			n /= 16;
		}
		i--;
		while (i >= 0 && count != -1)
			count = pf_putchar(str[i--], count);
	}
	return (count);
}

/*#include <stdio.h>

int main ()
{
	int	n = 9124824;
	int i;

	i = 0;
	i = pf_puthex(n, i, 0);
	write(1, "\n", 1);
	printf("contador = %d\n", i);
	i = pf_puthex(n, i, 1);
    write(1, "\n", 1);
	printf("contador = %d\n", i);
	i = pf_puthex(n, i, 2);
    write(1, "\n", 1);
	printf("contador = %d\n", i);
	char str[3] = "ho";
	void *str2;
	str2 = str;
	printf("printf og = %p\n", str2);
	i = pf_puthex(str2, i, 2);	

	return (0);
}*/
