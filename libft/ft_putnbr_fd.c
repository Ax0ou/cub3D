/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:57:35 by aalvard           #+#    #+#             */
/*   Updated: 2025/11/07 10:57:38 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + '0', fd);
}
