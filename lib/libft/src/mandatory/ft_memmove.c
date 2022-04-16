/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:49:56 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:54:11 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that copies 'n' bytes from memory area 'src' to memory area 'dst'.
 * The memory areas may overlap.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len == 0)
		return (dst);
	if (src < dst)
	{
		i = len - 1;
		while (i > 0)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i--;
		}
		((char *)dst)[0] = ((char *)src)[0];
	}
	else if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}
