/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:46:22 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/15 17:58:28 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <fcntl.h>

void	load_textures(t_game *game)
{
	game->txt[0].img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->map.texture.ea.path, &game->txt[0].width,
			&game->txt[0].height);
	game->txt[1].img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->map.texture.no.path, &game->txt[1].width,
			&game->txt[1].height);
	game->txt[2].img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->map.texture.so.path, &game->txt[2].width,
			&game->txt[2].height);
	game->txt[3].img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->map.texture.we.path, &game->txt[3].width,
			&game->txt[3].height);
	if (!game->txt[0].img || !game->txt[1].img || !game->txt[2].img
		|| !game->txt[3].img)
	{
		printf("Error\nmlx_xpm_file_to_image failed\n");
		exit(0);
	}
}

void	load_textures_addresses(t_game *game)
{
	game->txt[0].addr = mlx_get_data_addr(game->txt[0].img, &game->txt[0].bpp,
			&game->txt[0].line_length, &game->txt[0].endian);
	game->txt[1].addr = mlx_get_data_addr(game->txt[1].img, &game->txt[1].bpp,
			&game->txt[1].line_length, &game->txt[1].endian);
	game->txt[2].addr = mlx_get_data_addr(game->txt[2].img, &game->txt[2].bpp,
			&game->txt[2].line_length, &game->txt[2].endian);
	game->txt[3].addr = mlx_get_data_addr(game->txt[3].img, &game->txt[3].bpp,
			&game->txt[3].line_length, &game->txt[3].endian);
	if (!game->txt[0].addr || !game->txt[1].addr || !game->txt[2].addr
		|| !game->txt[3].addr)
	{
		printf("Error\nmlx_get_data_addr failed\n");
		exit(0);
	}
}

static void	control_textures(t_texture *texture)
{
	t_err	err;

	err = control_texture_dir(texture);
	if (err != OK)
	{
		printf("Error\ncontrol_texture_dir failed\n");
		exit(0);
	}
	err = control_texture_color(&texture->c);
	if (err != OK)
	{
		printf("Error\ncontrol_texture_color failed\n");
		exit(0);
	}
	err = control_texture_color(&texture->f);
	if (err != OK)
	{
		printf("Error\ncontrol_texture_color failed\n");
		exit(0);
	}
}

static bool	handle_empty_line(char *line, t_map *map)
{
	if (is_empty_line(line) && (ft_strlen(line) == 1)
		&& !(map->texture.no.count == 1 && map->texture.so.count == 1
			&& map->texture.we.count == 1 && map->texture.ea.count == 1
			&& map->texture.f.count == 1 && map->texture.c.count == 1))
	{
		map->map_len++;
		map->row++;
		free(line);
		return (true);
	}
	return (false);
}

t_err	texture_init(t_map *map, char *path)
{
	int		fd;
	char	*line;
	t_err	err;

	if (!map || !path)
		return (perr(__func__, "unexpected error"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (handle_empty_line(line, map))
			continue ;
		err = set_texture(line, map);
		if (err != OK)
			return (free(line), close(fd), err);
		free(line);
		map->map_len++;
	}
	control_textures(&map->texture);
	return (close(fd), OK);
}
