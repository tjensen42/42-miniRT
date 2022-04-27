/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:35:37 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/27 09:27:21 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_rand_double_0_1(void)
{
	return (rand() / (double)(RAND_MAX));
}

double	ft_rand_double(double min, double max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

