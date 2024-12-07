/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:18:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/05 19:24:11 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		print_nbr(int n);
char	*ft_strchr(const char *str, int c);
int		convert_flag(const char flag, va_list ap);
int		num_flags(const char *str);
int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_error(char *error_mssg);
int		print_str(char *str);
int		print_char(char c);
int		print_hexa(unsigned int n, char *base);
int		print_pointer(void *pointer);
int		print_lhexa(unsigned long num, char *hex);
int		print_unsigned(unsigned int c);

#endif