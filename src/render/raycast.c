/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/23 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** init_step — direction of the walk in the grid (step) and distance from
** pos to the FIRST x / y grid line the ray will cross (side_dist).
** pos.x - map_x is how far we are inside the cell (0 = left edge).
*/
static void	init_step(t_vec pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - pos.y) * ray->delta_dist.y;
	}
}

/*
** init_ray — prepares the ray of one screen column (DDA, step 1).
** Reference: https://lodev.org/cgtutor/raycasting.html
**   camera_x : -1 = left edge of the screen, 0 = center, +1 = right edge
**   dir      : player.dir + player.plane * camera_x
**   delta_dist: distance along the ray between two x (or two y) grid
**              lines. dir.x == 0 never crosses an x line: huge value.
*/
void	init_ray(t_game *game, t_ray *ray, int screen_x)
{
	t_player	*player;
	double		camera_x;

	player = &game->player;
	camera_x = 2 * screen_x / (double)WIN_WIDTH - 1;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	ray->delta_dist.x = 1e30;
	if (ray->dir.x != 0)
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = 1e30;
	if (ray->dir.y != 0)
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	init_step(player->pos, ray);
}

/*
** is_wall — 1 if the cell stops the ray. A cell outside the map also stops
** it: the parser guarantees a closed map, this is only a safety net so we
** never read outside scene.map.
*/
static int	is_wall(t_scene *scene, int x, int y)
{
	if (x < 0 || y < 0 || x >= scene->map_width || y >= scene->map_height)
		return (1);
	return (scene->map[y][x] == MAP_WALL);
}

/*
** run_dda — walks cell by cell until the ray enters a wall (DDA, step 2).
** At each step we cross the CLOSEST grid line: an x line (we move to the
** cell on the left/right, hit_vertical = 1) or a y line (cell above/below,
** hit_vertical = 0).
*/
void	run_dda(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->hit_vertical = 1;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->hit_vertical = 0;
		}
		if (is_wall(&game->scene, ray->map_x, ray->map_y))
			return ;
	}
}

/*
** compute_wall_distance — perpendicular distance + which face was hit.
**   side_dist went ONE step past the wall line: remove the last delta.
**   This is the distance to the camera PLANE, not to the player: no
**   fisheye (walls in front stay straight).
**   side: map row 0 is the top of the file = north, y grows towards south.
**   wall_x: where the wall was hit, decimal part only, in [0, 1[ (used to
**   pick the texture column in DV-09).
*/
void	compute_wall_distance(t_game *game, t_ray *ray)
{
	t_vec	pos;

	pos = game->player.pos;
	if (ray->hit_vertical)
	{
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
		ray->side = WEST;
		if (ray->dir.x > 0)
			ray->side = EAST;
		ray->wall_x = pos.y + ray->wall_dist * ray->dir.y;
	}
	else
	{
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
		ray->side = NORTH;
		if (ray->dir.y > 0)
			ray->side = SOUTH;
		ray->wall_x = pos.x + ray->wall_dist * ray->dir.x;
	}
	ray->wall_x -= floor(ray->wall_x);
}
