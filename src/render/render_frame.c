/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** draw_ceiling_and_floor — top half of the frame = ceiling_color,
** bottom half = floor_color.
** TODO (issue: render / ceiling & floor)  use put_pixel()
*/
void	draw_ceiling_and_floor(t_game *game)
{
	(void)game;
}

/*
** render_frame — draws ONE full image and shows it. Called by game_loop.
** TODO (issue: render / raycasting loop)
**   draw_ceiling_and_floor(game);
**   for screen_x in [0, WIN_WIDTH[:
**       t_ray ray;
**       init_ray(game, &ray, screen_x);
**       run_dda(game, &ray);
**       compute_wall_distance(game, &ray);
**       compute_wall_slice(&ray);
**       draw_wall_column(game, &ray, screen_x);
**   mlx_put_image_to_window(mlx, window, frame.ptr, 0, 0);
**   (no "for" in the norm -> while loop)
*/
int	render_frame(t_game *game)
{
	(void)game;
	return (0);
}
