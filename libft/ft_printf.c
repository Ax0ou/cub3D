/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 06:43:48 by aalvard           #+#    #+#             */
/*   Updated: 2026/02/23 15:28:32 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	int		total;
	va_list	args;

	va_start(args, fmt);
	total = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			write(1, fmt, 1);
			total++;
			fmt++;
		}
		else
		{
			fmt++;
			if (*fmt == '\0')
				break ;
			total += dispatch(*fmt, &args);
			fmt++;
		}
	}
	va_end(args);
	return (total);
}
