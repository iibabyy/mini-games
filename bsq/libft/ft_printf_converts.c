/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_converts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:58:52 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/14 23:40:24 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int	print_char(char c)
{
	int	check;
	int	temp;

	temp = 0;
	check = 0;
	temp = write(1, &c, 1);
	if (temp < 0)
		return (-1);
	check += temp;
	return (check);
}

int	print_str(char *str)
{
	int	check;
	int	i;

	i = 0;
	check = 0;
	if (!str)
	{
		check = write(1, "(null)", 6);
		if (check < 0)
			return (-1);
		return (check);
	}
	while (str[i])
	{
		if (write(1, &str[i], 1) < 0)
			return (-1);
		check++;
		i++;
	}
	return (check);
}

int	print_nbr(int n)
{
	long	c;
	int		check;
	int		temp;

	free((check = 0, c = (long)n, NULL));
	if (c < 0)
	{
		if (ft_putchar('-') < 0)
			return (-1);
		free(((check++, c = -c), NULL));
	}
	if (c >= 10)
	{
		temp = print_nbr(c / 10);
		if (temp < 0)
			return (-1);
		free((check += temp, temp = print_nbr(c % 10), NULL));
		if (temp < 0)
			return (-1);
		check += temp;
	}
	else if (c <= 9)
		if (check++ == -100 || ft_putchar(c + 48) < 0)
			return (-1);
	return (check);
}

int	print_unsigned(unsigned int c)
{
	int	check;
	int	temp;

	check = 0;
	if (c >= 10)
	{
		temp = print_unsigned(c / 10);
		if (temp < 0)
			return (-1);
		free((check += temp, temp = print_unsigned(c % 10), NULL));
		if (temp < 0)
			return (-1);
		check += temp;
	}
	else if (c <= 9)
		if (check++ == -100 || ft_putchar(c + 48) < 0)
			return (-1);
	return (check);
}

int	print_hexa(unsigned int n, char *hex)
{
	long	num;
	int		check;
	int		temp;

	num = (long)n;
	check = 0;
	temp = 0;
	if (num >= 16)
	{
		temp = print_hexa(num / 16, hex);
		if (temp < 0)
			return (-1);
		check += temp;
		temp = print_hexa(num % 16, hex);
		if (temp < 0)
			return (-1);
		check += temp;
	}
	else if (num < 16)
	{
		if (ft_putchar(hex[num]) < 0)
			return (-1);
		check++;
	}
	return (check);
}
