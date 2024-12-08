/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:04:49 by ibaby             #+#    #+#             */
/*   Updated: 2024/12/08 15:54:44 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	count_obstacle(int y, int x, t_data *data)
{
	int	count;

	count = (data->map[y][x] == data->obstacle);
	if (y > 0) {
		count += data->obstacle_map[y - 1][x];
	}
	if (x > 0) {
		count += data->obstacle_map[y][x - 1];
	}
	if (x > 0 AND y > 0) {
		count -= data->obstacle_map[y - 1][x - 1];
	}
	return (count);
}

int	create_int_matrix(t_data *data)
{
	int	x;
	int	y;
	
	data->obstacle_map = malloc(sizeof(int *) * (data->lines + 1));
	if (data->obstacle_map == NULL)
		return (1);
	y = 0;
	while (y < data->lines)
	{
		x = 0;
		data->obstacle_map[y] = malloc(sizeof(int) * data->line_len);
		if (data->obstacle_map[y] == NULL)
			return (1);
		while (x < data->line_len)
		{
			data->obstacle_map[y][x] = count_obstacle(y, x, data);
			x++;
		}
		y++;
	}
	data->obstacle_map[y] = NULL;
	return (0);
}

int	get_infos(char *line, t_data *data)
{
	data->lines = ft_atoi(line);
	while (*line >= '0' AND *line <= '9')
		line++;
	if (ft_strlen(line) < 3)
		return (1);
	data->empty = *line;
	data->obstacle = *(line + 1);
	data->full = *(line + 2);
	return (0);
}

int	add_obstacle(int i, int j, t_data *data)
{
	t_obstacle	*new_obstacle;
	t_obstacle	*tmp;

	new_obstacle = malloc(sizeof(t_obstacle));
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

int	check_line(char *line, int len, t_data *data)
{
	int	j;

	j = 0;
	if (line[len - 1] IS_NOT '\n')
		return (dprintf(2, "no end of line\n"), 1);
	else
		line[len - 1] = '\0';
	while (line[j])
	{
		if (line[j] IS_NOT data->empty AND line[j] IS_NOT data->obstacle)
			return (1);
		// else if (line[j] IS data->obstacle)
		// 	add_obstacle(i, j, data);
		j++;
	}
	return (0);
}

int	get_lines(t_data *data, int fd)
{
	int			i;
	int			len;
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
		if (check_line(line, len, data) IS 1)
			return (1);
		data->map[i] = line;
		i++;
	}
	data->map[i] = NULL;
	data->line_len = len - 1;
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

int	get_test_obstacle_count(int x, int y, t_data *data)
{
	int	obstacle_count;
	t_obstacle	*obstacle;

	obstacle_count = 0;
	obstacle = data->obstacles;
	while (obstacle IS_NOT NULL && (obstacle->x <= x OR obstacle->y <= y))
	{
		if (obstacle->x <= x AND obstacle->y <= y)
			obstacle_count++;
		obstacle = obstacle->next;
	}
	return (obstacle_count);
}

int	get_obstacle_count(int x, int y, t_data *data)
{
	return (data->obstacle_map[y][x]);
}

/*	formula to know if there is an obstacle in the square	*/
bool	is_obstacle_in(int top_left, int top_right, int bottom_left, int bottom_right)
{
	return ((bottom_right - bottom_left - top_right + top_left) > 0);
}

int	obstacle_at(int x, int y, t_data *data)
{
	if (x < 0 OR y < 0)
		return (0);
	return (data->obstacle_map[y][x]);
}

int	check_square_obstacle(t_square *square, t_data *data)
{
	int	top_left;
	int	top_right;
	int	bottom_left;
	int	bottom_right;

	top_left = obstacle_at(square->x - 1, square->y - 1, data);
	top_right = obstacle_at(square->x + square->size, square->y - 1, data);
	bottom_left = obstacle_at(square->x - 1, square->y + square->size, data);
	bottom_right = obstacle_at(square->x + square->size, square->y + square->size, data);

	return (is_obstacle_in(top_left, top_right, bottom_left, bottom_right));
}

int	check_square(t_square *square, t_data *data)
{
	if (data->square_found AND square->size < data->square.size)
		return (1);
	if (check_square_size(square, data) IS 1)
		return (1);
	if (check_square_obstacle(square, data) IS 1)
		return (1);
	ft_memcpy(&data->square, square, sizeof(t_square));
	data->square_found = true;
	return (0);
}

int	next_pos(t_square *square, t_data *data)
{
	int	x;
	int	y;
	int	square_y;

	square_y = square->y;
	x = square->x + square->size + 2;
	while (--x >= square->x) {
		y = square_y + square->size + 2;
		while (--y >= square_y) {
			if (y < data->lines && data->map[y][x] == data->obstacle)
				return (x + 1);
		}
	}
	return (square->x + 1);
	// if (x < data->line_len) {
	// 	while (y < data->lines && data->map[y][x] != data->obstacle && y < square->y + square->size + 1)
	// 		++y;
	// 	if (y < data->lines && data->map[y][x] == data->obstacle)
	// 		return (x);
	// }
	// x = square->x;
	// y = square->y + square->size + 1;
	// if (y < data->lines) {
	// 	while (x < data->line_len && data->map[y][x] != data->obstacle && x < square->x + square->size + 1)
	// 		++x;
	// 	if (x < data->line_len && data->map[y][x] == data->obstacle)
	// 		return (x);
	// }
	return (square->x + 1);
}

int	bsq(t_data *data)
{
	t_square	square;

	square.y = 0;
	square.size = 1;
	while (square.y + square.size < data->lines)
	{
		square.x = 0;
		while (square.x + square.size < data->line_len)
		{
			while (check_square(&square, data) IS 0)
				square.size++;
			square.x = next_pos(&square, data);
			// ++square.x;
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
		return (free(line), close(fd), 1);
	free(line);
	data->map = malloc(sizeof(char *) * (data->lines + 1));
	if (data->map IS NULL)
		return (close(fd), data->fatal_error = true, 1);
	if (get_lines(data, fd) IS 1)
		return (close(fd), 1);
	close(fd);
	create_int_matrix(data);
	// exit(EXIT_SUCCESS);
	if (bsq(data) IS 1)
		return (1);
	return (0);
}

void	fill_map(t_data *data)
{
	int	x;
	int	y;

	y = data->square.y;
	while (y <= data->square.y + data->square.size)
	{
		x = data->square.x;
		while (x <= data->square.x + data->square.size)
		{
			data->map[y][x] = data->full;
			x++;
		}
		y++;
	}
}

void	print_map(t_data *data)
{
	int	i;

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
