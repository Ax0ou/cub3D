/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:00:00 by dbomfim-          #+#    #+#             */
/*   Updated: 2026/10/28 12:00:00 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

/*
** fake_map — a small closed room, already rectangular (FAKE_MAP_WIDTH wide)
** like the parser guarantees. Each row is malloc'd so free_scene works.
*/
static char	**fake_map(void)
{
	static char	*rows[FAKE_MAP_HEIGHT] = {
		"111111",
		"100001",
		"10N001",
		"100101",
		"111111"};
	char		**map;
	int			i;

	map = ft_calloc(FAKE_MAP_HEIGHT + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < FAKE_MAP_HEIGHT)
	{
		map[i] = ft_strdup(rows[i]);
		if (!map[i])
		{
			free_string_array(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

/*
** fake_scene — fills scene by hand, the way parse_scene will, so the engine
** runs before the parser exists. Returns 1 on success, 0 on malloc error.
*/
int	fake_scene(t_scene *scene)
{
	int	i;

	scene->texture_paths[NORTH] = ft_strdup("textures/north.xpm");
	scene->texture_paths[SOUTH] = ft_strdup("textures/south.xpm");
	scene->texture_paths[WEST] = ft_strdup("textures/west.xpm");
	scene->texture_paths[EAST] = ft_strdup("textures/east.xpm");
	scene->floor_color = 0x6E6E6E;
	scene->ceiling_color = 0x87CEEB;
	i = 0;
	while (i < ELEM_COUNT)
		scene->found[i++] = 1;
	scene->map = fake_map();
	scene->map_width = FAKE_MAP_WIDTH;
	scene->map_height = FAKE_MAP_HEIGHT;
	scene->spawn_x = 2;
	scene->spawn_y = 2;
	scene->spawn_dir = 'N';
	i = 0;
	while (i < SIDE_COUNT)
		if (!scene->texture_paths[i++])
			return (0);
	return (scene->map != NULL);
}

/*
** gradient_color — red grows to the right, green grows downwards.
*/
static int	gradient_color(int x, int y)
{
	return ((x * 255 / WIN_WIDTH) << 16 | (y * 255 / WIN_HEIGHT) << 8);
}

/*
** debug_draw — test pattern for init_graphics + put_pixel (DV-01):
** gradient, 1px white border (checks the last row/column), and pixels
** outside the image that must be ignored without crashing.
*/
void	debug_draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (x == 0 || y == 0 || x == WIN_WIDTH - 1 || y == WIN_HEIGHT - 1)
				put_pixel(&game->frame, x, y, 0xFFFFFF);
			else
				put_pixel(&game->frame, x, y, gradient_color(x, y));
			x++;
		}
		y++;
	}
	put_pixel(&game->frame, -1, 0, 0xFF0000);
	put_pixel(&game->frame, WIN_WIDTH, 0, 0xFF0000);
	put_pixel(&game->frame, 0, WIN_HEIGHT, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->window, game->frame.ptr, 0, 0);
}
