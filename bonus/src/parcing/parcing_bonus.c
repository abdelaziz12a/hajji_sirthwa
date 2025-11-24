/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:17:51 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 22:26:28 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	find_and_replace_player(char **map, t_config *data)
{
	int i = 0;
	int j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				data->player_dir = map[i][j];
				map[i][j] = '0';
				return;
			}
			j++;
		}
		i++;
	}
}

t_config *parcing(int ac, char **av)
{
    t_config *map_conf;

    map_conf = gc_malloc(sizeof(t_config));
    if (!map_conf)
        return (NULL);
    data_init(map_conf);
    if (ac == 2)
    {
        if (main_parce(av, map_conf))
        {
            free_all();
            printf("error\n");
        }
    }
    else
        printf("error\n");
    //you do free_all(); after don with staruct;
    return (map_conf);
}
