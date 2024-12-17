/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:51 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:57:40 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	draw(t_game *game)
{
	game->img_w.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	game->img_w.addr = mlx_get_data_addr(game->img_w.img, &game->img_w.bpp,
			&game->img_w.line_length, &game->img_w.endian);
	draw_ceiling_and_floor(game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img_w.img, 0,
		0);
	mlx_destroy_image(game->mlx.mlx, game->img_w.img);
}

void	init_xpm(t_game *game)
{
	load_textures(game);
	load_textures_addresses(game);
}

void	set_angle_view(t_game *game)
{
	if (game->map.player.direction == 'N')
		game->angle_view = 0.5f * M_PI;
	else if (game->map.player.direction == 'E')
		game->angle_view = 0.0f * M_PI;
	else if (game->map.player.direction == 'S')
		game->angle_view = -0.5f * M_PI;
	else if (game->map.player.direction == 'W')
		game->angle_view = 1.0f * M_PI;
}

void	set_position(t_game *game)
{
	game->pos_y = game->map.player.x + 0.5f;
	game->pos_x = game->map.player.y + 0.5f;
	set_angle_view(game);
}

void	start_game(t_game *game)
{
	game->color_ceiling = game->map.texture.c.r << 16
		| game->map.texture.c.g << 8 | game->map.texture.c.b;
	game->color_floor = game->map.texture.f.r << 16
		| game->map.texture.f.g << 8 | game->map.texture.f.b;
	set_position(game);
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		printf("Error\nmlx init failed\n");
		exit(0);
	}
	init_xpm(game);
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx.win)
	{
		printf("Error\nmlx window creation failed\n");
		free(game->mlx.mlx);
		exit(0);
	}
	draw(game);
	mlx_hook(game->mlx.win, ON_KEYDOWN, KeyPressMask, key, game);
	mlx_hook(game->mlx.win, ON_DESTROY, NoEventMask, destroy_exit, game);
	mlx_loop(game->mlx.mlx);
}
