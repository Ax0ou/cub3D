/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/09 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** print_error — the subject requires "Error\n" then an explicit message.
** Writes on stderr (fd 2) and returns 1, so you can write:
**     return (print_error("duplicate element"));    in main
*/
int	print_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/*
** exit_error — fatal error after MLX is initialised: prints the message,
** frees everything that was created, then quits with status 1.
*/
void	exit_error(t_game *game, char *message)
{
	print_error(message);
	if (game)
		destroy_game(game);
	exit(1);
}
