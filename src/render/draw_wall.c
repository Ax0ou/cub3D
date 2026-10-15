/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** compute_wall_slice — height and vertical position of the wall on screen.
** TODO (issue: render / wall slice)
**   line_height = (int)(WIN_HEIGHT / wall_dist)
**   draw_start  = WIN_HEIGHT / 2 - line_height / 2   (clamp to 0)
**   draw_end    = WIN_HEIGHT / 2 + line_height / 2   (clamp to WIN_HEIGHT - 1)
*/
void	compute_wall_slice(t_ray *ray)
{
	(void)ray;
}

/*
** draw_wall_column — draws the textured wall slice of one screen column.
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
**   First version (week 2): draw a plain color per side, no texture.
*/
void	draw_wall_column(t_game *game, t_ray *ray, int screen_x)
{
	(void)game;
	(void)ray;
	(void)screen_x;
}
