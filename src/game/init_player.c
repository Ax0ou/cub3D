/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** init_player — converts the spawn found by the parser into a player.
** TODO (issue: game / player init)
**   pos = spawn + 0.5 (center of the cell)
**   y grows DOWNWARDS (row 0 = top of the file):
**     'N' : dir = ( 0, -1)   plane = ( FOV_PLANE, 0)
**     'S' : dir = ( 0,  1)   plane = (-FOV_PLANE, 0)
**     'E' : dir = ( 1,  0)   plane = (0,  FOV_PLANE)
**     'W' : dir = (-1,  0)   plane = (0, -FOV_PLANE)
**   plane must stay perpendicular to dir: check that left arrow really turns
**   left and that the textures are not mirrored.
*/
void	init_player(t_game *game)
{
	(void)game;
}
