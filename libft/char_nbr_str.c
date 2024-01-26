/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_nbr_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:20:17 by epenaloz          #+#    #+#             */
/*   Updated: 2023/11/28 19:20:20 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putchar(char c, int count)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	else
		return (count + 1);
}

int	pf_putnbr(long n, int count)
{
	if (count == -1)
		return (-1);
	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		else
		{
			n *= -1;
			count++;
		}
	}
	if (n > 9 && count != -1)
	{
		count = pf_putnbr(n / 10, count);
		if (count == -1)
			return (count);
		count = pf_putchar(n % 10 + '0', count);
	}
	else if (count != -1)
		count = pf_putchar(n + '0', count);
	return (count);
}

int	pf_putstr(char *str, int count)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		else
		{
			count += 6;
			return (count);
		}
	}
	else
	{
		while (str[i] && count != -1)
		{
			count = pf_putchar(str[i], count);
			i++;
		}
		return (count);
	}
}

/*#include "stdio.h"
#include "stdlib.h"

int	main (int ac, char **av)
{
	int	i;
	char *str = NULL;

	i = 0;
	if (ac >= 2)
		return (1);
	else if (ac == 1)
	{
		i = pf_putnbr(-2147483648, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 11
		i = pf_putnbr(-1, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 13
		i = pf_putnbr(0, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 14
		i = pf_putnbr(2456, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 18
		i = pf_putnbr(2147483647, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 28
		i = pf_putnbr(-9223372036854, i); 
		write(1, "\n", 1);if (write(1, &str[i++], 1) == -1)
                return (-1);
            count++;
		printf("contador = %d\n", i); //contador = 42
		i = pf_putnbr(4294967295, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 52
		i = pf_putnbr(32, i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 54
		i = pf_putstr("holaaa", i);
		write(1, "\n", 1);
		printf("contador = %d\n", i); //contador = 60
		i = pf_putstr(str, i);
        write(1, "\n", 1);
        printf("contador = %d\n", i); //contador = 66
	}
	else if (ac == 2)
	{
		i = pf_putnbr(atoi(av[1]), i);
		write(1, "\n", 1);
		printf("contador = %d\n", i);
	}
	return (0);
}*/
