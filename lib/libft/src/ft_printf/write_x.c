/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 07:53:54 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 16:02:50 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Helper function to write an x or X conversion specification, using the info
 * from the specs struct.
 */
static int	write_x_helper(t_specs *specs, t_options *opts, char *base)
{
	if (opts->minus == '0')
		putchar_n(' ', specs->spaces);
	if (opts->hash == '1' && specs->value != 0)
	{
		ft_putchar_fd('0', 1);
		if (opts->type == 'x')
			ft_putchar_fd('x', 1);
		else
			ft_putchar_fd('X', 1);
	}
	else if (opts->plus == '1')
		ft_putchar_fd('+', 1);
	else if (opts->space == '1')
		ft_putchar_fd(' ', 1);
	putchar_n('0', specs->zeros);
	if (opts->prec != 0 || specs->value != 0)
		putunbr_base(specs->value, base);
	if (opts->minus == '1')
		putchar_n(' ', specs->spaces);
	return (specs->field);
}

/*
 * Function that writes a conversion specification of type x or X.
 */
int	write_x(va_list args, t_options *opts, char *base)
{	
	t_specs	*specs;
	int		char_count;

	specs = get_specs_x(args, opts);
	if (specs == NULL)
		return (-1);
	char_count = write_x_helper(specs, opts, base);
	free(specs);
	return (char_count);
}
