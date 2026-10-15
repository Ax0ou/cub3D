/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:27:31 by aalvarad          #+#    #+#             */
/*   Updated: 2025/11/07 10:12:40 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*p;

	p = (const unsigned char *)s;
	while (*p)
		p++;
	while (p >= (const unsigned char *)s)
	{
		if (*p == (unsigned char)c)
			return ((char *)p);
		p--;
	}
	return (NULL);
}
