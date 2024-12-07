/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:06:28 by ibaby             #+#    #+#             */
/*   Updated: 2024/12/07 03:36:36 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
#define BSQ_H

# include <fcntl.h>
#include <string.h>

# include "libft/libft.h"

# define AND &&
# define OR ||
# define IS ==
# define IS_NOT !=

typedef struct s_obstacle {
	size_t		x;
	size_t		y;
	struct	s_obstacle	*next;
}	t_obstacle;

typedef struct s_square {
	size_t		x;
	size_t		y;
	size_t		size;
}	t_square;

typedef struct s_data {
	t_square	square;
	t_obstacle	*obstacles;
	char		**map;
	size_t		line_len;
	size_t		lines;
	char		empty;
	char		full;
	char		obstacle;
	bool		square_found;
	bool		fatal_error;
}	t_data;

#endif
