/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 08:00:40 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:42:53 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that writes a conversion specification of type c.
 */
int	write_c(va_list args, t_options *opts)
{
	unsigned char	c;
	int				i;

	c = (unsigned char) va_arg(args, int);
	i = 0;
	if (opts->width <= 1)
		ft_putchar_fd(c, 1);
	else
	{
		if (opts->minus == '1')
			ft_putchar_fd(c, 1);
		while (i < opts->width - 1)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		if (opts->minus == '0')
			ft_putchar_fd(c, 1);
	}
	return (i + 1);
}
