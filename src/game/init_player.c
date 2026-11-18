/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** init_player — converts the spawn found by the parser into a player.
**   pos = spawn + 0.5 (center of the cell)
**   y grows DOWNWARDS (row 0 = top of the file):
**     'N' : dir = ( 0, -1)   plane = ( FOV_PLANE, 0)
**     'S' : dir = ( 0,  1)   plane = (-FOV_PLANE, 0)
**     'E' : dir = ( 1,  0)   plane = (0,  FOV_PLANE)
**     'W' : dir = (-1,  0)   plane = (0, -FOV_PLANE)
** plane is dir turned 90 degrees to the RIGHT, (-dir.y, dir.x), scaled by
** FOV_PLANE: that gives the 4 lines above. Pointing right is what makes the
** left of the screen show what is on the player's left (no mirror).
*/
void	init_player(t_game *game)
{
	t_player	*player;
	char		spawn_dir;

	player = &game->player;
	spawn_dir = game->scene.spawn_dir;
	player->pos.x = game->scene.spawn_x + 0.5;
	player->pos.y = game->scene.spawn_y + 0.5;
	player->dir.x = 0;
	player->dir.y = 0;
	if (spawn_dir == 'N')
		player->dir.y = -1;
	else if (spawn_dir == 'S')
		player->dir.y = 1;
	else if (spawn_dir == 'E')
		player->dir.x = 1;
	else if (spawn_dir == 'W')
		player->dir.x = -1;
	player->plane.x = -player->dir.y * FOV_PLANE;
	player->plane.y = player->dir.x * FOV_PLANE;
}
