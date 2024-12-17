/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:46:10 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:17 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	flood_fill(char **map, int x, int y, char p)
{
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
		return ;
	if (map[y][x] == 'H')
		return ;
	if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == p)
		map[y][x] = 'K';
	else
		return ;
	flood_fill(map, x + 1, y, p);
	flood_fill(map, x - 1, y, p);
	flood_fill(map, x, y + 1, p);
	flood_fill(map, x, y - 1, p);
}

bool	is_one_or_space(char c)
{
	return (c == '1' || c == ' ');
}

bool	all_chars_are(char *str)
{
	while (*str)
	{
		if (!is_one_or_space(*str))
			return (false);
		str++;
	}
	return (true);
}
