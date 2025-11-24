/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/15 10:49:25 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_cub_loop(t_data *data)
{
	if (!mlx_loop_hook(data->mlx, ft_cub, data))
		return (1);
	if (!mlx_loop_hook(data->mlx, ft_move_player, data))
		return (1);
	mlx_loop(data->mlx);
	return (0);
}
