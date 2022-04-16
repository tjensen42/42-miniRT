/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 08:49:22 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:50:04 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that writes a conversion specification of type %.
 */
int	write_percent(t_options *opts)
{
	int	i;

	i = 0;
	if (opts->width <= 1)
		ft_putchar_fd('%', 1);
	else
	{
		if (opts->minus == '1')
			ft_putchar_fd('%', 1);
		while (i < opts->width - 1)
		{
			if (opts->null == '1' && opts->minus == '0')
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (opts->minus == '0')
			ft_putchar_fd('%', 1);
	}
	return (i + 1);
}
