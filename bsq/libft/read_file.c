/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:12:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/18 17:05:33 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_file(int fd)
{
	char	*temp;
	char	*str;

	temp = get_next_line(fd);
	if (temp == NULL)
		return (NULL);
	str = NULL;
	while (temp != NULL)
	{
		str = ft_re_strjoin(str, temp);
		ft_free(temp);
		if (str == NULL)
			return (NULL);
		temp = get_next_line(fd);
	}
	return (str);
}

char	**str2d_file(int fd)
{
	char	*temp[2];
	char	**str;

	str = ft_calloc(2, sizeof(char *));
	if (str == NULL)
		return (NULL);
	str[0] = get_next_line(fd);
	if (str[0] == NULL)
		return (ft_free(str), NULL);
	temp[0] = get_next_line(fd);
	if (temp[0] == NULL)
		return (ft_free(str[0]), ft_free(str), NULL);
	temp[1] = NULL;
	while (temp[0] != NULL)
	{
		str = str2djoin_and_free(str, temp);
		ft_free(temp[0]);
		if (str == NULL)
			return (NULL);
		temp[0] = get_next_line(fd);
	}
	return (str);
}
