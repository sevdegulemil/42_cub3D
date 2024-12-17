/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_h_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:14 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:42 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	map_h_fill(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_len - map->row)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == ' ' || map->map[i][j] == '\t'
				|| map->map[i][j] == '\v' || map->map[i][j] == '\f'
				|| map->map[i][j] == '\r' || map->map[i][j] == '\n')
				map->map_h[i][j] = 'H';
			else
				map->map_h[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	return (OK);
}

t_err	allocate_map_h(t_map *map)
{
	int	i;

	i = 0;
	map->map_h = malloc(sizeof(char *) * (map->map_len - map->row + 2));
	if (!map->map_h)
		return (perr(__func__, "malloc failed(map_h)"));
	while (i < map->map_len - map->row)
	{
		map->map_h[i] = malloc(sizeof(char) * (map->map_width + 1));
		if (!map->map_h[i])
			return (strr_arr_dispose(map->map_h), perr(__func__,
					"malloc failed(map_h row)"));
		ft_memset(map->map_h[i], 'H', map->map_width);
		map->map_h[i][map->map_width] = '\0';
		i++;
	}
	map->map_h[i] = NULL;
	return (OK);
}

t_err	map_h(t_map *map)
{
	t_err	err;

	map->map_width = map_width(map);
	err = allocate_map_h(map);
	if (err != OK)
		return (err);
	err = map_h_fill(map);
	if (err != OK)
		strr_arr_dispose(map->map_h);
	return (OK);
}
