/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/23 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** draw_ceiling_and_floor — top half of the frame = ceiling_color,
** bottom half = floor_color.
** Drawn first, every frame: the walls are then drawn on top of it.
*/
void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		color = game->scene.ceiling_color;
		if (y >= WIN_HEIGHT / 2)
			color = game->scene.floor_color;
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&game->frame, x, y, color);
			x++;
		}
		y++;
	}
}

/*
** render_frame — draws ONE full image and shows it. Called by game_loop.
** Background first, then one ray per screen column draws its wall slice
** on top. The image is sent to the window only once, at the end.
*/
int	render_frame(t_game *game)
{
	t_ray	ray;
	int		screen_x;

	draw_ceiling_and_floor(game);
	screen_x = 0;
	while (screen_x < WIN_WIDTH)
	{
		init_ray(game, &ray, screen_x);
		run_dda(game, &ray);
		compute_wall_distance(game, &ray);
		compute_wall_slice(&ray);
		draw_wall_column(game, &ray, screen_x);
		screen_x++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->frame.ptr, 0, 0);
	return (0);
}
