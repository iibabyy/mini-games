/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:14:01 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/15 17:31:21 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		check;
	int		temp;

	free((i = 0, check = 0, temp = 0, va_start(ap, str), NULL));
	if (!str)
		return (va_end(ap), -1);
	while (str[i] != '\0')
	{
		while ((str[i] != '%') && (str[i] != '\0'))
		{
			temp = write(1, &str[i++], 1);
			if (temp < 0)
				return (-1);
			check += temp;
		}
		if (str[i] == '\0')
			return (va_end(ap), check);
		temp = convert_flag(str[++i], ap);
		if (temp < 0)
			return (va_end(ap), -1);
		free((check += temp, i++, NULL));
	}
	return (va_end(ap), check);
}

int	convert_flag(const char flag, va_list ap)
{
	if (flag == 'c')
		return (print_char(va_arg(ap, int)));
	else if (flag == 's')
		return (print_str(va_arg(ap, char *)));
	else if (flag == 'p')
		return (print_pointer(va_arg(ap, void *)));
	else if (flag == 'i' || flag == 'd')
		return ((print_nbr(va_arg(ap, int))));
	else if (flag == 'u')
		return ((print_unsigned(va_arg(ap, unsigned int))));
	else if (flag == 'x')
		return ((print_hexa(va_arg(ap, unsigned int), "0123456789abcdef")));
	else if (flag == 'X')
		return ((print_hexa(va_arg(ap, unsigned int), "0123456789ABCDEF")));
	else if (flag == '\0')
		return (-1);
	else if (flag == '%')
		return ((write(1, "%", 1)));
	else
	{
		if ((write(1, "%", 1) + write(1, &flag, 1)) != 2)
			return (-1);
		return (2);
	}
}
