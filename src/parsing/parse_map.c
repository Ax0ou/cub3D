/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** is_map_line — 1 if the line only contains map characters
** ('0', '1', ' ', 'N', 'S', 'E', 'W') and at least one non-space.
** TODO (issue: parsing / map)
*/
int	is_map_line(char *line)
{
	(void)line;
	return (0);
}

/*
** parse_map — copies lines[start..] into scene->map as a RECTANGLE.
** TODO (issue: parsing / map)
**   - map_height = number of lines until the end of the file
**     (trailing blank lines at the very end of the file can be ignored)
**   - a blank line INSIDE the map -> error (maps/invalid/
**     map_empty_line_inside.cub)
**   - no map at all -> error (maps/invalid/map_missing.cub)
**   - map_width = length of the longest line
**   - every row is malloc'ed with map_width chars + '\0', and padded with
**     MAP_VOID (' ') -> later code never reads outside a row
**   - the map array itself is NULL-terminated (free_string_array works)
*/
int	parse_map(t_scene *scene, char **lines, int start)
{
	(void)scene;
	(void)lines;
	(void)start;
	return (1);
}
