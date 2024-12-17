/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:34 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:05 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	strr_arr_dispose(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	dispose_general(t_game *game)
{
	if (game->txt[0].img)
		mlx_destroy_image(game->mlx.mlx, game->txt[0].img);
	if (game->txt[1].img)
		mlx_destroy_image(game->mlx.mlx, game->txt[1].img);
	if (game->txt[2].img)
		mlx_destroy_image(game->mlx.mlx, game->txt[2].img);
	if (game->txt[3].img)
		mlx_destroy_image(game->mlx.mlx, game->txt[3].img);
	game->txt[0].img = NULL;
	game->txt[1].img = NULL;
	game->txt[2].img = NULL;
	game->txt[3].img = NULL;
	if (game->mlx.win)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		game->mlx.win = NULL;
	}
	free(game);
}

void	dispose_maps(t_game *game)
{
	if (game->last_map.map_h)
	{
		strr_arr_dispose(game->last_map.map_h);
		game->last_map.map_h = NULL;
	}
	if (game->pure_map.map)
	{
		strr_arr_dispose(game->pure_map.map);
		game->pure_map.map = NULL;
	}
	if (game->map.map)
	{
		strr_arr_dispose(game->map.map);
		game->map.map = NULL;
	}
	if (game->map.map_h)
	{
		strr_arr_dispose(game->map.map_h);
		game->map.map_h = NULL;
	}
}
