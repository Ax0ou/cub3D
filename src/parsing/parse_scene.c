/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/23 13:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** has_extension — 1 if path ends EXACTLY with extension, else 0.
**   - ".cub" alone is not a valid name (nothing before the dot),
**     neither is "maps/.cub"
**   - "map.cub.txt" -> 0, "map.CUB" -> 0, "map.cub" -> 1
**   - also reused to check texture paths end with ".xpm"
*/
int	has_extension(char *path, char *extension)
{
	int	path_len;
	int	ext_len;
	int	start;

	if (!path || !extension)
		return (0);
	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len <= ext_len)
		return (0);
	start = path_len - ext_len;
	if (path[start - 1] == '/')
		return (0);
	if (ft_strncmp(path + start, extension, ext_len) != 0)
		return (0);
	return (1);
}

/*
** parse_scene — reads the whole .cub file and fills scene.
** Returns 1 on success, 0 on error (the error message is ALREADY printed).
**   1. read_file_lines  : every line of the file (NULL -> error)
**   2. parse_elements   : the 6 elements, index stops just after them
**   3. parse_map        : the rest of the file, as a rectangle
**   4. check_map_chars then check_map_closed
** Each step only runs if the previous one succeeded. lines is freed in
** EVERY path. On error the scene may be half filled: main calls
** free_scene(), we free nothing of it here.
*/
int	parse_scene(t_scene *scene, char *path)
{
	char	**lines;
	int		index;
	int		ok;

	lines = read_file_lines(path);
	if (!lines)
		return (0);
	index = 0;
	ok = parse_elements(scene, lines, &index);
	if (ok)
		ok = parse_map(scene, lines, index);
	if (ok)
		ok = check_map_chars(scene);
	if (ok)
		ok = check_map_closed(scene);
	free_string_array(lines);
	return (ok);
}
