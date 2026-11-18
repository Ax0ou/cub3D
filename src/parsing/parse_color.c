/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/11/18 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** rgb_to_int — packs 3 components in one int: 0xRRGGBB.
** Each component is 8 bits: red goes to bits 16-23, green to 8-15,
** blue to 0-7.
*/
int	rgb_to_int(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

/*
** read_component — reads ONE number in [0, 255] at *str and moves *str
** after it. Spaces are accepted before and after the number, never inside.
** Returns 1 on success, 0 if there is no digit or the value is > 255.
**   - no ft_atoi: it accepts "-1" and "12abc", and overflows
**   - the "> 255" test is INSIDE the loop, so the int can never overflow,
**     even with "99999999999999999999"
*/
static int	read_component(char **str, int *value)
{
	char	*cursor;

	cursor = skip_spaces(*str);
	if (!ft_isdigit(*cursor))
		return (0);
	*value = 0;
	while (ft_isdigit(*cursor))
	{
		*value = *value * 10 + (*cursor - '0');
		if (*value > 255)
			return (0);
		cursor++;
	}
	*str = skip_spaces(cursor);
	return (1);
}

/*
** parse_color — "220,100,0" -> *color = rgb_to_int(220, 100, 0).
** Returns 1 on success, 0 on error (message printed).
** No malloc (no ft_split): we walk the string with one pointer.
**   - 3 numbers, with a ',' after the 1st and the 2nd
**   - after the 3rd the string must be finished: "1,2,3,4" and "1,2,3x"
**     are errors
**   - "225,3 0,0": after "3" and its spaces we expect ',' and find '0'
*/
int	parse_color(char *value, int *color)
{
	int	rgb[3];
	int	i;

	if (!value || !color)
		return (!print_error("invalid color"));
	i = 0;
	while (i < 3)
	{
		if (!read_component(&value, &rgb[i]))
			return (!print_error("color component must be in [0,255]"));
		if (i < 2 && *value != ',')
			return (!print_error("color needs 3 components R,G,B"));
		if (i < 2)
			value++;
		i++;
	}
	if (*value != '\0')
		return (!print_error("color needs 3 components R,G,B"));
	*color = rgb_to_int(rgb[0], rgb[1], rgb[2]);
	return (1);
}
