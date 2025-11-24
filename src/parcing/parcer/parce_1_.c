/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:51:56 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/15 13:40:08 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int is_double(char *start,  t_config *data)
{ 
	if (!start)
		return (1);
	if ((!ft_strncmp(&start[0], "NO ", 3) && data->tex.no != NULL)
		|| (!ft_strncmp(&start[0], "SO ", 3) && data->tex.so != NULL)
		|| (!ft_strncmp(&start[0], "WE ", 3) && data->tex.we != NULL)
		|| (!ft_strncmp(&start[0], "EA ", 3) && data->tex.ea != NULL)
		|| (!ft_strncmp(&start[0], "F ", 2) && data->floor.r != -1)
		|| (!ft_strncmp(&start[0], "C ", 2) && data->ceil.r != -1))
		return (1);
	else 
		return (0);
}

static int assign_map(char *line, t_config *data)
{
	int index;
	size_t len;

	index = 0;
	if (!line)
		return (1);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (data->map[index] && data->map[index][0])
		index++;
	data->map[index] = ft_strdup(line);
	if (!data->map[index])
		return (1);
	data->map[index + 1] = NULL;
	return (0);
}
static int append_map(char **file, char *line, t_config *data)
{
	int cont_line;

	if (!data->map)
	{
		cont_line = get_cont_line(file[1]);
		if (cont_line <= 0)
			return (1);
		data->map = gc_malloc(sizeof(char *) * (cont_line + 1));
		if (!data->map)
			return (1);
		data->map[0] = NULL;
	}
	return (assign_map(line, data));
}

static int append_config(char *line, int i, t_config *data)
{
	if (is_double(get_start(line , i), data))
		return (1);
	if (!ft_strcmp(get_start(line , i), "F ") || !ft_strcmp(get_start(line , i), "C "))
	{
		if (assign_color(get_start(line , i), line, i, data))
			return (1);
	}
	if (!ft_strcmp(get_start(line , i), "NO ") || !ft_strcmp(get_start(line , i), "WE ")
		|| !ft_strcmp(get_start(line , i), "SO ") || !ft_strcmp(get_start(line , i), "EA "))
	{
		if (assign_tex(get_start(line , i), line, i, data))
			return (1);
	}
	return(0);
}

int parce_line(char **file, int fd,t_config *data)
{
	int i;
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{ 
		i = 0;
		while (is_space(line[i]) && !is_map(line))
			i++;
		if (!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "SO ", 3)
			|| !ft_strncmp(&line[i], "WE ", 3) || !ft_strncmp(&line[i], "EA ", 3)
			|| !ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "C ", 2))
		{
			if (append_config(line, i, data))
				return (free_ptr(line), 1);
		}
		else if (is_map(line))
		{
			if (negative_map_position(data) || append_map(file, line, data))
				return (free_ptr(line), 1);
		}
		else if ((line[i] != '\0'))
			return (1);
	}
	free_ptr(line);
	return (0);
}
