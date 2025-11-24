/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:22:08 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/15 13:30:47 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int negative_map_position(t_config *data)
{
	if (!data->tex.no || !data->tex.so || !data->tex.we
		|| !data->tex.ea || data->floor.b < 0 || data->ceil.b < 0)
		return(1);
	return (0);
}

char *get_start(char *line, int i)
{
	if (!ft_strncmp(&line[i], "NO ", 3))
		return("NO ");
	if (!ft_strncmp(&line[i], "SO ", 3))
		return ("SO ");
	if (!ft_strncmp(&line[i], "WE ", 3))
		return ("WE ");
	if (!ft_strncmp(&line[i], "EA ", 3))
		return ("EA ");
	if (!ft_strncmp(&line[i], "F ", 2))
		return ("F ");
	if (!ft_strncmp(&line[i], "C ", 2))
		return ("C ");
	else
		return (NULL);
}

char *get_color(char *line, int i)
{
	int begin;
	int end;

	i += 2;
	while (is_space(line[i]))
		i++;
	begin = i;
	while (line[i] && !is_space(line[i]) && line[i] != '\n')
		i++;
	end = i;
	while (line[i])
	{
		if (!is_space(line[i]) && line[i] != '\n')
			return (NULL);
		i++;
	}
	return (gc_strndup(line, begin, end));
}



static int  valid_file_name(char *path)
{
	int len;
	int fd;
	
	fd = open(path, O_RDONLY);
	if (-1 == fd)
	{
		close(fd);
		return (-1);
	}
	len = ft_strlen(path);
	if (len <= 4 || ft_strcmp(&path[len - 4], ".cub"))
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

int main_parce(char **cub_file, t_config *data)
{
	int fd;

	fd = valid_file_name(cub_file[1]);
	if (fd > 0)
	{
		if (parce_line(cub_file, fd, data))
		{
		   close (fd);
		   return (1);
		}
		else
		{
			if (validation(data))
				return (close(fd), 1);
		}
	}
	else
		return (close(fd), 1);
	return (close(fd),0);
}
