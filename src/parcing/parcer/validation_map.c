/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:34:46 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 16:12:17 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char *get_value(char *line, int i)
{
	int begin;
	int end;

	i += 3;
	while (is_space(line[i]))
		i++;
	begin = i;
	while (line[i] && line[i] != '\n')
		i++;
	end = i;
	while (end > begin && is_space(line[end - 1]))
		end--;
	return (gc_strndup(line, begin, end));
}

int	check_tex(t_config *data)
{
	int	fd;

	fd = open(data->tex.no, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->tex.so, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->tex.we, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->tex.ea, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int assign_tex(char *start,char *line, int i, t_config *data)
{
	char *value;
	
	if (!start)
		return (1);
	value = get_value(line , i);
	if (!value)
		return (1);
	if (!ft_strcmp(start, "NO "))
		data->tex.no = value;
	if (!ft_strcmp(start, "SO "))
		data->tex.so = value;
	if (!ft_strcmp(start, "WE "))
		data->tex.we = value;
	if (!ft_strcmp(start, "EA "))
		data->tex.ea = value;
	return (0);
}

int is_player(char c)
{
	return (c == 'W' || c == 'E' || c == 'S' || c == 'N');	
}

int validation(t_config *data)
{
	char **s_map;
	
	if (validation_char_map(data))
		return (1);
	s_map = prepar_map(data);
	if (!s_map)
		return (1);
	data->y_rows = get_h(data->map);
	if (check_inside(s_map, data))
		return (1);
	find_and_replace_player(data->map, data);
    data->map = prepar_map(data);
	if (check_tex(data))
		return (1);
	return (0);
}
