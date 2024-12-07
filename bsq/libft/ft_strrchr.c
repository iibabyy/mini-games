/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:34:44 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/16 17:01:38 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*retval;

	i = 0;
	retval = (char *)str + i;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
		{
			retval = (char *)str + i;
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		retval = (char *)str + i;
		return (retval);
	}
	if (*retval != (unsigned char)c)
		return (retval = 0);
	return (retval);
}
