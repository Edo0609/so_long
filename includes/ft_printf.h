/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:03:27 by epenaloz          #+#    #+#             */
/*   Updated: 2023/11/28 19:23:30 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(char const *str, ...);
int		type_check(char c, va_list args, size_t bytes);
int		pf_putchar(char c, int count);
int		pf_putnbr(long n, int count);
int		pf_putstr(char *str, int count);
int		pf_puthex(unsigned long n, int count, int mode);
int		pf_putptr(unsigned long n, int count);

#endif
