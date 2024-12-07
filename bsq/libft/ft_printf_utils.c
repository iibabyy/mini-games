/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:18:10 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/27 16:23:40 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar(char c)
{
	if (write(1, &c, 1) < 0)
	{
		return (-1);
	}
	return (1);
}

int	print_lhexa(unsigned long int num, char *hex)
{
	int	check;
	int	temp;

	check = 0;
	temp = 0;
	if (num >= 16)
	{
		temp = print_lhexa(num / 16, hex);
		if (temp < 0)
			return (-1);
		check += temp;
		temp = print_lhexa(num % 16, hex);
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

int	print_pointer(void *pointer)
{
	unsigned long	p;
	int				check;
	int				temp;

	if (pointer == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	temp = 0;
	p = (unsigned long)pointer;
	check = write(1, "0x", 2);
	if (check < 0)
		return (-1);
	temp = print_lhexa(p, "0123456789abcdef");
	if (temp < 0)
		return (-1);
	check += temp;
	return (check);
}
