/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:51 by aalvard           #+#    #+#             */
/*   Updated: 2025/11/07 09:17:46 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*p;
	unsigned char		ch;
	int					i;

	ch = (unsigned char)c;
	p = (const unsigned char *)s;
	i = 0;
	while (p[i])
	{
		if (p[i] == ch)
			return ((char *)&p[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&p[i]);
	return (NULL);
}
