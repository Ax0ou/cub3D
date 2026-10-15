/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** strip_newline — removes the trailing '\n' of a line returned by
** get_next_line (in place) and returns the same pointer.
** TODO (issue: parsing / read file)
*/
char	*strip_newline(char *line)
{
	return (line);
}

/*
** read_file_lines — returns every line of the file, without '\n',
** in a NULL-terminated array. NULL on error (open failed, empty file,
** malloc failed) with the error ALREADY printed.
** TODO (issue: parsing / read file)
**   - open() -> if fd < 0: print_error(strerror(errno)) or a clear message
**   - loop on get_next_line() until it returns NULL
**     (ALWAYS read until NULL, even on error: GNL keeps a static buffer,
**      stopping early = leak reported by valgrind)
**   - grow the array (or count lines first, then re-read)
**   - close(fd)
**   - an empty file is an error
**   NB: keep empty lines! "empty line inside the map" must be detected later
*/
char	**read_file_lines(char *path)
{
	(void)path;
	return (NULL);
}
