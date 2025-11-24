/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/22 16:33:43 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_cub_init(&data, argc, argv);
	ft_cub_loop(&data);
	mlx_terminate(data.mlx);

	// t_config	*conf;

	// conf = parcing(argc, argv);
	// printf("NO %s\nSO %s\nWE %s\nEA %s\n\n", conf->tex.no, conf->tex.so, conf->tex.ea, conf->tex.we);
	// printf("F %d,%d,%d\n", conf->floor.r, conf->floor.g, conf->floor.b);
	// printf("C %d,%d,%d\n\n", conf->ceil.r, conf->ceil.g, conf->ceil.b);

	// char **s;

	// s = conf->map;
	// while (*s)
	// 	printf("%s\n", *s++);
	// printf("\nPOS %d, %d\n", conf->player_x, conf->player_y);
	// printf("DIR %c\n", conf->player_dir);
	// printf("%d, %d\n", conf->x_cols, conf->y_rows);
	return (EXIT_SUCCESS);
}
