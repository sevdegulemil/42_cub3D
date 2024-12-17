/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:45 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/15 17:42:36 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	control_texture_dir(t_texture *texture)
{
	if (texture->no.count != 1)
		return (perr(__func__, "Invalid texture NO count."));
	if (texture->so.count != 1)
		return (perr(__func__, "Invalid texture SO count."));
	if (texture->we.count != 1)
		return (perr(__func__, "Invalid texture WE count."));
	if (texture->ea.count != 1)
		return (perr(__func__, "Invalid texture EA count."));
	return (OK);
}

t_err	set_texture(char *line, t_map *map)
{
	char	*tmp;

	tmp = ft_strtrim_a(line, "\t\v\f\r\n ");
	if (!tmp)
		return (ERR);
	if (!ft_strncmp(tmp, "NO ", 3) || !ft_strncmp(tmp, "SO ", 3)
		|| !ft_strncmp(tmp, "WE ", 3) || !ft_strncmp(tmp, "EA ", 3))
		set_texture_dir(tmp, map);
	if (!ft_strncmp(tmp, "F ", 2))
	{
		if (!check_texture_color(tmp, map))
			return (free(tmp), ERR);
		set_texture_color_f(&map->texture);
		map->row++;
	}
	if (!ft_strncmp(tmp, "C ", 2))
	{
		if (!check_texture_color(tmp, map))
			return (free(tmp), ERR);
		set_texture_color_c(&map->texture);
		map->row++;
	}
	free(tmp);
	return (OK);
}

void	set_texture_for_direction(char *line, t_map *map, t_img *texture)
{
	char	*tmp;

	if (!line || !texture)
		return ;
	texture->path = ft_strdup(line + 3);
	tmp = ft_strtrim_a(line + 3, "\t\v\f\r\n ");
	if (!tmp)
		return ;
	if (texture->path)
	{
		free(texture->path);
		texture->path = NULL;
	}
	texture->path = tmp;
	texture->count++;
	map->row++;
}

void	set_texture_dir(char *line, t_map *map)
{
	if (!line)
		return ;
	if (map->texture.no.count == 1 && map->texture.so.count == 1
		&& map->texture.we.count == 1 && map->texture.ea.count == 1)
		return ;
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.no);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.so);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.we);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.ea);
}
