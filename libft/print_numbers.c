/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:35:00 by aalvard           #+#    #+#             */
/*   Updated: 2026/02/23 15:35:00 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(va_list *args)
{
	int		tmp;
	long	n;

	tmp = va_arg(*args, int);
	n = (long)tmp;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		return (1 + helper_int(n));
	}
	return (helper_int(n));
}

int	print_unsigned(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (helper_uint(n));
}

int	print_hex(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (helper_hex_lower(n));
}

int	print_hex_upper(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (helper_hex_upper(n));
}
