/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 09:30:40 by hepple            #+#    #+#             */
/*   Updated: 2021/10/20 15:30:01 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Function that writes an unsigned long n to the standard output
 * in a specific base.
 */
void	putulong_base(unsigned long n, char *base)
{
	unsigned long	len_base;

	len_base = ft_strlen(base);
	if (n < len_base)
		ft_putchar_fd(base[n], 1);
	else
	{
		putulong_base(n / len_base, base);
		ft_putchar_fd(base[n % len_base], 1);
	}
}

/*
 * Function that writes an unsigned integer n to the standard output
 * in a specific base.
 */
void	putunbr_base(unsigned int n, char *base)
{
	unsigned int	len_base;

	len_base = ft_strlen(base);
	if (n < len_base)
		ft_putchar_fd(base[n], 1);
	else
	{
		putunbr_base(n / len_base, base);
		ft_putchar_fd(base[n % len_base], 1);
	}
}

/*
 * Function that writes an unsigned integer n to the standard output.
 */
void	putunbr(unsigned int n)
{
	if (n < 10)
		ft_putchar_fd(n + '0', 1);
	else
	{
		putunbr(n / 10);
		ft_putchar_fd(n % 10 + '0', 1);
	}
}

/*
 * Function that writes the character c to the standard output n times.
 */
void	putchar_n(char c, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

/*
 * Function that writes up to len characters from a string to the
 * standard output.
 */
void	putstr_len(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len && str[i] != '\0')
	{
		write(1, str + i, 1);
		i++;
	}
}
