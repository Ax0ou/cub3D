/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** move_player — tries to move the player by (dx, dy).
** TODO (issue: game / movement)
**   - only move if the destination cell is not a wall
**   - test x and y SEPARATELY: the player slides along walls instead of
**     getting stuck (and keep a small margin so the camera never enters
**     a wall)
*/
void	move_player(t_game *game, double dx, double dy)
{
	(void)game;
	(void)dx;
	(void)dy;
}

/*
** rotate_player — rotates dir AND plane by angle (radians).
** TODO (issue: game / movement)
**   rotation matrix:  x' = x * cos(a) - y * sin(a)
**                     y' = x * sin(a) + y * cos(a)
**   save the old x before computing y!
*/
void	rotate_player(t_game *game, double angle)
{
	(void)game;
	(void)angle;
}

/*
** update_player — applies every held key, once per frame.
** TODO (issue: game / movement)
**   forward : move_player(dir * MOVE_SPEED)
**   backward: move_player(-dir * MOVE_SPEED)
**   strafe  : move along the perpendicular of dir: (-dir.y, dir.x)
**   turn    : rotate_player(+/- ROT_SPEED)
*/
void	update_player(t_game *game)
{
	(void)game;
}
