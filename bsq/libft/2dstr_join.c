/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dstr_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 03:35:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/18 17:57:08 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	join2d(char **join, char **str1, char **str2);

char	**str2d_join(char **str1, char **str2)
{
	char	**join;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	join = ft_malloc(sizeof(char *)
			* (ft_strlen_2d(str1) + ft_strlen_2d(str2) + 1));
	if (join == NULL)
		return (NULL);
	if (join2d(join, str1, str2) == EXIT_FAILURE)
		return (NULL);
	return (join);
}

char	**str2djoin_and_free(char **str1, char **str2)
{
	char	**join;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	join = ft_malloc(sizeof(char *)
			* (ft_strlen_2d(str1) + ft_strlen_2d(str2) + 1));
	if (join == NULL)
		return (free_2d_str(str1), NULL);
	if (join2d(join, str1, str2) == EXIT_FAILURE)
		return (free_2d_str(str1), NULL);
	return (free_2d_str(str1), join);
}

static int	join2d(char **join, char **str1, char **str2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str1[++i] != NULL)
	{
		join[++j] = ft_strdup(str1[i]);
		if (join[j] == NULL)
			return (free_2d_str(join), EXIT_FAILURE);
	}
	i = -1;
	while (str2[++i] != NULL)
	{
		join[++j] = ft_strdup(str2[i]);
		if (join[j] == NULL)
			return (free_2d_str(join), EXIT_FAILURE);
	}
	join[++j] = NULL;
	return (EXIT_SUCCESS);
}