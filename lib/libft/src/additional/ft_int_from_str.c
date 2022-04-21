/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_from_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:49:48 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/19 15:56:26 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_from_str(const char *str, int min, int max, int *res)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	*res = ft_atoi(str);
	if (*res < min || *res > max)
		return (-1);
	return (0);
}
