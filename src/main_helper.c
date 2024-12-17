/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:08 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:29 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player(t_game *game)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (game->pure_map.map[i])
	{
		if (ft_strchr(game->pure_map.map[i], 'N'))
			c = 'N';
		else if (ft_strchr(game->pure_map.map[i], 'S'))
			c = 'S';
		else if (ft_strchr(game->pure_map.map[i], 'W'))
			c = 'W';
		else if (ft_strchr(game->pure_map.map[i], 'E'))
			c = 'E';
		if (c != 0)
		{
			game->map.player.x = i;
			game->map.player.y = ft_strchr(game->pure_map.map[i], c)
				- game->pure_map.map[i];
			game->map.player.direction = c;
			break ;
		}
		i++;
	}
}

char	**pure_map(char **map, int height)
{
	int		i;
	int		j;
	char	**new_map;
	char	*trimmed_line;

	i = 0;
	j = 0;
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
	{
		perr(__func__, "malloc failed");
		return (NULL);
	}
	i = 0;
	while (map[i])
	{
		trimmed_line = ft_strtrim(map[i], "\n");
		if (trimmed_line && ft_strlen(trimmed_line) > 0)
			new_map[j++] = trimmed_line;
		else
			free(trimmed_line);
		i++;
	}
	new_map[j] = NULL;
	return (new_map);
}

void	initialize_pure_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map[i])
		i++;
	game->map.map_height = i;
	game->pure_map.map = pure_map(game->map.map, game->map.map_height);
	game->pure_map.map_height = game->map.map_height;
	game->pure_map.map_width = game->map.map_width;
}
