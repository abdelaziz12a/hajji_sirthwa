/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_coler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:06:37 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/13 15:47:08 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int put_rgb(int color, int cont, char c, t_config *data)
{
	if (color > 255)
		return (1);
	if (c == 'F')
	{
		if (cont == 1)
			data->floor.r = color;
		else if (cont == 2)
			data->floor.g = color;
		else if (cont == 3)
			data->floor.b = color;
		else
			return (1);
	}
	if (c == 'C')
	{
		if (cont == 1)
			data->ceil.r = color;
		else if (cont == 2)
			data->ceil.g = color;
		else if (cont == 3)
			data->ceil.b = color;
		else
			return (1);
	}
	return(0);
}

int append_color(char *value, char c, t_config *data)
{
	int  i;
	int  start;
	int  cont;
	int  color;
	char *num;

	i = 0;
	cont = 0;
	while (value[i])
	{
		start = i;
		while (value[i] && value[i] != ',')
			i++;
		num = gc_strndup(value, start, i);
		if (!num)
			return (1);
		color = ft_atoi(num);
		if (put_rgb(color, ++cont, c, data))
			return (1);
		if (value[i] == ',')
			i++;
	}
	if (cont != 3)
		return (1);
	return (0);
}

int parce_color(char *start, char *value, t_config *data)
{
	int i;

	i = 0;
	if (!start || !value)
		return (1);
	while (value[i])
	{
		if (!ft_isdigit((unsigned char)value[i]) && (value[i] != 44))
			return (1);
		if ((value[i] == 44)
			&& (!value[i + 1]))
				return(1);
		i++;
	}
	return (append_color(value, start[0], data));
}
int assign_color(char *start,char *line, int i, t_config *data)
{
	char *value;
	
	if (!start)
		return (1);
	value = get_color(line , i);
	if (!value)
		return (1);
	if (parce_color(start, value, data))
		return (1);
	return (0);
}
