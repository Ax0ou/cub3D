/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/23 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** compute_wall_slice — height and vertical position of the wall on screen.
**   line_height = WIN_HEIGHT / wall_dist: a wall 1 cell away fills the
**   screen height, 2 cells away half of it...
**   The slice is centered on the horizon (WIN_HEIGHT / 2), then clamped to
**   the screen: a very close wall is taller than the window.
**   wall_dist is kept above a tiny minimum so the division can never give
**   a value too big for an int.
*/
void	compute_wall_slice(t_ray *ray)
{
	if (ray->wall_dist < 0.0001)
		ray->wall_dist = 0.0001;
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = WIN_HEIGHT / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/*
** side_color — one plain color per face, until the textures (DV-09).
*/
static int	side_color(t_side side)
{
	if (side == NORTH)
		return (0xC0392B);
	if (side == SOUTH)
		return (0x27AE60);
	if (side == WEST)
		return (0x2980B9);
	return (0xF1C40F);
}

/*
** draw_wall_column — draws the wall slice of one screen column.
** Version 1 (DV-07): a plain color per side (N red, S green, W blue,
** E yellow).
** TODO (issue: render / textures)
**   texture = &game->textures[ray->side]
**   tex_x = (int)(wall_x * texture->width)
**   flip tex_x for 2 of the 4 sides, otherwise those textures are mirrored
**   (tex_x = texture->width - tex_x - 1)
**   step    = texture->height / (double)line_height
**   tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step
**   for y in [draw_start, draw_end]:
**       tex_y = (int)tex_pos (clamp to height - 1); tex_pos += step
**       put_pixel(&frame, screen_x, y, get_texture_pixel(texture, tex_x, tex_y))
*/
void	draw_wall_column(t_game *game, t_ray *ray, int screen_x)
{
	int	y;
	int	color;

	color = side_color(ray->side);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(&game->frame, screen_x, y, color);
		y++;
	}
}
