/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/15 15:49:03 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_mouse_rotate(double xpos, double ypos, void *param)
{
	static double	x;
	t_data			*data;

	(void)ypos;
	data = (t_data *)param;
	if (data->mouse && xpos < x)
		ft_rotate1(param);
	if (data->mouse && xpos > x)
		ft_rotate2(param);
	x = xpos;
}

void	ft_mouse_mode(mouse_key_t button, action_t action, modifier_key_t mods,
			void *param)
{
	t_data	*data;

	(void)mods;
	data = (t_data *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		if (data->mouse == 1)
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
			data->mouse = 0;
		}
		else
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
			data->mouse = 1;
		}
	}
}
