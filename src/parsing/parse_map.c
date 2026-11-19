/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** is_map_line — 1 if the line only contains map characters
** ('0', '1', ' ', 'N', 'S', 'E', 'W') and at least one non-space.
** Used by parse_elements to say "map found before the 6 elements".
*/
int	is_map_line(char *line)
{
	int	i;
	int	has_content;

	if (!line)
		return (0);
	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (!ft_strchr("01 NSEW", line[i]))
			return (0);
		if (line[i] != MAP_VOID)
			has_content = 1;
		i++;
	}
	return (has_content);
}

/*
** count_map_lines — number of lines from lines[0] to the LAST non-blank
** line of the file: blank lines at the very end are ignored, blank lines
** in the middle are counted (longest_line refuses them just after).
** 0 means there is no map at all.
*/
static int	count_map_lines(char **lines)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (lines[i])
	{
		if (!is_blank_line(lines[i]))
			height = i + 1;
		i++;
	}
	return (height);
}

/*
** longest_line — length of the longest of the first height lines
** (= map_width). Returns -1 if one of them is blank: a blank line inside
** the map is an error.
*/
static int	longest_line(char **lines, int height)
{
	int	i;
	int	len;
	int	width;

	i = 0;
	width = 0;
	while (i < height)
	{
		if (is_blank_line(lines[i]))
			return (-1);
		len = ft_strlen(lines[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

/*
** make_row — copy of line in a new string of EXACTLY width chars: the end
** is padded with MAP_VOID (' '). NULL if malloc failed.
** line is never longer than width (width is the longest line).
*/
static char	*make_row(char *line, int width)
{
	char	*row;

	row = malloc(width + 1);
	if (!row)
		return (NULL);
	ft_memset(row, MAP_VOID, width);
	ft_memcpy(row, line, ft_strlen(line));
	row[width] = '\0';
	return (row);
}

/*
** parse_map — copies lines[start..] into scene->map as a RECTANGLE of
** map_height rows of map_width chars. Returns 1, or 0 on error (printed).
**   - blank lines before the map are skipped
**   - no map -> error, blank line inside the map -> error
**   - ft_calloc fills the array with NULL: it is NULL-terminated, and if a
**     row malloc fails, free_scene() frees the rows already copied
**   - characters are NOT checked here: check_map_chars does it
*/
int	parse_map(t_scene *scene, char **lines, int start)
{
	int	i;

	while (lines[start] && is_blank_line(lines[start]))
		start++;
	scene->map_height = count_map_lines(lines + start);
	if (scene->map_height == 0)
		return (!print_error("map is missing"));
	scene->map_width = longest_line(lines + start, scene->map_height);
	if (scene->map_width < 0)
		return (!print_error("empty line inside the map"));
	scene->map = ft_calloc(scene->map_height + 1, sizeof(char *));
	if (!scene->map)
		return (!print_error("malloc failed"));
	i = 0;
	while (i < scene->map_height)
	{
		scene->map[i] = make_row(lines[start + i], scene->map_width);
		if (!scene->map[i])
			return (!print_error("malloc failed"));
		i++;
	}
	return (1);
}
