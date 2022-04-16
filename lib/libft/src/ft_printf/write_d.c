/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 07:47:05 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:45:37 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Helper function to write a d or i conversion specification using info from
 * the specs struct.
 */
static int	write_d_helper(t_specs *specs, t_options *opts)
{
	if (opts->minus == '0')
		putchar_n(' ', specs->spaces);
	if (specs->sign == '-')
		ft_putchar_fd('-', 1);
	else if (opts->plus == '1')
		ft_putchar_fd('+', 1);
	else if (opts->space == '1')
		ft_putchar_fd(' ', 1);
	putchar_n('0', specs->zeros);
	if (opts->prec != 0 || specs->value != 0)
		putunbr(specs->value);
	if (opts->minus == '1')
		putchar_n(' ', specs->spaces);
	return (specs->field);
}

/*
 * Function that writes a conversion specification of type d or i.
 */
int	write_d(va_list args, t_options *opts)
{	
	t_specs	*specs;
	int		char_count;

	specs = get_specs_d(args, opts);
	if (specs == NULL)
		return (-1);
	char_count = write_d_helper(specs, opts);
	free(specs);
	return (char_count);
}
