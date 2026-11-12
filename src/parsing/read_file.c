/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/10 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** strip_newline — removes the trailing '\n' of a line returned by
** get_next_line (in place) and returns the same pointer.
*/
char	*strip_newline(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

/*
** open_scene_file — opens path read-only. Refuses a directory (open()
** succeeds on a directory, only read() would fail). -1 on error, printed.
*/
static int	open_scene_file(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		print_error("map file is a directory");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(strerror(errno));
	return (fd);
}

/*
** append_line — returns a new array: the count old lines + line + NULL.
** Frees the old array (not its strings). On malloc failure, frees
** everything (old lines + line) and returns NULL.
*/
static char	**append_line(char **lines, int count, char *line)
{
	char	**new_lines;
	int		i;

	new_lines = malloc(sizeof(char *) * (count + 2));
	if (!new_lines)
	{
		free(line);
		free_string_array(lines);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new_lines[i] = lines[i];
		i++;
	}
	new_lines[count] = line;
	new_lines[count + 1] = NULL;
	free(lines);
	return (new_lines);
}

/*
** read_all_lines — reads fd with get_next_line until it returns NULL,
** even after a malloc failure: GNL keeps a static buffer, stopping early
** would leak it. Empty lines are kept (needed to detect an empty line
** inside the map). NULL if the file is empty or malloc failed, printed.
** "count > 0 but lines == NULL" means a malloc failed: we only free the
** remaining lines.
*/
static char	**read_all_lines(int fd)
{
	char	**lines;
	char	*line;
	int		count;

	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (count > 0 && !lines)
			free(line);
		else
			lines = append_line(lines, count, strip_newline(line));
		count++;
		line = get_next_line(fd);
	}
	if (count > 0 && !lines)
		print_error("malloc failed");
	else if (count == 0)
		print_error("map file is empty");
	return (lines);
}

/*
** read_file_lines — returns every line of the file, without '\n',
** in a NULL-terminated array. NULL on error (open failed, directory,
** empty file, malloc failed) with the error ALREADY printed.
*/
char	**read_file_lines(char *path)
{
	int		fd;
	char	**lines;

	fd = open_scene_file(path);
	if (fd < 0)
		return (NULL);
	lines = read_all_lines(fd);
	close(fd);
	return (lines);
}
