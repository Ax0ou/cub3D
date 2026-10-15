/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/* ---------------------------------------------------------------------------
** Keycodes are NOT the same on macOS (mlx_macos) and Linux (mlx_linux / X11).
** Always use these names in the code, never a raw number.
** ------------------------------------------------------------------------ */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

/* X11 event numbers and masks used with mlx_hook() */
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_DESTROY 17
# define MASK_KEY_PRESS 1
# define MASK_KEY_RELEASE 2
# define MASK_NONE 0

#endif
