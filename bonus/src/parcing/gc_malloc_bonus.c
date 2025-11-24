/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:33:25 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 17:14:06 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	data_init(t_config *conf)
{
	conf->player_dir = '1';
	conf->tex.no = NULL;
	conf->tex.so = NULL;
	conf->tex.we = NULL;
	conf->tex.ea = NULL;
	conf->map = NULL;
	conf->floor.r = -1;
	conf->floor.g = -1;
	conf->floor.b = -1;
	conf->ceil.r = -1;
	conf->ceil.g = -1;
	conf->ceil.b = -1;
}

static t_gc	**get_gc_list(void)
{
	static t_gc	*gc = NULL;
	return (&gc);
}

void	*gc_malloc(size_t size)
{
	void	*ptr;
	t_gc	*node;
	t_gc	**gc_list;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = NULL;

	gc_list = get_gc_list();
	if (!*gc_list)
		*gc_list = node;
	else
	{
		node->next = *gc_list;
		*gc_list = node;
	}
	return (ptr);
}

void free_ptr(void *ptr)
{
	t_gc **list;
	t_gc *cur;
	t_gc *prev;

	list = get_gc_list();
	if (!list || !*list || !ptr)
		return;
	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				*list = cur->next;
			free(cur->ptr);
			free(cur);
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	free_all(void)
{
	t_gc	**gc_list = get_gc_list();
	t_gc	*tmp;
	t_gc	*curr;

	curr = *gc_list;
	while (curr)
	{
		tmp = curr->next;
		free(curr->ptr);
		free(curr);
		curr = tmp;
	}
	*gc_list = NULL;
}