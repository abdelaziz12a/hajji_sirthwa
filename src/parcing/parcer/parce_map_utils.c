/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:45:31 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/15 13:38:54 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int only_spaces(char *s)
{
	int i = 0;
	int space = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			space = 1;
		if (s[i] == '\n' && !space)
			return (0);
		i++;
	}
	return (1);
}

int check(int fd)
{
    char *line;
    int result;

	result = 0;
    while ((line = get_next_line(fd)))
    {
        int i = 0;
        while (line[i])
        {
            if (line[i] != ' ' && line[i] != '\n')
            {
                result = 1;
                free_ptr(line);
                return result;
            }
            i++;
        }
        free_ptr(line);
    }
    return (result);
}
int get_cont_line(char *file)
{
	int  fd;
	int  cont = 0;
	char *line;
	int  in_map = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)))
	{
		if (is_map(line) || (in_map && only_spaces(line)))
		{
			in_map = 1;
			cont++;
		}
		else if (in_map && !only_spaces(line))
		{
			if (check(fd))
				return (close(fd), free_ptr(line), -1);
			return (cont > 0 ? cont : -1);
		}
		free_ptr(line);
	}
	close(fd);
	return (cont > 0 ? cont : -1);
}

int	fill(char **map, t_point p, int height, int width)
{
	if (p.x < 0 || p.y < 0 || p.y >= height || p.x >= width)
		return (0);
	if (map[p.y][p.x] == '0' || is_player(map[p.y][p.x]))
		return (1);
	if (map[p.y][p.x] == ' ')
	{
		map[p.y][p.x] = 'V';
		if (fill(map, (t_point){p.x - 1, p.y}, height, width)
			|| fill(map, (t_point){p.x + 1, p.y}, height, width)
			|| fill(map, (t_point){p.x, p.y - 1}, height, width)
			|| fill(map, (t_point){p.x, p.y + 1}, height, width))
			return (1);
	}
	return (0);
}

int	flood_fill(char **map, t_point p, int height, int width)
{
	return (fill(map, p, height, width));
}
