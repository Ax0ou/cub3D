/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:06:07 by aalvarad          #+#    #+#             */
/*   Updated: 2025/11/07 09:30:54 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = 0;
	s = ft_strlen(src);
	while (d < size && dst[d])
		d++;
	if (d == size)
		return (size + s);
	i = 0;
	while (i + d + 1 < size && src[i])
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (d + s);
}
