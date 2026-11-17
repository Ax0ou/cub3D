/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_string_array — frees a NULL-terminated array of strings + the array.
** Accepts NULL.
*/
void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
** free_scene — frees the 4 texture paths and the map. Accepts a scene
** that is only partially filled (parser error in the middle).
** Freed pointers are set to NULL, so calling it twice is safe.
*/
void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	i = 0;
	while (i < SIDE_COUNT)
	{
		free(scene->texture_paths[i]);
		scene->texture_paths[i] = NULL;
		i++;
	}
	free_string_array(scene->map);
	scene->map = NULL;
}

/*
** destroy_game — frees everything, in the reverse order of creation:
** textures, frame image, window, then the MLX display, then the scene.
** Every pointer is tested: we can get here at any step (exit_error during
** init_graphics, ESC, red cross). Freed pointers are set to NULL, so
** calling it twice is safe.
*/
void	destroy_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < SIDE_COUNT)
	{
		if (game->textures[i].ptr)
			mlx_destroy_image(game->mlx, game->textures[i].ptr);
		game->textures[i].ptr = NULL;
		i++;
	}
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	game->frame.ptr = NULL;
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	game->window = NULL;
	destroy_display(game->mlx);
	game->mlx = NULL;
	free_scene(&game->scene);
}
