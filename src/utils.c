/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 16:45:22 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_iswall(t_data *data, double x, double y)
{
	if ((data->map[(int)y][(int)(x + .1)] == '1')
		|| (data->map[(int)y][(int)(x - .1)] == '1')
		|| (data->map[(int)(y + .1)][(int)x] == '1')
		|| (data->map[(int)(y - .1)][(int)x] == '1')
		|| (data->map[(int)(y + .1)][(int)(x + .1)] == '1')
		|| (data->map[(int)(y + .1)][(int)(x - .1)] == '1')
		|| (data->map[(int)(y - .1)][(int)(x + .1)] == '1')
		|| (data->map[(int)(y - .1)][(int)(x - .1)] == '1'))
		return (1);
	return (0);
}

t_u_int	ft_color(t_u_int r, t_u_int g, t_u_int b, t_u_int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
