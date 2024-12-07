/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:04:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/12/07 20:16:21 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	get_infos(char *line, t_data *data)
{
	data->lines = ft_atoi(line);
	while (*line >= '0' AND *line <= '9')
		line++;
	if (ft_strlen(line) < 3)
		return (free(line), 1);
	data->empty = *line;
	data->obstacle = *(line + 1);
	data->full = *(line + 2);
	return (free(line), 0);
}

int	add_obstacle(size_t i, size_t j, t_data *data)
{
	t_obstacle	*new_obstacle;
	t_obstacle	*tmp;

	new_obstacle = malloc(sizeof(t_square));
	if (new_obstacle IS NULL)
		return (data->fatal_error = true, 1);
	new_obstacle->y = i;
	new_obstacle->x = j;
	new_obstacle->next = NULL;
	if (data->obstacles IS NULL)
		data->obstacles = new_obstacle;
	else
	{
		tmp = data->obstacles;
		while (tmp->next IS_NOT NULL)
			tmp = tmp->next;
		tmp->next = new_obstacle;
	}
	return (0);
}

int	check_line(char *line, size_t i, size_t len, t_data *data)
{
	size_t	j;

	j = 0;
	if (line[len - 1] IS_NOT '\n')
		return (dprintf(2, "no end of line\n"), 1);
	else
		line[len - 1] = '\0';
	while (line[j])
	{
		if (line[j] IS_NOT data->empty AND line[j] IS_NOT data->obstacle)
			return (1);
		else if (line[j] IS data->obstacle)
			add_obstacle(i, j, data);
		j++;
	}
	return (0);
}

int	get_lines(t_data *data, int fd)
{
	size_t		i;
	long long	len;
	char		*line;

	i = 0;
	len = -1;
	while (i < data->lines)
	{
		line = get_next_line(fd);
		if (line IS NULL)
			return (1);
		if (len IS -1)
			len = ft_strlen(line);
		else if ((size_t)len IS_NOT ft_strlen(line))
			return (1);
		if (check_line(line, i, len, data) IS 1)
			return (1);
		data->map[i] = line;
		i++;
	}
	data->map[i] = NULL;
	data->line_len = len;
	return (0);
}

int	check_square_size(t_square *square, t_data *data)
{
	if (square->x + square->size >= data->line_len)
		return (1);
	if (square->y + square->size >= data->lines)
		return (1);
	return (0);
}

long long	get_obstacle_count(long long x, long long y, t_data *data)
{
	long long	obstacle_count;
	t_obstacle	*obstacle;

	obstacle_count = 0;
	obstacle = data->obstacles;
	while (obstacle IS_NOT NULL)
	{
		if ((long long)obstacle->x <= x AND (long long)obstacle->y <= y)
			obstacle_count++;
		obstacle = obstacle->next;
	}
	return (obstacle_count);
}

/*	formula to know if there is an obstacle in the square*/
bool	is_obstacle_in(size_t top_left, size_t top_right, size_t bottom_left, size_t bottom_right)
{
	return ((bottom_right - bottom_left - top_right + top_left) > 0);
}

int	check_square_obstacle(t_square *square, t_data *data)
{
	long long	top_left_obstacle_count;
	long long	top_right_obstacle_count;
	long long	bottom_left_obstacle_count;
	long long	bottom_right_obstacle_count;

	top_left_obstacle_count = get_obstacle_count(square->x - 1, square->y - 1, data);
	top_right_obstacle_count = get_obstacle_count(square->x + square->size, square->y - 1, data);
	bottom_left_obstacle_count = get_obstacle_count(square->x - 1, square->y + square->size, data);
	bottom_right_obstacle_count = get_obstacle_count(square->x + square->size, square->y + square->size, data);

	return (is_obstacle_in(top_left_obstacle_count, top_right_obstacle_count, bottom_left_obstacle_count, bottom_right_obstacle_count));
}

int	check_square(t_square *square, t_data *data)
{
	if (data->square_found AND square->size <= data->square.size)
		return (1);
	if (check_square_size(square, data) IS 1)
		return (1);
	if (check_square_obstacle(square, data) IS 1)
		return (1);
	ft_memcpy(&data->square, square, sizeof(t_square));
	data->square_found = true;
	return (0);
}

int	bsq(t_data *data)
{
	t_square	square;

	square.x = 0;
	square.y = 0;
	square.size = 1;
	while (square.x + square.size < data->lines && square.y < data->lines)
	{
		square.x = 0;
		while (square.x + square.size < data->line_len && square.x < data->line_len)
		{
			while (check_square(&square, data) IS 0)
				square.size++;
			square.x++;
		}
		square.y++;
	}
	return (0);
}

int	get_map(t_data *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd IS -1)
		return (data->fatal_error = true, perror(file), 1);
	line = get_next_line(fd);
	if (line IS NULL)
		return (close(fd), 1);
	if (get_infos(line, data) IS 1)
		return (close(fd), 1);
	data->map = malloc(sizeof(char *) * (data->lines + 1));
	if (data->map IS NULL)
		return (close(fd), data->fatal_error = true, 1);
	if (get_lines(data, fd) IS 1)
		return (close(fd), 1);
	close(fd);
	if (bsq(data) IS 1)
		return (1);
	return (0);
}

void	fill_map(t_data *data)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < data->lines)
	{
		x = -1;
		while (++x < data->line_len)
		{
			if (y >= data->square.y AND x >= data->square.x AND y <= data->square.y + data->square.size AND x <= data->square.x + data->square.size)
				data->map[y][x] = data->full;
		}
	}
}

void	print_map(t_data *data)
{
	size_t	i;

	i = -1;
	fill_map(data);
	while (++i < data->lines)
	{
		printf("%s\n", data->map[i]);
	}
}

int main(int ac, char **av) {
	t_data	data;
	
	if (ac < 2)
		return (dprintf(2, "usage: ./bsq [file]\n"), 1);
	while (*++av) {
		memset(&data, 0, sizeof(t_data));
		if (get_map(&data, *av) IS 1)
		{
			free_2d_str(data.map);
			if (data.fatal_error)
				return (dprintf(2, "fatal error\n"), 1);
			dprintf(2, "map error\n");
			continue;
		}
		else if (data.square_found IS false) {
			free_2d_str(data.map);
			dprintf(2, "no square found\n");
			continue ;
		}
		print_map(&data);
		if (av[1])
			printf("\n");
		free_2d_str(data.map);
	}
	return (0);
}
