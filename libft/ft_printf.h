/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 06:40:15 by aalvard           #+#    #+#             */
/*   Updated: 2026/02/24 16:56:29 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *fmt, ...);
int	dispatch(char spec, va_list *args);
int	print_pourcent(void);
int	print_char(va_list *args);
int	print_str(va_list *args);
int	print_ptr(va_list *args);
int	print_int(va_list *args);
int	print_unsigned(va_list *args);
int	print_hex(va_list *args);
int	print_hex_upper(va_list *args);
int	helper_int(long n);
int	helper_uint(unsigned long n);
int	helper_hex_lower(unsigned long n);
int	helper_hex_upper(unsigned long n);
int	forty_two(void);

#endif
