/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 07:52:19 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 16:00:44 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
 * Function that calculates the number of additional leading zeros for an
 * unsigned integer conversion.
 */
static unsigned int	get_zeros_u(t_specs *specs, t_options *opts)
{
	unsigned int	zeros;

	zeros = 0;
	if (opts->prec != -1 && (unsigned int) opts->prec > specs->digits)
		zeros = opts->prec - specs->digits;
	if (opts->prec == -1 && opts->null == '1' && opts->minus == '0')
		zeros = specs->field - specs->digits;
	return (zeros);
}

/*
 * Function that calculates the total field width for an unsigned integer
 * conversion.
 */
static unsigned int	get_field_u(t_specs *specs, t_options *opts)
{
	unsigned int	field;

	field = specs->digits;
	if (opts->width != -1 && (unsigned int) opts->width > field)
		field = opts->width;
	if (opts->prec != -1 && (unsigned int) opts->prec > field)
		field = opts->prec;
	return (field);
}

/*
 * Function that calculates the number of digits of an unsigned integer.
 */
static unsigned int	get_digits_u(unsigned int n)
{
	if (n < 10)
		return (1);
	return (get_digits_u(n / 10) + 1);
}

/*
 * Function that allocates memory for the specs struct and sets the respective
 * values.
 */
static t_specs	*get_specs_u(va_list args, t_options *opts)
{
	t_specs			*specs;
	unsigned int	u;

	specs = malloc(sizeof(t_specs));
	if (specs == NULL)
		return (NULL);
	u = (unsigned int) va_arg(args, unsigned int);
	specs->sign = 'u';
	specs->value = u;
	if (specs->value == 0 && opts->prec == 0)
		specs->digits = 0;
	else
		specs->digits = get_digits_u(specs->value);
	specs->field = get_field_u(specs, opts);
	specs->zeros = get_zeros_u(specs, opts);
	specs->spaces = specs->field - specs->digits - specs->zeros;
	return (specs);
}

/*
 * Function that writes a conversion specification of type u.
 */
int	write_u(va_list args, t_options *opts)
{	
	t_specs	*specs;
	int		char_count;

	specs = get_specs_u(args, opts);
	if (specs == NULL)
		return (-1);
	if (opts->minus == '0')
		putchar_n(' ', specs->spaces);
	putchar_n('0', specs->zeros);
	if (opts->prec != 0 || specs->value != 0)
		putunbr(specs->value);
	if (opts->minus == '1')
		putchar_n(' ', specs->spaces);
	char_count = specs->field;
	free(specs);
	return (char_count);
}
