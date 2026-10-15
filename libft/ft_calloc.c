/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:44:17 by aalvarad          #+#    #+#             */
/*   Updated: 2025/11/07 09:28:20 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbrmem, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nbrmem == 0 || size == 0)
		return (malloc(0));
	if (nbrmem > __SIZE_MAX__ / size)
		return (NULL);
	total_size = nbrmem * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
