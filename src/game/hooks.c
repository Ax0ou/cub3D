/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/09 13:35:22 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** on_key_press — sets the matching flag in game->keys to 1.
** We only remember that the key is held: the move itself is done once per
** frame by update_player, so it is smooth and several keys work together.
** ESC quits right away. Other keys are ignored.
*/
int	on_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		on_close(game);
	else if (keycode == KEY_W)
		game->keys.forward = 1;
	else if (keycode == KEY_S)
		game->keys.backward = 1;
	else if (keycode == KEY_A)
		game->keys.strafe_left = 1;
	else if (keycode == KEY_D)
		game->keys.strafe_right = 1;
	else if (keycode == KEY_LEFT)
		game->keys.turn_left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.turn_right = 1;
	return (0);
}

/*
** on_key_release — sets the matching flag in game->keys back to 0.
** Same mapping as on_key_press (the norm allows no 6th function here).
*/
int	on_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.forward = 0;
	else if (keycode == KEY_S)
		game->keys.backward = 0;
	else if (keycode == KEY_A)
		game->keys.strafe_left = 0;
	else if (keycode == KEY_D)
		game->keys.strafe_right = 0;
	else if (keycode == KEY_LEFT)
		game->keys.turn_left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.turn_right = 0;
	return (0);
}

/*
** on_close — ESC or red cross: free EVERYTHING then exit(0).
** mlx_loop never returns, so this is the only way out of the program.
*/
int	on_close(t_game *game)
{
	destroy_game(game);
	exit(0);
	return (0);
}

/*
** game_loop — called by MLX in a loop (mlx_loop_hook), once per frame.
*/
int	game_loop(t_game *game)
{
	update_player(game);
	render_frame(game);
	return (0);
}

/*
** setup_hooks — connects our functions to MLX events.
** The mask tells X11 which events the window must listen to. The red cross
** needs no mask: MLX turns the "close window" message into EVENT_DESTROY.
*/
void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, EVENT_KEY_PRESS, MASK_KEY_PRESS,
		on_key_press, game);
	mlx_hook(game->window, EVENT_KEY_RELEASE, MASK_KEY_RELEASE,
		on_key_release, game);
	mlx_hook(game->window, EVENT_DESTROY, MASK_NONE, on_close, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
