/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/19 13:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_cell — checks ONE cell of the map. Returns 1, or 0 on error.
**   - player letter: its position and direction are saved in the scene,
**     the letter becomes MAP_EMPTY ('0') and *players is incremented
**   - anything that is not '0', '1' or ' ' -> error (printed)
*/
static int	check_cell(t_scene *scene, int x, int y, int *players)
{
	char	c;

	c = scene->map[y][x];
	if (ft_strchr(PLAYER_CHARS, c))
	{
		scene->spawn_x = x;
		scene->spawn_y = y;
		scene->spawn_dir = c;
		scene->map[y][x] = MAP_EMPTY;
		(*players)++;
	}
	else if (c != MAP_EMPTY && c != MAP_WALL && c != MAP_VOID)
		return (!print_error("invalid character in map"));
	return (1);
}

/*
** check_map_chars — every cell is one of "01 NSEW" and there is EXACTLY one
** player. Saves its position in scene->spawn_x / spawn_y / spawn_dir and
** replaces the letter by MAP_EMPTY ('0') in the map.
** The map is a rectangle (parse_map), so map[y][x] always exists for
** y < map_height and x < map_width.
*/
int	check_map_chars(t_scene *scene)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (y < scene->map_height)
	{
		x = 0;
		while (x < scene->map_width)
		{
			if (!check_cell(scene, x, y, &players))
				return (0);
			x++;
		}
		y++;
	}
	if (players == 0)
		return (!print_error("no player in map (N, S, E or W)"));
	if (players > 1)
		return (!print_error("more than one player in map"));
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
