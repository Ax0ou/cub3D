/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:22:06 by aalvarad          #+#    #+#             */
/*   Updated: 2025/11/07 08:55:07 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		j;

	j = (unsigned char)c;
	p = (const unsigned char *)s;
	while (n > 0)
	{
		if (*p == j)
			return ((void *)p);
		p++;
		n--;
	}
	return (NULL);
}
