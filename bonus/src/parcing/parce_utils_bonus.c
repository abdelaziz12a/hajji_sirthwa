/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:58:21 by aaboudra          #+#    #+#             */
/*   Updated: 2025/11/22 17:15:15 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	ft_isdigit(int v)
{
	if (v >= 48 && v <= 57)
		return (1);
	return (0);
}

static int	check_sig(int sg)
{
	if (sg > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					seg;
	unsigned long long	res;

	seg = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			seg = (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res > ((unsigned long long)((9223372036854775807
					- (*str - 48)) / 10)))
			return (check_sig(seg));
		res = (res * 10) + *str - 48;
		str++;
	}
	return (res * seg);
}