/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarad <aalvarad@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by aalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** put_pixel — writes one pixel in an image buffer (NOT on the screen).
** TODO (issue: render / window)
**   - ignore x/y outside [0, width[ / [0, height[
**   - dst = addr + y * line_length + x * (bits_per_pixel / 8)
**   - *(unsigned int *)dst = color
*/
void	put_pixel(t_image *image, int x, int y, int color)
{
	(void)image;
	(void)x;
	(void)y;
	(void)color;
}

/*
** get_texture_pixel — reads the color of one texel of a texture.
** TODO (issue: render / textures)  same address formula as put_pixel
*/
int	get_texture_pixel(t_image *texture, int x, int y)
{
	(void)texture;
	(void)x;
	(void)y;
	return (0);
}
