/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:40 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:07 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dispose_rgb_arrays(t_game *game)
{
	int	i;

	if (game->map.texture.f.rgb_str_arr)
	{
		i = 0;
		while (game->map.texture.f.rgb_str_arr[i])
		{
			free(game->map.texture.f.rgb_str_arr[i]);
			i++;
		}
		free(game->map.texture.f.rgb_str_arr);
		game->map.texture.f.rgb_str_arr = NULL;
	}
	if (game->map.texture.c.rgb_str_arr)
	{
		i = 0;
		while (game->map.texture.c.rgb_str_arr[i])
		{
			free(game->map.texture.c.rgb_str_arr[i]);
			i++;
		}
		free(game->map.texture.c.rgb_str_arr);
		game->map.texture.c.rgb_str_arr = NULL;
	}
}

void	dispose_texture_paths(t_game *game)
{
	if (game->map.texture.no.path)
	{
		free(game->map.texture.no.path);
		game->map.texture.no.path = NULL;
	}
	if (game->map.texture.so.path)
	{
		free(game->map.texture.so.path);
		game->map.texture.so.path = NULL;
	}
	if (game->map.texture.we.path)
	{
		free(game->map.texture.we.path);
		game->map.texture.we.path = NULL;
	}
	if (game->map.texture.ea.path)
	{
		free(game->map.texture.ea.path);
		game->map.texture.ea.path = NULL;
	}
}

void	dispose_textures(t_game *game)
{
	dispose_texture_paths(game);
	dispose_rgb_arrays(game);
}

void	dispose(t_game *game)
{
	dispose_textures(game);
	dispose_maps(game);
	dispose_general(game);
}
