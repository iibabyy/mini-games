/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:11:07 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/02 09:41:52 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*re_join_get_next_line(int fd, char **str_address)
{
	char	*gnl;

	gnl = get_next_line(fd);
	if (gnl == NULL)
		return (*str_address);
	*str_address = ft_re_strjoin(*str_address, gnl);
	free(gnl);
	return (*str_address);
}
