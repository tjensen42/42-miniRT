/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_from_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:50:04 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/08 15:11:12 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_double(const char *str);

int	ft_double_from_str(const char *str, int before_dec,
				int after_dec, double *res)
{
	int	i;

	if (ft_strchr(str, '.') != ft_strrchr(str, '.'))
		return (-1);
	if (ft_strchr(str, '.') && (int)(ft_strchr(str, '.') - str) > before_dec)
		return (-1);
	if (ft_strchr(str, '.')
		&& (int)(ft_strlen(ft_strchr(str, '.') + 1)) > after_dec)
		return (-1);
	if (ft_strchr(str, '.') && !ft_isdigit(*(ft_strchr(str, '.') + 1)))
		return (-1);
	if (!ft_strchr(str, '.') && (int)(ft_strlen(str)) > before_dec)
		return (-1);
	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (-1);
		i++;
	}
	*res = get_double(str);
	return (0);
}

static double	get_double(const char *str)
{
	double	value;
	double	factor;
	int		i;

	i = 0;
	value = 0.0;
	factor = 1;
	if (str[i] == '-')
		factor = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10.0 + (str[i] - '0');
		factor = factor / 10.0;
		i++;
	}
	return (factor * value);
}
