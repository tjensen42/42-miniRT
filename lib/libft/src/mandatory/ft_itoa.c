/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 08:43:54 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:34:01 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Helper function for ft_itoa that counts the number of digits
 * of an integer 'i' in base 10.
 */
static size_t	num_digits(int i)
{
	if (i == INT_MIN)
		return (11);
	if (i < 0)
		return (num_digits(i * (-1)) + 1);
	if (i < 10)
		return (1);
	return (num_digits(i / 10) + 1);
}

/*
 * Helper function for ft_itoa that writes the digits of the integer 'n'
 * to the string 'str' one by one.
 */
static char	*itoa_main_part(int n, char *str, size_t size)
{
	size_t	i;
	int		n_is_negative;

	str[size] = '\0';
	if (n < 0)
	{
		n_is_negative = 1;
		n = n * (-1);
	}
	else
		n_is_negative = 0;
	i = size - 1;
	while (i > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	if (n_is_negative)
		str[0] = '-';
	else
		str[0] = n + '0';
	return (str);
}

/*
 * Function that converts an integer 'n' to a null-terminated string.
 */
char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;

	size = num_digits(n);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	if (n == INT_MIN)
		ft_memcpy(str, "-2147483648\0", size + 1);
	else
		str = itoa_main_part(n, str, size);
	return (str);
}
