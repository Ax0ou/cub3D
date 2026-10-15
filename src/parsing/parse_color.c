/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** rgb_to_int — packs 3 components in one int: 0xRRGGBB.
** TODO (issue: parsing / colors)  hint: red << 16 | green << 8 | blue
*/
int	rgb_to_int(int red, int green, int blue)
{
	(void)red;
	(void)green;
	(void)blue;
	return (0);
}

/*
** parse_color — "220,100,0" -> *color = rgb_to_int(220, 100, 0).
** Returns 1 on success, 0 on error (message printed).
** TODO (issue: parsing / colors)
**   errors to detect (see maps/invalid/color_*.cub):
**   - not exactly 3 components            "220,100"   "225,30,0,0"
**   - a component is empty or not digits  "220,,0"    "220,1a0,0"
**   - a component is out of [0, 255]      "220,300,0" "-1,100,0"
**   - spaces INSIDE a number              "225,3 0,0"
**   - do NOT use ft_atoi blindly: it accepts "12abc" and overflows
**   - free every ft_split result
*/
int	parse_color(char *value, int *color)
{
	(void)value;
	(void)color;
	return (1);
}
