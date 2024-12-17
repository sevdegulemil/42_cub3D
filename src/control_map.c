/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:20 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/15 15:55:25 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	validate_map_line(t_map *map, char *line, int row)
{
	t_err	err;

	line = ft_strtrim(map->map[row], "\n\v\t\r ");
	if (!line)
		return (perr(__func__, "ft_strtrim failed"));
	if (((ft_strlen(line) >= 1)) && line[0] == '0' && (line[0] != '1'
			|| line[ft_strlen(line) - 1] != '1'))
	{
		return (free(line), perr(__func__, "Invalid map,surrounded by walls3"));
	}
	if (ft_strlen(line) > 1)
	{
		err = map_control_centrals_items(map, line, row);
		if (err != OK || map->player_count > 1)
			return (free(line), perr(__func__,
					"Invalid map(undefined item) or player count"));
	}
	free(line);
	return (OK);
}

t_err	map_control_centrals(t_map *map)
{
	int		i;
	t_err	err;

	i = map->map_start + 1;
	while (i <= map->map_end)
	{
		err = validate_map_line(map, map->map[i], i);
		if (err != OK)
			return (err);
		i++;
	}
	return (OK);
}

t_err	validate_and_set_end(t_map *map)
{
	int		i;
	char	*line;

	i = map->map_len - map->row - 1;
	while (i >= 0 && map->map[i] && is_empty_line(map->map[i])
		&& ft_strlen(map->map[i]) == 1)
		i--;
	map->map_end = i;
	line = ft_strtrim(map->map[map->map_end], "\n\v\t\r ");
	if (!line || !all_chars_are(line))
		return (free(line), perr(__func__, "Invalid map,surrounded by walls2"));
	free(line);
	return (OK);
}

t_err	map_control_boundaries(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * (map->map_width + 1));
	if (!line)
		return (free(line), perr(__func__, "Memory allocation failed"));
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1
		&& i < map->map_len)
		i++;
	map->map_start = i;
	free(line);
	line = ft_strtrim(map->map[map->map_start], "\n\v\t\r ");
	if (!line || !all_chars_are(line))
		return (free(line), perr(__func__, "Invalid map,surrounded by walls1"));
	free(line);
	if (validate_and_set_end(map) != OK)
		return (ERR);
	return (OK);
}

t_err	map_control(t_map *map)
{
	t_err	err;

	err = map_control_boundaries(map);
	if (err != OK)
		return (err);
	err = map_control_centrals(map);
	if (err != OK)
		return (perr(__func__, "map_control_centrals failed"));
	return (OK);
}
