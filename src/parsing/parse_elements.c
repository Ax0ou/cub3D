/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** get_element_type — looks at the identifier at the start of the line
** (after optional spaces) and returns ELEM_NO ... ELEM_CEILING.
** TODO (issue: parsing / elements)
**   - "NO " -> ELEM_NO, "SO " -> ELEM_SO, "WE " -> ELEM_WE, "EA " -> ELEM_EA
**   - "F "  -> ELEM_FLOOR,   "C " -> ELEM_CEILING
**   - the identifier MUST be followed by at least one space
**   - anything else -> ELEM_UNKNOWN
*/
t_element	get_element_type(char *line)
{
	(void)line;
	return (ELEM_UNKNOWN);
}

/*
** parse_texture — stores the path of one wall texture.
** TODO (issue: parsing / textures)
**   - value = what is after the identifier, spaces skipped
**   - trim trailing spaces; empty value -> error
**   - must end with ".xpm" (has_extension)
**   - the file must exist: try open() then close()
**   - type ELEM_NO -> scene->texture_paths[NORTH] = ft_strdup(value), etc.
**   Returns 1 on success, 0 on error (message printed).
*/
int	parse_texture(t_scene *scene, t_element type, char *value)
{
	(void)scene;
	(void)type;
	(void)value;
	return (1);
}

/*
** parse_elements — reads lines from *index until the 6 elements are found.
** On return, *index points to the first line AFTER the last element.
** TODO (issue: parsing / elements)
**   - skip blank lines (is_blank_line)
**   - type = get_element_type(line)
**       ELEM_UNKNOWN          -> error ("unknown identifier" or
**                                "map before elements" if is_map_line)
**       scene->found[type]==1 -> error "duplicate element"
**   - texture -> parse_texture, F / C -> parse_color
**   - set scene->found[type] = 1
**   - stop as soon as the 6 are found; if the file ends before -> error
*/
int	parse_elements(t_scene *scene, char **lines, int *index)
{
	(void)scene;
	(void)lines;
	(void)index;
	return (1);
}
