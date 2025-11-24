/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 22:44:19 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/15 18:23:21 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	ft_draw_line(t_data *data, t_ray *ray, t_i_xy *xy, t_tex *tex)
{
	unsigned int	color;

	xy->y = 0;
	while (xy->y < ray->line.start)
		mlx_put_pixel(data->cub_img, xy->x, xy->y++, data->ceil);
	while (xy->y < ray->line.end + 1)
	{
		tex->y = (int)((double)(xy->y + ray->line.height / 2
					- data->mlx->height / 2)
				* (data->tex[tex->id]->height - 1) / ray->line.height);
		color = ft_color(data->tex[tex->id]
				->pixels[(tex->x + tex->y * data->tex[tex->id]
					->width) * data->tex[tex->id]->bytes_per_pixel],
				data->tex[tex->id]->pixels[(tex->x + tex->y * data->tex[tex->id]
					->width) * data->tex[tex->id]->bytes_per_pixel + 1],
				data->tex[tex->id]->pixels[(tex->x + tex->y * data->tex[tex->id]
					->width) * data->tex[tex->id]->bytes_per_pixel + 2],
				data->tex[tex->id]->pixels[(tex->x + tex->y * data->tex[tex->id]
					->width) * data->tex[tex->id]->bytes_per_pixel + 3]);
		mlx_put_pixel(data->cub_img, xy->x, xy->y++, color);
	}
	while (xy->y < data->mlx->height)
		mlx_put_pixel(data->cub_img, xy->x, xy->y++, data->floor);
}

void	ft_draw(t_data *data, t_ray *ray, t_i_xy *xy)
{
	double	coll_rate;
	t_tex	tex;

	if (!ray->side && ray->dir.x < 0)
		tex.id = WE;
	else if (!ray->side)
		tex.id = EA;
	if (ray->side && ray->dir.y < 0)
		tex.id = SO;
	else if (ray->side)
		tex.id = NO;
	if (!ray->side)
		coll_rate = data->player.pos.y - ray->dir.y * ray->perp_wall_dist;
	else
		coll_rate = data->player.pos.x + ray->dir.x * ray->perp_wall_dist;
	coll_rate -= (int)coll_rate;
	tex.x = (int)(coll_rate * data->tex[tex.id]->width);
	if ((ray->side == 0 && ray->dir.x < 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex.x = data->tex[tex.id]->width - tex.x - 1;
	ft_draw_line(data, ray, xy, &tex);
}
