/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/18 13:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** has_identifier — 1 if line starts with id AND the next char is a space:
** "NO ./path" -> 1, "NOx" -> 0, "NO" alone -> 0 (no value after it).
*/
static int	has_identifier(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	return (is_space(line[len]));
}

/*
** get_element_type — looks at the identifier at the start of the line
** (after optional spaces) and returns ELEM_NO ... ELEM_CEILING.
** The identifier MUST be followed by at least one space.
** Anything else (map line, garbage, NULL) -> ELEM_UNKNOWN.
*/
t_element	get_element_type(char *line)
{
	if (!line)
		return (ELEM_UNKNOWN);
	line = skip_spaces(line);
	if (has_identifier(line, "NO"))
		return (ELEM_NO);
	if (has_identifier(line, "SO"))
		return (ELEM_SO);
	if (has_identifier(line, "WE"))
		return (ELEM_WE);
	if (has_identifier(line, "EA"))
		return (ELEM_EA);
	if (has_identifier(line, "F"))
		return (ELEM_FLOOR);
	if (has_identifier(line, "C"))
		return (ELEM_CEILING);
	return (ELEM_UNKNOWN);
}

/*
** parse_texture — stores the path of one wall texture.
** Returns 1 on success, 0 on error (message printed).
** value = what is after the identifier, leading spaces already skipped.
**   - trailing spaces are cut IN PLACE (the line is ours, from GNL)
**   - empty value -> error, must end with ".xpm"
**   - the file must exist: open() then close()
**   - ELEM_NO..ELEM_EA have the same values as NORTH..EAST (0..3), so
**     type is used directly as the index of texture_paths[]
**   - the copy is freed by free_scene(), also when a later line fails
*/
int	parse_texture(t_scene *scene, t_element type, char *value)
{
	int	len;
	int	fd;

	len = ft_strlen(value);
	while (len > 0 && is_space(value[len - 1]))
		len--;
	value[len] = '\0';
	if (len == 0)
		return (!print_error("texture path is missing"));
	if (!has_extension(value, ".xpm"))
		return (!print_error("texture must be a .xpm file"));
	fd = open(value, O_RDONLY);
	if (fd < 0)
		return (!print_error("texture file cannot be opened"));
	close(fd);
	scene->texture_paths[type] = ft_strdup(value);
	if (!scene->texture_paths[type])
		return (!print_error("malloc failed"));
	return (1);
}

/*
** parse_element_line — parses ONE non-blank line as an element.
** Returns 1 on success, 0 on error (message printed).
** print_error() returns 1, so "!print_error()" prints and gives 0.
**   - value = what follows the identifier (2 chars for a texture, 1 for
**     F / C), spaces skipped
**   - found[type] is set only if the value was accepted
*/
static int	parse_element_line(t_scene *scene, char *line)
{
	t_element	type;
	char		*value;
	int			ok;

	type = get_element_type(line);
	if (type == ELEM_UNKNOWN && is_map_line(line))
		return (!print_error("map found before the 6 elements"));
	if (type == ELEM_UNKNOWN)
		return (!print_error("unknown identifier"));
	if (scene->found[type])
		return (!print_error("duplicate element"));
	value = skip_spaces(line) + 1;
	if (type < ELEM_FLOOR)
		value++;
	value = skip_spaces(value);
	if (type == ELEM_FLOOR)
		ok = parse_color(value, &scene->floor_color);
	else if (type == ELEM_CEILING)
		ok = parse_color(value, &scene->ceiling_color);
	else
		ok = parse_texture(scene, type, value);
	if (ok)
		scene->found[type] = 1;
	return (ok);
}

/*
** parse_elements — reads lines from *index until the 6 elements are found.
** On return, *index points to the first line AFTER the last element.
** Returns 1 on success, 0 on error (message printed).
**   - blank lines are skipped, the order of the elements is free
**   - a duplicate can never be counted twice (parse_element_line refuses
**     it), so count == ELEM_COUNT means "each of the 6 exactly once"
**   - end of file before the 6 -> error
*/
int	parse_elements(t_scene *scene, char **lines, int *index)
{
	int	count;

	count = 0;
	while (count < ELEM_COUNT && lines[*index])
	{
		if (!is_blank_line(lines[*index]))
		{
			if (!parse_element_line(scene, lines[*index]))
				return (0);
			count++;
		}
		(*index)++;
	}
	if (count < ELEM_COUNT)
		return (!print_error("missing element (NO SO WE EA F C needed)"));
	return (1);
}
