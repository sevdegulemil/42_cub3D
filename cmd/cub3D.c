/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:44:47 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/15 17:58:06 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_and_run_game(t_game *game)
{
	initialize_pure_map(game);
	set_player(game);
	start_game(game);
}

t_err	run_map_checks(t_game *game, char *path)
{
	t_err	err;

	err = texture_init(&game->map, path);
	if (err != OK)
		return (perr(__func__, "texture_init failed"), err);
	err = prepare_map_init(&game->map, path);
	if (err != OK)
		return (perr(__func__, "map_init failed"), err);
	err = map_control(&game->map);
	if (err != OK)
		return (perr(__func__, "map_control failed"), err);
	err = map_h(&game->map);
	if (err != OK)
		return (perr(__func__, "map_h failed"), err);
	err = control_player(&game->map);
	if (err != OK)
		return (perr(__func__, "control_reachable_player failed"), err);
	err = map_control_part(&game->map);
	if (err != OK)
		return (perr(__func__, "map_control_part failed"), err);
	err = validate_map(game->map.map_h, game->map.player.direction);
	if (err != OK)
		return (perr(__func__, "validate_map failed"), err);
	return (OK);
}

t_game	*initialize_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		perr(__func__, "malloc failed");
		return (NULL);
	}
	ft_memset(game, 0, sizeof(t_game));
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;
	t_err	err;

	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	err = map_path_control(av[1]);
	if (err != OK)
		return (1);
	game = initialize_game();
	if (!game)
		return (1);
	err = run_map_checks(game, av[1]);
	if (err != OK)
		return (dispose(game), 1);
	initialize_and_run_game(game);
	return (dispose(game), 0);
}
