/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:34:29 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:52:01 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that copies 'n' bytes from memory area 'src' to memory area 'dst'.
 * For overlapping memory areas, the behaviour is undefined.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	size_t			i;

	dst_copy = (unsigned char *)dst;
	src_copy = (unsigned char *)src;
	if (dst_copy == NULL && src_copy == NULL)
		return (dst);
	i = 0;
	while (i < n)
	{
		dst_copy[i] = src_copy[i];
		i++;
	}
	return (dst);
}
