/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_map_chars — every cell is one of "01 NSEW" and there is EXACTLY one
** player. Saves its position in scene->spawn_x / spawn_y / spawn_dir and
** replaces the letter by MAP_EMPTY ('0') in the map.
** TODO (issue: parsing / map validation)
**   errors: maps/invalid/map_invalid_char.cub, map_no_player.cub,
**           map_two_players.cub
*/
int	check_map_chars(t_scene *scene)
{
	(void)scene;
	return (1);
}

/*
** check_map_closed — the player must not be able to "walk out" of the map.
** TODO (issue: parsing / map validation)
**   Simple rule (no flood fill needed): for every walkable cell ('0' and
**   the spawn), the 4 neighbours (up, down, left, right) must exist and
**   must NOT be MAP_VOID (' ').
**   -> a '0' on the first/last row or column = open map
**   -> a '0' next to a ' ' = hole in the wall
**   errors: maps/invalid/map_open_wall.cub, map_space_hole.cub,
**           map_player_on_border.cub
**   Optional alternative: flood fill from the spawn on a COPY of the map.
*/
int	check_map_closed(t_scene *scene)
{
	(void)scene;
	return (1);
}
