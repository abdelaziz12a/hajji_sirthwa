/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_loop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:32:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/11/15 18:27:39 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void animation(void *param)
{
    t_anim *anim = (t_anim *)param;

    if (!anim->playing || anim->total_frames == 0)
        return;

    anim->counter++;
    if (anim->counter < anim->frame_delay)
        return;
    anim->counter = 0;

    mlx_image_t *old = anim->frames[anim->current_frame];
    old->enabled = false;

    anim->current_frame = (anim->current_frame + 1) % anim->total_frames;

    mlx_image_t *new = anim->frames[anim->current_frame];
    new->enabled = true;

    new->instances[0].x = 0;
    new->instances[0].y = HEIGHT - new->height;
}

static void	ft_mouse_hook(t_data *data)
{
	data->mouse = 1;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data->mlx, ft_mouse_rotate, data);
	mlx_mouse_hook(data->mlx, ft_mouse_mode, data);
}

void init_anim(void *param)
{
	t_anim *anim = (t_anim *)param;
    anim->current_frame = 0;
    anim->counter = 0;
    anim->frame_delay = 6;   // ≈ 10 FPS
    anim->total_frames = 0;
    anim->playing = true;

    char path[256];

    for (int i = 1; i < 15; i++)
    {
        snprintf(path, sizeof(path), "./bonus/frames/frame%d.png", i);

		int fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			printf("Error %s\n", path);
			return;
		}

        mlx_texture_t *tex = mlx_load_png(path);
        if (!tex)
            break;

        mlx_image_t *img = mlx_texture_to_image(anim->data->mlx, tex);
        if (!img)
        {
            mlx_delete_texture(tex);
            break;
        }

        mlx_delete_texture(tex); // we no longer need texture in ram

        anim->frames[i] = img;
        anim->total_frames++;
    }

    if (anim->total_frames == 0)
    {
        printf("❌ No frames loaded from ./frames\n");
        return;
    }

    // Show first frame at bottom-left
    // USING HEIGHT constant instead of win_h
    mlx_image_to_window(
        anim->data->mlx,
        anim->frames[0],
        0,
        HEIGHT - anim->frames[0]->height
    );
}


int	ft_cub_loop(t_data *data, t_anim *anim)
{
	if (!mlx_loop_hook(data->mlx, ft_cub, data))
		return (1);
	if (!mlx_loop_hook(data->mlx, ft_mini_map, data))
		return (1);
	if (!mlx_loop_hook(data->mlx, ft_move_player, data))
		return (1);
	if (!mlx_loop_hook(data->mlx, animation, anim))
		return (1);
	if (!mlx_loop_hook(data->mlx, init_anim, anim))
		return (1);
	ft_mouse_hook(data);
	mlx_loop(data->mlx);
	return (0);
}
