/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** on_key_press — sets the matching flag in game->keys to 1.
** TODO (issue: game / hooks)
**   KEY_W forward, KEY_S backward, KEY_A strafe_left, KEY_D strafe_right,
**   KEY_LEFT turn_left, KEY_RIGHT turn_right, KEY_ESC -> on_close(game)
*/
int	on_key_press(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

/*
** on_key_release — sets the matching flag in game->keys back to 0.
** TODO (issue: game / hooks)
*/
int	on_key_release(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

/*
** on_close — ESC or red cross: free EVERYTHING then exit(0).
** TODO (issue: game / clean exit)  destroy_game(game); exit(0);
*/
int	on_close(t_game *game)
{
	(void)game;
	return (0);
}

/*
** game_loop — called by MLX in a loop (mlx_loop_hook).
** TODO (issue: game / hooks)
**   update_player(game);
**   render_frame(game);
*/
int	game_loop(t_game *game)
{
	(void)game;
	return (0);
}

/*
** setup_hooks — connects our functions to MLX events.
** TODO (issue: game / hooks)
**   mlx_hook(window, EVENT_KEY_PRESS, MASK_KEY_PRESS, on_key_press, game)
**   mlx_hook(window, EVENT_KEY_RELEASE, MASK_KEY_RELEASE, on_key_release, ...)
**   mlx_hook(window, EVENT_DESTROY, MASK_NONE, on_close, game)
**   mlx_loop_hook(mlx, game_loop, game)
*/
void	setup_hooks(t_game *game)
{
	(void)game;
}
