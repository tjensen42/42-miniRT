/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specs_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 07:50:18 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:35:40 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that calculates the number of additional spaces for an integer
 * conversion.
 */
static unsigned int	get_spaces_d(t_specs *specs, t_options *opts)
{
	unsigned int	spaces;

	spaces = specs->field - specs->digits - specs->zeros;
	if (specs->sign == '-' || opts->space == '1' || opts->plus == '1')
		spaces--;
	return (spaces);
}

/*
 * Function that calculates the number of additional leading zeros for an
 * integer conversion.
 */
static unsigned int	get_zeros_d(t_specs *specs, t_options *opts)
{
	unsigned int	zeros;

	zeros = 0;
	if (opts->prec != -1 && (unsigned int) opts->prec > specs->digits)
		zeros = opts->prec - specs->digits;
	else if (opts->prec == -1)
	{
		if (opts->null == '1' && opts->minus == '0')
		{
			zeros = specs->field - specs->digits;
			if (specs->sign == '-' || opts->space == '1' || opts->plus == '1')
				zeros--;
		}
	}	
	return (zeros);
}

/*
 * Function that calculates the total field width for an integer conversion.
 */
static unsigned int	get_field_d(t_specs *specs, t_options *opts)
{
	unsigned int	field;
	unsigned int	prec;

	field = specs->digits;
	if (specs->sign == '-' || opts->space == '1' || opts->plus == '1')
		field++;
	if (opts->width != -1 && (unsigned int) opts->width > field)
		field = opts->width;
	if (opts->prec != -1)
	{
		prec = opts->prec;
		if (specs->sign == '-' || opts->space == '1' || opts->plus == '1')
			prec++;
		if (prec > field)
			field = prec;
	}
	return (field);
}

/*
 * Function that calculates the number of digits of an integer, not counting
 * the sign.
 */
static unsigned int	get_digits_d(unsigned int n)
{
	if (n < 10)
		return (1);
	return (get_digits_d(n / 10) + 1);
}

/*
 * Function that allocates memory for the specs struct and sets the respective
 * values.
 */
t_specs	*get_specs_d(va_list args, t_options *opts)
{
	t_specs	*specs;
	int		d;

	specs = malloc(sizeof(t_specs));
	if (specs == NULL)
		return (NULL);
	d = (int) va_arg(args, int);
	if (d < 0)
		specs->sign = '-';
	else
		specs->sign = '+';
	if (d < 0)
		specs->value = -d;
	else
		specs->value = d;
	if (specs->value == 0 && opts->prec == 0)
		specs->digits = 0;
	else
		specs->digits = get_digits_d(specs->value);
	specs->field = get_field_d(specs, opts);
	specs->zeros = get_zeros_d(specs, opts);
	specs->spaces = get_spaces_d(specs, opts);
	return (specs);
}
