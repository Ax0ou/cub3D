/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** destroy_display — Linux (X11) version, compiled only on Linux.
** mlx_init() allocated a display connection + a struct: free both.
*/
void	destroy_display(void *mlx)
{
	if (!mlx)
		return ;
	mlx_destroy_display(mlx);
	free(mlx);
}
