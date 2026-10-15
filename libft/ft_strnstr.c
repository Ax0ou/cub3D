/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:02:46 by aalvarad          #+#    #+#             */
/*   Updated: 2025/11/07 09:23:22 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while (big[i + j] == little[j] && (i + j < len) && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)(&big[i]));
		i++;
		j = 0;
	}
	return (NULL);
}
