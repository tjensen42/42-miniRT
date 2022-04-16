/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 07:37:04 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:24:08 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that reads the precision from the conversion specification
 * or the argument list.
 */
static int	get_prec(const char *str, int i, va_list args, t_options *opts)
{
	unsigned int	value;

	if (str[i] == '.')
	{
		opts->prec = 0;
		i++;
		if (ft_isdigit(str[i]))
		{
			value = 0;
			while (ft_isdigit(str[i]))
			{
				value = value * 10 + (str[i] - '0');
				i++;
			}
			opts->prec = value;
		}
		else if (str[i] == '*')
		{
			opts->prec = va_arg(args, int);
			if (opts->prec < 0)
				opts->prec = -1;
			i++;
		}
	}
	return (i);
}

/* 
 * Function reads the width from the conversion specification
 * or the argument list.
 */
static int	get_width(const char *str, int i, va_list args, t_options *opts)
{
	unsigned int	value;

	if (ft_isdigit(str[i]))
	{
		value = 0;
		while (ft_isdigit(str[i]))
		{
			value = value * 10 + (str[i] - '0');
			i++;
		}
		opts->width = value;
	}
	else if (str[i] == '*')
	{
		opts->width = va_arg(args, int);
		if (opts->width < 0)
		{
			opts->width = -opts->width;
			opts->minus = '1';
		}
		i++;
	}
	return (i);
}

/*
 * Function that reads the flags from the conversion specification.
 */
static int	get_flags(const char *str, int i, t_options *opts)
{
	while (ft_strchr("-0+ #", str[i]) != NULL && str[i] != '\0')
	{
		if (str[i] == '-')
			opts->minus = '1';
		else if (str[i] == '0')
			opts->null = '1';
		else if (str[i] == '#')
			opts->hash = '1';
		else if (str[i] == ' ')
			opts->space = '1';
		else if (str[i] == '+')
			opts->plus = '1';
		i++;
	}
	return (i);
}

/*
 * Function that saves all the information from the conversion specification
 * in the options struct.
 */
int	get_options(const char *str, int i, va_list args, t_options *opts)
{
	i = get_flags(str, i, opts);
	i = get_width(str, i, args, opts);
	i = get_prec(str, i, args, opts);
	if (ft_strchr("cspdiuxX%", str[i]) != NULL && str[i] != '\0')
	{
		opts->type = str[i];
		i++;
	}
	return (i);
}
