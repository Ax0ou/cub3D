/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_macos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** destroy_display — macOS version, compiled only on macOS.
** mlx_macos has no mlx_destroy_display(): nothing to free here.
** Leaks are checked on Linux with valgrind (CI + school machines).
*/
void	destroy_display(void *mlx)
{
	(void)mlx;
}
