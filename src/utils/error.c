/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** print_error — the subject requires "Error\n" then an explicit message.
** Writes on stderr (fd 2) and returns 1, so you can write:
**     return (print_error("duplicate element"));    in main
** TODO (issue: utils / errors)
**   write "Error\n", then message, then "\n" on fd 2
*/
int	print_error(char *message)
{
	(void)message;
	return (1);
}

/*
** exit_error — fatal error after MLX is initialised.
** TODO (issue: utils / errors)  print_error(message); destroy_game(game);
**                               exit(1);
*/
void	exit_error(t_game *game, char *message)
{
	print_error(message);
	(void)game;
	exit(1);
}
