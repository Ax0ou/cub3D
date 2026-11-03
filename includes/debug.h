/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:00:00 by dbomfim-          #+#    #+#             */
/*   Updated: 2026/10/28 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DEBUG — temporary engine helpers. NEVER merge on dev (docs/ROADMAP.md):
** remove this file, src/debug/ and their lines in main.c / Makefile once
** parse_scene is done (DUO-05).
*/
#ifndef DEBUG_H
# define DEBUG_H

# include "cub3d.h"

# define FAKE_MAP_WIDTH 6
# define FAKE_MAP_HEIGHT 5

int		fake_scene(t_scene *scene);
void	debug_draw(t_game *game);

#endif
