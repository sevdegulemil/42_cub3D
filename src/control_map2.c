/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:26 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:57:16 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	is_map_valid(char **map, char p)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == p)
				return (perr(__func__, "invalid map, map count is not one"));
			j++;
		}
		i++;
	}
	return (OK);
}

t_err	validate_map_start(char **map, int *start_x, int *start_y, char p)
{
	int	i;
	int	j;

	*start_x = -1;
	*start_y = -1;
	i = 0;
	while (map[i] != NULL && *start_x == -1)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '1')
			{
				*start_y = i;
				*start_x = j;
				break ;
			}
			j++;
		}
		i++;
	}
	if (*start_x != -1 && *start_y != -1)
		flood_fill(map, *start_x, *start_y, p);
	return (OK);
}

t_err	validate_map(char **map, char p)
{
	int		start_x;
	int		start_y;
	t_err	err;

	err = validate_map_start(map, &start_x, &start_y, p);
	if (err != OK)
		return (err);
	err = is_map_valid(map, p);
	if (err != OK)
		return (perr(__func__, "is_map_valid failed"));
	return (OK);
}

t_err	validate_map_cell(t_map *map, int i, int j, char p)
{
	if (map->map_h[i][j] == 'H')
	{
		if ((map->map_h[i][j + 1] && (map->map_h[i][j + 1] == '0'
			|| map->map_h[i][j + 1] == p)) || (j != 0 && map->map_h[i][j
				- 1] && (map->map_h[i][j - 1] == '0' || map->map_h[i][j
					- 1] == p)) || (map->map_h[i + 1] && (map->map_h[i
					+ 1][j] == '0' || map->map_h[i + 1][j] == p)) || (i != 0
				&& map->map_h[i - 1] && (map->map_h[i - 1][j] == '0'
					|| map->map_h[i - 1][j] == p)))
			return (perr(__func__,
					"Invalid map,surrounded by walls(space and 0)"));
	}
	return (OK);
}

t_err	map_control_part(t_map *map)
{
	int		i;
	int		j;
	char	p;
	t_err	err;

	i = 0;
	p = map->player.direction;
	while (map->map_h[i])
	{
		j = 0;
		while (map->map_h[i][j])
		{
			err = validate_map_cell(map, i, j, p);
			if (err != OK)
				return (err);
			j++;
		}
		i++;
	}
	return (OK);
}
