/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:03 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:27 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

float	calculate_ray_distance(t_game *game, float current_angle)
{
	t_ray	ray;
	t_err	err;

	err = initialize_ray(game, current_angle, &ray);
	if (err != OK)
		return (INFINITY);
	return (compute_ray_steps(game, &ray));
}

void	move(t_game *game, int direction)
{
	float	dist;
	float	dx;
	float	dy;
	float	angle;

	angle = game->angle_view + direction * M_PI / 2;
	dx = LINEAR_STEP * cos(angle);
	dy = LINEAR_STEP * sin(angle);
	dist = calculate_ray_distance(game, sign(dy) * M_PI / 2);
	if (dist * dist < dy * dy)
		dy = 0.0f;
	dist = calculate_ray_distance(game, (1 - (sign(dx) + 1) / 2) * M_PI);
	if (dist * dist < dx * dx)
		dx = 0.0f;
	dist = calculate_ray_distance(game, angle);
	if (dist * dist < dy * dy + dx * dx)
		if (sign(dy) * sign(dx) != 0)
			dy = 0.0f;
	game->pos_x += dx;
	game->pos_y -= dy;
}

int	key(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		destroy_exit(game);
	else if (keycode == ARROW_UP || keycode == KEY_W)
		move(game, 0);
	else if (keycode == ARROW_DOWN || keycode == KEY_S)
		move(game, 2);
	else if (keycode == ARROW_LEFT)
		game->angle_view -= ANGLE_STEP * M_PI;
	else if (keycode == ARROW_RIGHT)
		game->angle_view += ANGLE_STEP * M_PI;
	else if (keycode == KEY_A)
		move(game, 3);
	else if (keycode == KEY_D)
		move(game, 1);
	else
		return (0);
	draw(game);
	return (0);
}
