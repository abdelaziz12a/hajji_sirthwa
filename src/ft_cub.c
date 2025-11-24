/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 22:44:19 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 16:44:39 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_dda(t_data *data, t_ray *ray, t_dist *dist, t_i_xy *map)
{
	while (data->map[map->y][map->x] == '0')
	{
		if (dist->side.x < dist->side.y)
		{
			dist->side.x += dist->delta.x;
			map->x -= 2 * (ray->dir.x < 0.) - 1;
			ray->side = 0;
		}
		else
		{
			dist->side.y += dist->delta.y;
			map->y += 2 * (ray->dir.y < 0.) - 1;
			ray->side = 1;
		}
	}
}

static double	ft_perp_wall_dist(t_data *data, t_ray *ray)
{
	t_dist	dist;
	t_i_xy	map;

	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;
	dist.delta.x = 1. / fabs(ray->dir.x);
	dist.delta.y = 1. / fabs(ray->dir.y);
	if (ray->dir.x < 0.)
		dist.side.x = (data->player.pos.x - map.x) * dist.delta.x;
	else
		dist.side.x = (map.x - data->player.pos.x + 1.) * dist.delta.x;
	if (ray->dir.y < 0.)
		dist.side.y = (map.y - data->player.pos.y + 1.) * dist.delta.y;
	else
		dist.side.y = (data->player.pos.y - map.y) * dist.delta.y;
	ft_dda(data, ray, &dist, &map);
	if (!ray->side)
		return (dist.side.x - dist.delta.x);
	return (dist.side.y - dist.delta.y);
}

static void	ft_ray(t_data *data, t_ray *ray, int x)
{
	ray->cam_rate = (2. * x - data->mlx->width) / data->mlx->height;
	ray->dir.x = data->player.dir.x + data->player.plane.x * ray->cam_rate;
	ray->dir.y = data->player.dir.y + data->player.plane.y * ray->cam_rate;
	ray->perp_wall_dist = ft_perp_wall_dist(data, ray);
	ray->line.height = (int)(data->mlx->height / ray->perp_wall_dist);
	ray->line.start = -ray->line.height / 2 + data->mlx->height / 2;
	if (ray->line.start < 0)
		ray->line.start = 0;
	ray->line.end = ray->line.height / 2 + data->mlx->height / 2;
	if (ray->line.end >= data->mlx->height)
		ray->line.end = data->mlx->height - 1;
}

void	ft_cub(void *param)
{
	t_data	*data;
	t_ray	ray;
	t_i_xy	xy;

	data = (t_data *)param;
	xy.x = 0;
	while (xy.x < data->mlx->width)
	{
		ft_ray(data, &ray, xy.x);
		ft_draw(data, &ray, &xy);
		xy.x++;
	}
}
