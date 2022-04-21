/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_chr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:36:42 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/18 11:44:18 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_count_chr(const char *str, const char c)
{
	int		i;
	int		chr_count;

	if (str == NULL)
		return (-1);
	chr_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			chr_count++;
		i++;
	}
	return (chr_count);
}
