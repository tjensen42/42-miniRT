/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:34:21 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:50:58 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that copies up to 'n' bytes from memory area 'src'
 * to memory area 'dst', stopping when the character 'c' is found.
 * For overlapping memory areas, the behaviour is undefined.
 */
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	size_t			i;

	dst_copy = (unsigned char *)dst;
	src_copy = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_copy[i] = src_copy[i];
		if (src_copy[i] == (unsigned char) c)
			break ;
		i++;
	}
	if (i == n)
		return (NULL);
	else
		return (dst + i + 1);
}
