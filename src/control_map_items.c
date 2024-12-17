/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:12 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:55:57 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	map_control_set_player(t_map *map, int x, int y, char direction)
{
	map->player.x = x;
	map->player.y = y;
	map->player.direction = direction;
	map->player_count++;
	return (OK);
}

t_err	map_control_centrals_items(t_map *map, char *line, int x)
{
	int		y;
	t_err	err;

	y = 0;
	while (line[y])
	{
		if (line[y] == '1' || line[y] == '0' || line[y] == ' ')
			y++;
		else if (line[y] == 'N' || line[y] == 'S' || line[y] == 'W'
			|| line[y] == 'E')
		{
			err = map_control_set_player(map, x, y, line[y]);
			if (err != OK)
				return (err);
			y++;
		}
		else
			return (perr(__func__, "Invalid map(undefined item)"));
	}
	return (OK);
}

int	map_width(t_map *map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

t_err	control_player(t_map *map)
{
	if (map->player.x == 0 || map->player.y == 0)
		return (perr(__func__, "Invalid player position"));
	if (map->map_h[map->player.x][map->player.y - 1] == '1'
		&& map->map_h[map->player.x][map->player.y + 1] == '1'
		&& map->map_h[map->player.x - 1][map->player.y] == '1'
		&& map->map_h[map->player.x + 1][map->player.y] == '1')
		return (perr(__func__, "Invalid player position, surrounded by walls"));
	return (OK);
}
