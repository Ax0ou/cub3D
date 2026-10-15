/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 21:41:00 by aalvard           #+#    #+#             */
/*   Updated: 2026/04/06 13:02:13 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dispatch(char spec, va_list *args)
{
	if (spec == '%')
		return (print_pourcent());
	if (spec == 'c')
		return (print_char(args));
	if (spec == 's')
		return (print_str(args));
	if (spec == 'p')
		return (print_ptr(args));
	if (spec == 'd' || spec == 'i')
		return (print_int(args));
	if (spec == 'u')
		return (print_unsigned(args));
	if (spec == 'x')
		return (print_hex(args));
	if (spec == 'X')
		return (print_hex_upper(args));
	if (spec == 'a')
		return (forty_two());
	return (0);
}

int	print_pourcent(void)
{
	char	c;

	c = '%';
	write(1, &c, 1);
	return (1);
}

int	print_char(va_list *args)
{
	unsigned char	c;
	int				value;

	value = va_arg(*args, int);
	c = value;
	write(1, &c, 1);
	return (1);
}

int	print_str(va_list *args)
{
	char	*ptr;
	int		count;

	count = 0;
	ptr = va_arg(*args, char *);
	if (ptr == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*ptr)
	{
		write(1, ptr, 1);
		ptr++;
		count++;
	}
	return (count);
}

int	print_ptr(va_list *args)
{
	void			*ptr;
	unsigned long	addr;

	ptr = va_arg(*args, void *);
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	if (ptr == NULL)
	{
		write(1, "0", 1);
		return (3);
	}
	return (2 + helper_hex_lower(addr));
}
