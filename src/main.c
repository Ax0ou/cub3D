/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** main — the glue between the 3 big modules. Already written: it is the
** contract between parsing (person A) and render/game (person B).
**
**   1. check argc == 2 and that argv[1] ends with ".cub"
**   2. parse_scene()  -> fills game.scene, or prints "Error\n..." and fails
**   3. init_player()  -> converts scene.spawn_* into player pos/dir/plane
**   4. init_graphics() + load_textures() -> window, frame image, 4 textures
**   5. setup_hooks()  -> keys, red cross, game_loop
**   6. mlx_loop()     -> never returns: we leave through on_close()
*/
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (print_error("usage: ./cub3D <map.cub>"));
	if (!has_extension(argv[1], ".cub"))
		return (print_error("map file must end with .cub"));
	if (!parse_scene(&game.scene, argv[1]))
	{
		free_scene(&game.scene);
		return (1);
	}
	init_player(&game);
	if (!init_graphics(&game) || !load_textures(&game))
		exit_error(&game, "could not initialise graphics");
	setup_hooks(&game);
	mlx_loop(game.mlx);
	destroy_game(&game);
	return (0);
}
