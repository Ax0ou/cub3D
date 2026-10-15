/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:11:09 by aalvard           #+#    #+#             */
/*   Updated: 2025/11/07 08:45:59 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	len_s;
	size_t	rest;
	size_t	copy_len;

	if (!str)
		return (NULL);
	len_s = ft_strlen(str);
	if (start >= len_s)
		return (ft_strdup(""));
	rest = len_s - start;
	if (len < rest)
		copy_len = len;
	else
		copy_len = rest;
	ptr = ft_calloc(copy_len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, str + start, copy_len);
	ptr[copy_len] = '\0';
	return (ptr);
}
