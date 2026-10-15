/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** has_extension — 1 if path ends EXACTLY with extension, else 0.
** TODO (issue: parsing / arguments)
**   - ".cub" alone is not a valid name (nothing before the dot)
**   - "map.cub.txt" -> 0, "map.CUB" -> 0, "map.cub" -> 1
**   - also reused to check texture paths end with ".xpm"
*/
int	has_extension(char *path, char *extension)
{
	(void)path;
	(void)extension;
	return (1);
}

/*
** parse_scene — reads the whole .cub file and fills scene.
** Returns 1 on success, 0 on error (the error message is ALREADY printed).
** TODO (issue: parsing / orchestration)
**   1. lines = read_file_lines(path)            (NULL -> error)
**   2. index = 0; parse_elements(scene, lines, &index)
**      -> must end with the 6 elements found exactly once
**   3. skip blank lines, then parse_map(scene, lines, index)
**   4. check_map_chars(scene) then check_map_closed(scene)
**   5. free_string_array(lines) in EVERY path (success and errors)
*/
int	parse_scene(t_scene *scene, char *path)
{
	(void)scene;
	(void)path;
	return (1);
}
