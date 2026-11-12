/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/09 12:00:00 by aalvarad         ###   ########.fr       */
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
** TODO (issue: game / clean exit)
**   - each texture image (mlx_destroy_image) if not NULL
**   - frame image, window (mlx_destroy_window)
**   - destroy_display(game->mlx)   (already written, one file per OS,
**     see src/platform/ and docs/ARCHITECTURE.md "macOS vs Linux")
**   - free_scene(&game->scene)
*/
void	destroy_game(t_game *game)
{
	(void)game;
}
