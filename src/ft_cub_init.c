/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 16:37:37 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_game_init(t_data *data, int argc, char **argv)
{
	t_config	*conf;

	conf = parcing(argc, argv);
	if (!conf)
		return (1);
	data->player.pos.x = conf->player_x + .5;
	data->player.pos.y = conf->player_y + .5;
	data->player.dir.x = (conf->player_dir == 'E') - (conf->player_dir == 'W');
	data->player.dir.y = (conf->player_dir == 'N') - (conf->player_dir == 'S');
	data->player.plane.x = ((conf->player_dir == 'N')
			- (conf->player_dir == 'S')) * tan(PI / 6);
	data->player.plane.y = ((conf->player_dir == 'W')
			- (conf->player_dir == 'E')) * tan(PI / 6);
	data->tex_path[NO] = conf->tex.no;
	data->tex_path[SO] = conf->tex.so;
	data->tex_path[WE] = conf->tex.we;
	data->tex_path[EA] = conf->tex.ea;
	data->ceil = ft_color(conf->ceil.r, conf->ceil.g, conf->ceil.b, 0xFF);
	data->floor = ft_color(conf->floor.r, conf->floor.g, conf->floor.b, 0xFF);
	data->map = conf->map;
	data->map_size.x = conf->x_cols;
	data->map_size.y = conf->y_rows;
	return (0);
}

static int	ft_tex_init(t_data *data)
{
	data->tex[NO] = mlx_load_png(data->tex_path[NO]);
	if (!data->tex[NO])
		return (1);
	data->tex[SO] = mlx_load_png(data->tex_path[SO]);
	if (!data->tex[SO])
		return (1);
	data->tex[WE] = mlx_load_png(data->tex_path[WE]);
	if (!data->tex[WE])
		return (1);
	data->tex[EA] = mlx_load_png(data->tex_path[EA]);
	if (!data->tex[EA])
		return (1);
	return (0);
}

int	ft_cub_init(t_data *data, int argc, char **argv)
{
	if (ft_game_init(data, argc, argv))
		return (1);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!data->mlx)
		return (1);
	data->cub_img
		= mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (!data->cub_img)
		return (1);
	if (mlx_image_to_window(data->mlx, data->cub_img, 0, 0) < 0)
		return (1);
	if (ft_tex_init(data))
		return (1);
	return (0);
}
