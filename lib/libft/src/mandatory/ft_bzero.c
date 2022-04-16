/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:24:00 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:20:14 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that erases the data in the next 'n' bytes of memory starting from
 * the location pointed to by 's', by writing null bytes to that area.
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dst;
	size_t			i;

	dst = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
}
