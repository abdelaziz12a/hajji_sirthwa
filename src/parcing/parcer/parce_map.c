/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:19:57 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 16:11:44 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_map(char *line)
{
    int i;

	i = 0;
    while (is_space(line[i]))
        i++;
    if (line[i] == '\0')
        return (0);
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' 
			&& line[i] != 'E' && line[i] != 'W' && !is_space(line[i]))
            return (0);
        i++;
    }
    return (1);
}

int get_long(t_config *data)
{
	int len;
	int max;
	int i;

	i = 0;
	max = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	data->x_cols = max;
	return (max);
}
char **prepar_map(t_config *data)
{
	int longer_len;
	char **squar_map;
	int i;

	longer_len = get_long(data);
	i = 0;
	while (data->map[i])
		i++;
	squar_map = gc_malloc(sizeof (char *) * (i + 1));
	if (!squar_map)
		return (NULL);
	i = 0;
	while (data->map[i])
	{
		squar_map[i] = gc_malloc(sizeof(char) * (longer_len + 1));
		if (!squar_map[i])
			return (NULL);
		memset(squar_map[i], ' ', longer_len);
        memcpy(squar_map[i], data->map[i], ft_strlen(data->map[i]));
        squar_map[i][longer_len] = '\0';
        i++;
	}
	squar_map[i] = NULL;
	return(squar_map);
}
int get_h(char**map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int validation_char_map(t_config * data)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1' 
				&& data->map[i][j] != ' ' && !is_player(data->map[i][j]))
					return (1);
			if (is_player(data->map[i][j]) && data->player_dir == '1')
				data->player_dir = data->map[i][j];
			else if(is_player(data->map[i][j]) && data->player_dir != '1')
					return (1);
			j++;	
		}
		i++;
	}
	if (data->player_dir == '1')
		return (1);
	return (0);
}

