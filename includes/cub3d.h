/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "keys.h"

/* ---------------------------------------------------------------------------
** Window & gameplay tuning
** ------------------------------------------------------------------------ */
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "cub3D"
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.04
# define FOV_PLANE 0.66

/* ---------------------------------------------------------------------------
** Characters allowed in the map part of a .cub file
** ------------------------------------------------------------------------ */
# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_VOID ' '
# define PLAYER_CHARS "NSEW"

/* ---------------------------------------------------------------------------
** e_side: which face of a wall a ray hit. Also used as the index of
** scene.texture_paths[] and game.textures[].
** ------------------------------------------------------------------------ */
typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	SIDE_COUNT
}	t_side;

/* ---------------------------------------------------------------------------
** e_element: every identifier that can start a line before the map.
** ------------------------------------------------------------------------ */
typedef enum e_element
{
	ELEM_NO,
	ELEM_SO,
	ELEM_WE,
	ELEM_EA,
	ELEM_FLOOR,
	ELEM_CEILING,
	ELEM_COUNT,
	ELEM_UNKNOWN
}	t_element;

/* ---------------------------------------------------------------------------
** t_vec: a 2D vector of doubles (position, direction, camera plane...).
** ------------------------------------------------------------------------ */
typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

/* ---------------------------------------------------------------------------
** t_image: an MLX image + direct access to its pixel buffer.
** Used for the frame we draw into AND for each loaded wall texture.
** ------------------------------------------------------------------------ */
typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

/* ---------------------------------------------------------------------------
** t_scene: everything read from the .cub file. Filled by the parser only.
**   texture_paths : indexed by t_side
**   found         : found[ELEM_xx] == 1 once that element was parsed
**   map           : rectangle of map_height lines, each map_width chars,
**                   short lines are padded with MAP_VOID
**   spawn_x/y     : column/row of the player letter, spawn_dir: 'N'...'W'
** ------------------------------------------------------------------------ */
typedef struct s_scene
{
	char	*texture_paths[SIDE_COUNT];
	int		floor_color;
	int		ceiling_color;
	int		found[ELEM_COUNT];
	char	**map;
	int		map_width;
	int		map_height;
	int		spawn_x;
	int		spawn_y;
	char	spawn_dir;
}	t_scene;

/* ---------------------------------------------------------------------------
** t_player: position in map units + where we look.
**   dir   : unit vector of the view direction
**   plane : camera plane, perpendicular to dir; its length sets the FOV
** ------------------------------------------------------------------------ */
typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

/* ---------------------------------------------------------------------------
** t_ray: all the data of ONE ray (one screen column), DDA algorithm.
**   map_x/map_y   : grid cell the ray is currently in
**   side_dist     : distance from pos to the next x / y grid line
**   delta_dist    : distance between two x / two y grid lines
**   step_x/step_y : +1 or -1, direction of the walk in the grid
**   hit_vertical  : 1 if the wall hit is on a vertical grid line (x side)
**   wall_dist     : perpendicular distance to the wall (no fisheye)
**   wall_x        : where exactly the wall was hit, in [0, 1[
**   line_height   : height of the wall slice on screen
**   draw_start/end: first and last screen row of the slice
** ------------------------------------------------------------------------ */
typedef struct s_ray
{
	t_vec	dir;
	int		map_x;
	int		map_y;
	t_vec	side_dist;
	t_vec	delta_dist;
	int		step_x;
	int		step_y;
	int		hit_vertical;
	t_side	side;
	double	wall_dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* ---------------------------------------------------------------------------
** t_keys: 1 while a key is held down. Lets movement stay smooth and lets
** several keys work at the same time (W + left arrow...).
** ------------------------------------------------------------------------ */
typedef struct s_keys
{
	int	forward;
	int	backward;
	int	strafe_left;
	int	strafe_right;
	int	turn_left;
	int	turn_right;
}	t_keys;

/* ---------------------------------------------------------------------------
** t_game: the root struct. Only ONE exists (in main), everything else
** receives a pointer to it.
** ------------------------------------------------------------------------ */
typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_image		frame;
	t_image		textures[SIDE_COUNT];
	t_scene		scene;
	t_player	player;
	t_keys		keys;
}	t_game;

/* ================================ PARSING ================================ */
/* parsing/parse_scene.c */
int			parse_scene(t_scene *scene, char *path);
int			has_extension(char *path, char *extension);

/* parsing/read_file.c */
char		**read_file_lines(char *path);
char		*strip_newline(char *line);

/* parsing/parse_elements.c */
int			parse_elements(t_scene *scene, char **lines, int *index);
int			parse_texture(t_scene *scene, t_element type, char *value);
t_element	get_element_type(char *line);

/* parsing/parse_color.c */
int			parse_color(char *value, int *color);
int			rgb_to_int(int red, int green, int blue);

/* parsing/parse_map.c */
int			parse_map(t_scene *scene, char **lines, int start);
int			is_map_line(char *line);

/* parsing/check_map.c */
int			check_map_chars(t_scene *scene);
int			check_map_closed(t_scene *scene);

/* ================================ RENDER ================================= */
/* render/init_graphics.c */
int			init_graphics(t_game *game);
int			load_textures(t_game *game);

/* render/render_frame.c */
int			render_frame(t_game *game);
void		draw_ceiling_and_floor(t_game *game);

/* render/raycast.c */
void		init_ray(t_game *game, t_ray *ray, int screen_x);
void		run_dda(t_game *game, t_ray *ray);
void		compute_wall_distance(t_game *game, t_ray *ray);

/* render/draw_wall.c */
void		compute_wall_slice(t_ray *ray);
void		draw_wall_column(t_game *game, t_ray *ray, int screen_x);

/* render/pixel.c */
void		put_pixel(t_image *image, int x, int y, int color);
int			get_texture_pixel(t_image *texture, int x, int y);

/* ================================= GAME ================================== */
/* game/init_player.c */
void		init_player(t_game *game);

/* game/hooks.c */
void		setup_hooks(t_game *game);
int			on_key_press(int keycode, t_game *game);
int			on_key_release(int keycode, t_game *game);
int			on_close(t_game *game);
int			game_loop(t_game *game);

/* game/movement.c */
void		update_player(t_game *game);
void		move_player(t_game *game, double dx, double dy);
void		rotate_player(t_game *game, double angle);

/* ================================= UTILS ================================= */
/* utils/error.c */
int			print_error(char *message);
void		exit_error(t_game *game, char *message);

/* utils/cleanup.c */
void		free_string_array(char **array);
void		free_scene(t_scene *scene);
void		destroy_game(t_game *game);

/* utils/string_utils.c */
int			is_blank_line(char *line);
char		*skip_spaces(char *str);
int			is_space(char c);

/* platform/display_linux.c OR platform/display_macos.c (chosen by Makefile) */
void		destroy_display(void *mlx);

#endif
