/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:43:20 by hepple            #+#    #+#             */
/*   Updated: 2021/10/25 10:53:25 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* ******************* */
/*   I N C L U D E S   */
/* ******************* */

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

/* ******************* */
/*   T Y P E D E F S   */
/* ******************* */

/*
 * Struct to save the information from a conversion specification:
 * - minus:	1 if minus flag is found, 0 if it isn't
 * - null:	1 if null flag is found, 0 if it isn't
 * - hash:	1 if hash flag is found, 0 if it isn't
 * - space:	1 if space flag is found, 0 if it isn't
 * - plus:	1 if plus flag is found, 0 if it isn't
 * - width:	minimum field with
 * - prec:	precision
 * - type:	type specifier
 */
typedef struct s_options
{
	char	minus;
	char	null;
	char	hash;
	char	space;
	char	plus;
	int		width;
	int		prec;
	char	type;
}			t_options;

/*
 * Struct to save information used when printing numerical conversions:
 * - sign:		sign of the number
 * - value:		absolute value
 * - digits:	number of digits
 * - field:		total field width
 * - zeros:		number of leading zeros
 * - spaces:	number of spaces
 */
typedef struct s_specs
{
	char			sign;
	unsigned int	value;
	unsigned int	digits;
	unsigned int	field;
	unsigned int	zeros;
	unsigned int	spaces;
}					t_specs;

/* ******************* */
/* P R O T O T Y P E S */
/* ******************* */

/* Functions - [...].c */

int		ft_printf(const char *format, ...);

int		get_options(const char *str, int i, va_list args,
			t_options *opts);
int		write_percent(t_options *opts);
int		write_c(va_list args, t_options *opts);
int		write_s(va_list args, t_options *opts);
int		write_d(va_list args, t_options *opts);
t_specs	*get_specs_d(va_list args, t_options *opts);
int		write_u(va_list args, t_options *opts);
int		write_x(va_list args, t_options *opts, char *base);
t_specs	*get_specs_x(va_list args, t_options *opts);
int		write_p(va_list args, t_options *opts);

/* Functions - utils.c */

void	putstr_len(char *str, int len);
void	putchar_n(char c, unsigned int n);
void	putunbr(unsigned int n);
void	putunbr_base(unsigned int n, char *base);
void	putulong_base(unsigned long n, char *base);

#endif