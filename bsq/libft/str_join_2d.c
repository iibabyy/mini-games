/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:28:32 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/16 17:01:38 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_join_2d(char **str_2d, char *sep)
{
	char	*str;
	int		i;

	if (str_2d == NULL)
		return (NULL);
	str = NULL;
	i = -1;
	while (str_2d[++i] != NULL)
	{
		if (i != 0)
		{
			str = ft_re_strjoin(str, sep);
			if (str == NULL)
				return (NULL);
		}
		str = ft_re_strjoin(str, str_2d[i]);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}
