/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:22:47 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 17:14:50 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*gc_strndup(const char *line, int start, int end)
{
	char	*res;
	int		len;
	int		i;

	if (!line || end <= start)
		return (NULL);
	len = end - start;
	res = gc_malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && line[start + i])
	{
		res[i] = line[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*p_sr;
	unsigned char		*p_dst;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	p_sr = (const unsigned char *)src;
	p_dst = (unsigned char *) dst;
	while (n--)
	{
		*p_dst++ = *p_sr++;
	}
	return (dst);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	size_t	i;

	i = ft_strlen(s1);
	p = (char *)gc_malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, i + 1);
	return (p);
}
