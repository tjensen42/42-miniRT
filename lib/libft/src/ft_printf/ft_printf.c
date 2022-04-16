/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:33:48 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:17:57 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that calls the fitting write function for the respective type.
 */
static int	write_args(va_list args, t_options *opts)
{
	int	char_count;

	char_count = -1;
	if (opts->type == '%')
		char_count = write_percent(opts);
	else if (opts->type == 'c')
		char_count = write_c(args, opts);
	else if (opts->type == 's')
		char_count = write_s(args, opts);
	else if (opts->type == 'd' || opts->type == 'i')
		char_count = write_d(args, opts);
	else if (opts->type == 'u')
		char_count = write_u(args, opts);
	else if (opts->type == 'x')
		char_count = write_x(args, opts, "0123456789abcdef");
	else if (opts->type == 'X')
		char_count = write_x(args, opts, "0123456789ABCDEF");
	else if (opts->type == 'p')
		char_count = write_p(args, opts);
	return (char_count);
}

/*
 * Function that allocates memory for the options struct and sets default
 * values.
 */
static t_options	*init_options(void)
{
	t_options	*opts;

	opts = malloc(sizeof(t_options));
	if (opts == NULL)
		return (NULL);
	opts->minus = '0';
	opts->null = '0';
	opts->hash = '0';
	opts->space = '0';
	opts->plus = '0';
	opts->width = -1;
	opts->prec = -1;
	opts->type = '0';
	return (opts);
}

/*
 * Function that gets called when a conversion specification is encountered
 * in the format string and that first reads in the information for the
 * conversion and then prints the data with correct formatting.
 */
static int	handle_conv(const char *str, va_list args, int i, int *ptr)
{
	t_options	*opts;
	int			check;

	i++;
	opts = init_options();
	if (opts == NULL)
		return (-1);
	i = get_options(str, i, args, opts);
	check = write_args(args, opts);
	if (check == -1)
	{
		free(opts);
		return (-1);
	}
	*ptr += check;
	free(opts);
	return (i);
}

/*
 * Function that analyzes the format string and prints normal characters.
 */
static int	parse_string(const char *str, va_list args)
{
	int			char_count;
	int			*count_ptr;
	int			i;

	char_count = 0;
	count_ptr = &char_count;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i = handle_conv(str, args, i, count_ptr);
			if (i == -1)
				return (-1);
		}
		else if (str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			i++;
			char_count++;
		}
		else
			return (-1);
	}
	return (char_count);
}

/*
 * Recode of the libc printf function.
 */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		char_count;

	va_start(args, format);
	char_count = parse_string(format, args);
	va_end(args);
	return (char_count);
}
