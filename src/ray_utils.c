/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:23 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:45 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

float	ray_check_horizontal(t_game *game, t_ray *r)
{
	int	index_y;

	index_y = (int)r->horizontal_y + (r->step_y - 1) / 2;
	if ((int)r->horizontal_x < 0
		|| (int)r->horizontal_x >= game->pure_map.map_width - 1)
		return (INFINITY);
	if (index_y < 0 || index_y >= game->pure_map.map_height - 1)
		return (INFINITY);
	if (game->pure_map.map[index_y][(int)r->horizontal_x] == '1')
		return (save_color(game, r->horizontal_distance, r->step_y + 2,
				r->horizontal_fraction));
	else
		r->horizontal_y += r->step_y;
	return (OK);
}

float	ray_check_vertical(t_game *game, t_ray *r)
{
	int	index_x;

	index_x = (int)r->vertical_x + (r->step_x - 1) / 2;
	if (index_x < 0 || index_x >= game->pure_map.map_width - 1)
		return (INFINITY);
	if ((int)r->vertical_y < 0
		|| (int)r->vertical_y >= game->pure_map.map_height - 1)
		return (INFINITY);
	if (game->pure_map.map[(int)r->vertical_y][index_x] == '1')
		return (save_color(game, r->vertical_distance, r->step_x + 1,
				r->vertical_fraction));
	else
		r->vertical_x += r->step_x;
	return (OK);
}

float	compute_ray_steps(t_game *game, t_ray *r)
{
	float	result;

	while (1)
	{
		ray_next_step_calculation(game, r);
		if (r->vertical_distance < r->horizontal_distance)
		{
			result = ray_check_vertical(game, r);
			if (result != OK)
				return (result);
		}
		else
		{
			result = ray_check_horizontal(game, r);
			if (result != OK)
				return (result);
		}
	}
}

float	initialize_ray(t_game *game, float angle, t_ray *r)
{
	r->delta_x = cos(angle);
	r->delta_y = -sin(angle);
	r->step_x = sign(r->delta_x);
	r->step_y = sign(r->delta_y);
	r->vertical_x = (int)game->pos_x;
	if (r->step_x > 0)
		r->vertical_x += 1.0f;
	r->horizontal_y = (int)game->pos_y;
	if (r->step_y > 0)
		r->horizontal_y += 1.0f;
	return (OK);
}
