/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/28 15:52:58 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** init_graphics — opens the window and creates the frame image we draw in.
** Returns 1 on success, 0 on error.
** On error we free nothing here: game was zeroed in main, so destroy_game()
** (called by exit_error) only frees what was really created.
** We NEVER use mlx_pixel_put: too slow. We write in frame.addr then send
** the whole image with mlx_put_image_to_window once per frame.
*/
int	init_graphics(t_game *game)
{
	t_image	*frame;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!game->window)
		return (0);
	frame = &game->frame;
	frame->ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!frame->ptr)
		return (0);
	frame->addr = mlx_get_data_addr(frame->ptr, &frame->bits_per_pixel,
			&frame->line_length, &frame->endian);
	if (!frame->addr)
		return (0);
	frame->width = WIN_WIDTH;
	frame->height = WIN_HEIGHT;
	return (1);
}

/*
** load_textures — loads the 4 .xpm walls into game->textures[NORTH..EAST].
** Returns 1 on success, 0 on error.
** TODO (issue: render / textures)
**   - for each side: mlx_xpm_file_to_image(mlx, scene.texture_paths[side],
**                                          &tex.width, &tex.height)
**   - NULL -> error (bad xpm file)
**   - then mlx_get_data_addr() to fill addr / bits_per_pixel / ...
*/
int	load_textures(t_game *game)
{
	(void)game;
	return (1);
}
