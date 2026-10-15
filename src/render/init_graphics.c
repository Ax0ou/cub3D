/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** init_graphics — opens the window and creates the frame image we draw in.
** Returns 1 on success, 0 on error.
** TODO (issue: render / window)
**   - game->mlx = mlx_init()
**   - game->window = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE)
**   - game->frame.ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT)
**   - game->frame.addr = mlx_get_data_addr(ptr, &bits_per_pixel,
**                                          &line_length, &endian)
**   - frame.width / frame.height = WIN_WIDTH / WIN_HEIGHT
**   We NEVER use mlx_pixel_put: too slow. We write in frame.addr then send
**   the whole image with mlx_put_image_to_window once per frame.
*/
int	init_graphics(t_game *game)
{
	(void)game;
	return (0);
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
