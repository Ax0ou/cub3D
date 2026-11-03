/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbomfim- <dbomfim-@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by aalvarad          #+#    #+#             */
/*   Updated: 2026/10/28 15:52:58 by dbomfim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** put_pixel — writes one pixel in an image buffer (NOT on the screen).
** Pixels outside the image are ignored (walls very close give negative or
** too big rows). line_length is in bytes and may include padding: never
** replace it with width * 4.
*/
void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	dst = image->addr + y * image->line_length
		+ x * (image->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
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
