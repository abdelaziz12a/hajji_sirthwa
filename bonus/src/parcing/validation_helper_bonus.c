/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helper_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:56:15 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 22:25:42 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int get_h(char**map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int map_char(char c, t_config *data, int x, int y)
{
	if (c == 'D')
	{
		if (parcing_dor(data, y, x))
			return(1);
		else
			return (0);
	}
	else if (c == '0' || c == '1' || c == ' ' || is_player(c))
		return(0);
	else 
		return (1);
}

void assing_position(int y, int x, t_config *data)
{
	data->player_x = x;
	data->player_y = y;
}
int	fill_inside(char **map, t_point p, t_config *data)
{
	if (p.x < 0 || p.y < 0 || p.y >= data->y_rows || p.x >= data->x_cols)
		return (1);
	if (map[p.y][p.x] == '1' || map[p.y][p.x] == 'V')
		return (0);
	if (map[p.y][p.x] == ' ')
		return (1);
	if (is_player(map[p.y][p.x]))
		assing_position(p.y, p.x, data);
	map[p.y][p.x] = 'V';
	if (fill_inside(map, (t_point){p.x + 1, p.y}, data))
		return (1);
	if (fill_inside(map, (t_point){p.x - 1, p.y}, data))
		return (1);
	if (fill_inside(map, (t_point){p.x, p.y + 1}, data))
		return (1);
	if (fill_inside(map, (t_point){p.x, p.y - 1}, data))
		return (1);
	return (0);
}

int check_inside(char **map, t_config *data)
{
	t_point p;
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_player(map[i][j]) || map[i][j] == 'D')
			{
				p.x = j;
				p.y = i;
				if (fill_inside(map, p, data))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
