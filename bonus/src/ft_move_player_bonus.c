/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 17:12:14 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	ft_move1(t_data *data, keys_t key)
{
	if (key == MLX_KEY_W)
	{
		if (!ft_iswall(data, data->player.pos.x + .1 * data->player.dir.x,
				data->player.pos.y))
			data->player.pos.x += .1 * data->player.dir.x;
		if (!ft_iswall(data, data->player.pos.x,
				data->player.pos.y - .1 * data->player.dir.y))
			data->player.pos.y -= .1 * data->player.dir.y;
	}
	if (key == MLX_KEY_S)
	{
		if (!ft_iswall(data, data->player.pos.x - .1 * data->player.dir.x,
				data->player.pos.y))
			data->player.pos.x -= .1 * data->player.dir.x;
		if (!ft_iswall(data, data->player.pos.x,
				data->player.pos.y + .1 * data->player.dir.y))
			data->player.pos.y += .1 * data->player.dir.y;
	}
}

static void	ft_move2(t_data *data, keys_t key)
{
	if (key == MLX_KEY_D)
	{
		if (!ft_iswall(data, data->player.pos.x + .1 * data->player.dir.y,
				data->player.pos.y))
			data->player.pos.x += .1 * data->player.dir.y;
		if (!ft_iswall(data, data->player.pos.x,
				data->player.pos.y + .1 * data->player.dir.x))
			data->player.pos.y += .1 * data->player.dir.x;
	}
	if (key == MLX_KEY_A)
	{
		if (!ft_iswall(data, data->player.pos.x - .1 * data->player.dir.y,
				data->player.pos.y))
			data->player.pos.x -= .1 * data->player.dir.y;
		if (!ft_iswall(data, data->player.pos.x,
				data->player.pos.y - .1 * data->player.dir.x))
			data->player.pos.y -= .1 * data->player.dir.x;
	}
}

void	ft_rotate1(t_data *data)
{
	double	tmp;

	tmp = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(PI / 36.)
		- data->player.dir.y * sin(PI / 36.);
	data->player.dir.y = data->player.dir.y * cos(PI / 36.)
		+ tmp * sin(PI / 36.);
	tmp = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(PI / 36.)
		- data->player.plane.y * sin(PI / 36.);
	data->player.plane.y = data->player.plane.y * cos(PI / 36.)
		+ tmp * sin(PI / 36.);
}

void	ft_rotate2(t_data *data)
{
	double	tmp;

	tmp = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-PI / 36.)
		- data->player.dir.y * sin(-PI / 36.);
	data->player.dir.y = data->player.dir.y * cos(-PI / 36.)
		+ tmp * sin(-PI / 36.);
	tmp = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(-PI / 36.)
		- data->player.plane.y * sin(-PI / 36.);
	data->player.plane.y = data->player.plane.y * cos(-PI / 36.)
		+ tmp * sin(-PI / 36.);
}

void	ft_move_player(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_move1(param, MLX_KEY_W);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		ft_move1(param, MLX_KEY_S);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		ft_move2(param, MLX_KEY_D);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		ft_move2(param, MLX_KEY_A);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		ft_rotate1(param);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		ft_rotate2(param);
}
