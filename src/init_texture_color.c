/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:46:16 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/15 15:40:00 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	control_texture_color(t_color *color)
{
	if (color->r < 0 || color->r > 255)
		return (perr(__func__, "Invalid color R"));
	if (color->g < 0 || color->g > 255)
		return (perr(__func__, "Invalid color G"));
	if (color->b < 0 || color->b > 255)
		return (perr(__func__, "Invalid color B"));
	if (color->count != 1)
		return (perr(__func__, "Invalid color count."));
	return (OK);
}

t_err	is_invalid_color(char **rgb_str_arr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (rgb_str_arr[i])
	{
		tmp = ft_strtrim(rgb_str_arr[i], "\t\v\f\r\n ");
		if (!tmp || !strevery(&ft_isdigit, tmp) || tmp[0] == '\0')
		{
			free(tmp);
			return (perr(__func__, "Invalid color, not digit"));
		}
		free(rgb_str_arr[i]);
		rgb_str_arr[i] = tmp;
		i++;
	}
	if (i != 3)
	{
		return (perr(__func__, "Invalid rgb count, must be 3"));
	}
	return (OK);
}

t_err	check_texture_color(char *line, t_map *map)
{
	if (!line)
		return (ERR);
	if (!ft_strncmp(line, "F ", 2))
	{
		map->texture.f.rgb_str = ft_strtrim_a(line + 2, " ");
		map->texture.f.rgb_str_arr = ft_split(map->texture.f.rgb_str, ',');
		free(map->texture.f.rgb_str);
		if (!is_invalid_color(map->texture.f.rgb_str_arr))
			return (ERR);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		map->texture.c.rgb_str = ft_strtrim_a(line + 2, " ");
		map->texture.c.rgb_str_arr = ft_split(map->texture.c.rgb_str, ',');
		free(map->texture.c.rgb_str);
		if (!is_invalid_color(map->texture.c.rgb_str_arr))
			return (ERR);
	}
	return (OK);
}
