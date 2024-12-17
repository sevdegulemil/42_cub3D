/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:40 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:50 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_texture_color_f(t_texture *texture)
{
	int	i;

	i = 0;
	while (texture->f.rgb_str_arr[i])
	{
		if (i == 0)
			texture->f.r = ft_atoi(texture->f.rgb_str_arr[i]);
		if (i == 1)
			texture->f.g = ft_atoi(texture->f.rgb_str_arr[i]);
		if (i == 2)
			texture->f.b = ft_atoi(texture->f.rgb_str_arr[i]);
		i++;
	}
	texture->f.count++;
}

void	set_texture_color_c(t_texture *texture)
{
	int	i;

	i = 0;
	while (texture->c.rgb_str_arr[i])
	{
		if (i == 0)
			texture->c.r = ft_atoi(texture->c.rgb_str_arr[i]);
		if (i == 1)
			texture->c.g = ft_atoi(texture->c.rgb_str_arr[i]);
		if (i == 2)
			texture->c.b = ft_atoi(texture->c.rgb_str_arr[i]);
		i++;
	}
	texture->c.count++;
}
