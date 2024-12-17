/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_ray_cast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:49 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:10 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	draw_vertical_line(t_game *game, int w, float dist)
{
	unsigned int	*dst;
	unsigned int	*src;
	unsigned int	line_height;
	float			texture_pos;
	float			texture_step;

	line_height = (float)HEIGHT / dist + 0.5f;
	texture_pos = 0.0f;
	texture_step = (float)game->txt[game->txt_idx].height / line_height;
	if (line_height > HEIGHT)
	{
		texture_pos = 0.5f * (line_height - HEIGHT) / line_height
			* game->txt[game->txt_idx].height;
		line_height = HEIGHT;
	}
	src = (unsigned int *)game->txt[game->txt_idx].addr;
	src += (int)((float)game->txt_w * game->txt[game->txt_idx].width);
	dst = (unsigned int *)game->img_w.addr + w + (HEIGHT - line_height) / 2
		* WIDTH;
	while (line_height-- > 0)
	{
		*dst = *(src + ((int)texture_pos) * game->txt[game->txt_idx].width);
		dst += WIDTH;
		texture_pos += texture_step;
	}
}

void	ray_casting(t_game *game)
{
	int		x;
	float	delta_angle;
	float	current_angle;
	float	ray_distance;

	current_angle = game->angle_view - FOV / 2;
	delta_angle = FOV / (WIDTH - 1);
	x = -1;
	while (++x < WIDTH)
	{
		ray_distance = calculate_ray_distance(game, current_angle);
		if (ray_distance == INFINITY)
			ray_distance = 0.1f;
		if (ray_distance < 0.1f)
			ray_distance = 0.1f;
		draw_vertical_line(game, x, ray_distance * cos(game->angle_view
				- current_angle));
		current_angle += delta_angle;
	}
}

void	draw_ceiling_and_floor(t_game *game)
{
	unsigned int	*pixel_ptr;
	unsigned int	i;

	pixel_ptr = (unsigned int *)game->img_w.addr;
	i = WIDTH * HEIGHT / 2;
	while (--i > 0)
		*pixel_ptr++ = game->color_ceiling;
	i = WIDTH * HEIGHT / 2;
	while (--i > 0)
		*pixel_ptr++ = game->color_floor;
}
