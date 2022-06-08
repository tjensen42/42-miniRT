/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:19:42 by hepple            #+#    #+#             */
/*   Updated: 2022/06/08 12:29:11 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_rand(void)
{
	return (rand() / ((double) RAND_MAX + 1.0));
}

double	ft_rand_range(double min, double max)
{
	return (min + (rand() / (((double) RAND_MAX + 1.0) / (max - min))));
}
