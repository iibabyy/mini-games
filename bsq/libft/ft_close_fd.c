/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:22:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/16 17:11:52 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_close(int *fd)
{
	if (*fd == -1 || *fd == STDIN_FILENO || *fd == STDOUT_FILENO
		|| *fd == STDERR_FILENO)
		return (EXIT_FAILURE);
	if (close(*fd) == -1)
		return (EXIT_FAILURE);
	*fd = -1;
	return (EXIT_SUCCESS);
}
