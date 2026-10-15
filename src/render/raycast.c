/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** init_ray — prepares the ray of one screen column (DDA, step 1).
** Reference: https://lodev.org/cgtutor/raycasting.html
** TODO (issue: render / raycasting DDA)
**   camera_x  = 2 * screen_x / (double)WIN_WIDTH - 1      (-1 left, +1 right)
**   ray->dir  = player.dir + player.plane * camera_x
**   ray->map_x / map_y = (int)player.pos.x / (int)player.pos.y
**   delta_dist.x = fabs(1 / dir.x)   (if dir.x == 0 -> use a huge value 1e30)
**   delta_dist.y = fabs(1 / dir.y)
**   step_x = -1 and side_dist.x = (pos.x - map_x) * delta_dist.x  if dir.x < 0
**   step_x = +1 and side_dist.x = (map_x + 1 - pos.x) * delta_dist.x  else
**   same for y
*/
void	init_ray(t_game *game, t_ray *ray, int screen_x)
{
	(void)game;
	(void)ray;
	(void)screen_x;
}

/*
** run_dda — walks cell by cell until the ray enters a wall (DDA, step 2).
** TODO (issue: render / raycasting DDA)
**   while no wall hit:
**     if side_dist.x < side_dist.y:
**         side_dist.x += delta_dist.x; map_x += step_x; hit_vertical = 1
**     else:
**         side_dist.y += delta_dist.y; map_y += step_y; hit_vertical = 0
**     wall hit if scene.map[map_y][map_x] == MAP_WALL
**   The parser guarantees the map is closed -> the loop always ends.
*/
void	run_dda(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}

/*
** compute_wall_distance — perpendicular distance + which face was hit.
** TODO (issue: render / raycasting DDA)
**   hit_vertical: wall_dist = side_dist.x - delta_dist.x
**   else        : wall_dist = side_dist.y - delta_dist.y
**   (perpendicular distance = no fisheye effect)
**   ray->side: hit_vertical -> dir.x > 0 ? EAST : WEST
**              else         -> dir.y > 0 ? SOUTH : NORTH
**   (map row 0 is the top of the file = north, so y grows towards south)
**   wall_x = exact hit position on the wall, keep only the decimal part:
**     hit_vertical: pos.y + wall_dist * dir.y   else: pos.x + wall_dist * dir.x
**     wall_x -= floor(wall_x)
*/
void	compute_wall_distance(t_game *game, t_ray *ray)
{
	(void)game;
	(void)ray;
}
