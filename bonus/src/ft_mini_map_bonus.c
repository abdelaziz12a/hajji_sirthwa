/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:40:14 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 23:24:13 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	ft_mini_player(t_data *data)
{
	t_i_xy	c0;
	t_i_xy	c;
	t_i_xy	d;
	int		r;

	r = 8;
	c0.x = data->mm_img->width / 2;
	c0.y = data->mm_img->height / 2;
	c.y = c0.y - r;
	while (c.y >= 0 && c.y <= c0.y + r)
	{
		d.y = c.y - c0.y;
		d.x = (int)sqrt(r * r - d.y * d.y);
		c.x = c0.x - d.x;
		while (c.x >= 0 && c.x <= c0.x + d.x)
		{
			if (pow(c.y - c0.y + data->player.dir.y * r / 2, 2)
				+ pow(c.x - c0.x - data->player.dir.x * r / 2, 2) <= pow(r / 2, 2))
				mlx_put_pixel(data->mm_img, c.x, c.y, 0xFFB4DCFF);
			else
				mlx_put_pixel(data->mm_img, c.x, c.y, 0xC8325AFF);
			c.x++;
		}
		c.y++;
	}
}

void	ft_mini_map(void *param)
{
	t_data	*data;
	t_i_xy	xy;
	t_i_xy	map;

	data = (t_data *)param;
	xy.y = 0;
	while (xy.y < (int)data->mm_img->height)
	{
		xy.x = 0;
		while (xy.x < (int)data->mm_img->width)
		{
			map.x = xy.x / 32. + (data->player.pos.x - (int)data->mm_img->width / (2 * 32.));
			map.y = xy.y / 32. + (data->player.pos.y - (int)data->mm_img->height / (2 * 32.));
			if (map.x < 0 || map.x >= data->map_size.x
				|| map.y < 0 || map.y >= data->map_size.y
				|| data->map[map.y][map.x] == ' ')
				mlx_put_pixel(data->mm_img, xy.x, xy.y, 0x141419FF);
			else if (data->map[map.y][map.x] == '1')
				mlx_put_pixel(data->mm_img, xy.x, xy.y, 0x2D2D37FF);
			else
				mlx_put_pixel(data->mm_img, xy.x, xy.y, 0x649B64FF);
			xy.x++;
		}
		xy.y++;
	}
	ft_mini_player(data);
}
