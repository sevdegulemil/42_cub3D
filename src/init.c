/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:46:57 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:24 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"
#include <ctype.h>
#include <fcntl.h>
#include <string.h>

t_err	map_path_control(char *path)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (perr(__func__, "Invalid file extension"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	close(fd);
	return (OK);
}

t_err	process_line(t_map *map, int fd, int *indices, bool *eof)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		*eof = true;
		return (OK);
	}
	if (indices[0] >= (map->row))
	{
		map->map[indices[1]] = ft_strdup(line);
		if (!map->map[indices[1]])
		{
			free(line);
			close(fd);
			return (strr_arr_dispose(map->map), perr(__func__,
					"ft_strdup failed"));
		}
		indices[1]++;
	}
	indices[0]++;
	free(line);
	return (OK);
}

t_err	prepare_map_init_part2(t_map *map, int fd)
{
	int		indices[2];
	t_err	err;
	bool	eof;

	indices[0] = 0;
	indices[1] = 0;
	eof = false;
	while (!eof)
	{
		err = process_line(map, fd, indices, &eof);
		if (err != OK)
			return (err);
	}
	map->map[indices[1]] = NULL;
	return (close(fd), OK);
}

t_err	prepare_map_init_part1(t_map *map, char *path, int *fd)
{
	if (!map || !path)
		return (perr(__func__, "unexpected error"));
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (perr(__func__, "open failed"));
	map->map = malloc(sizeof(char *) * (map->map_len - map->row + 1));
	if (!map->map)
	{
		close(*fd);
		return (perr(__func__, "malloc failed"));
	}
	return (OK);
}

t_err	prepare_map_init(t_map *map, char *path)
{
	int		fd;
	t_err	err;

	err = prepare_map_init_part1(map, path, &fd);
	if (err != OK)
	{
		free(map);
		return (err);
	}
	err = prepare_map_init_part2(map, fd);
	if (err != OK)
	{
		strr_arr_dispose(map->map);
		free(map);
	}
	return (err);
}
