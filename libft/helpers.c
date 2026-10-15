/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:35:00 by aalvard           #+#    #+#             */
/*   Updated: 2026/04/06 13:02:13 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	helper_hex_lower(unsigned long n)
{
	int			i;
	int			count;
	const char	*base;

	base = "0123456789abcdef";
	count = 0;
	i = (n % 16);
	if (n >= 16)
		count += helper_hex_lower(n / 16);
	write(1, &base[i], 1);
	count++;
	return (count);
}

int	helper_hex_upper(unsigned long n)
{
	int			i;
	int			count;
	const char	*base;

	base = "0123456789ABCDEF";
	count = 0;
	i = (n % 16);
	if (n >= 16)
		count += helper_hex_upper(n / 16);
	write(1, &base[i], 1);
	count++;
	return (count);
}

int	helper_int(long n)
{
	int			i;
	int			count;
	const char	*base;

	base = "0123456789";
	count = 0;
	i = (n % 10);
	if (n >= 10)
		count += helper_int(n / 10);
	write(1, &base[i], 1);
	count++;
	return (count);
}

int	helper_uint(unsigned long n)
{
	int			i;
	int			count;
	const char	*base;

	base = "0123456789";
	count = 0;
	i = (n % 10);
	if (n >= 10)
		count += helper_uint(n / 10);
	write(1, &base[i], 1);
	count++;
	return (count);
}

int	forty_two(void)
{
	write(1, "42", 2);
	return (2);
}
