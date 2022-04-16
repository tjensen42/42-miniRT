/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:05:29 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 13:11:34 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that locates the first occurrence of the null-terminated string
 * 'needle' in the null-terminated string 'haystack', searching at most 'len'
 * bytes. The return value is either a pointer to the first character of the
 * first occurrence of 'needle' in 'haystack', or NULL if 'needle' isn't
 * contained in 'haystack'.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] != '\0' && i < len - ft_strlen(needle) + 1)
	{
		j = 0;
		while (needle[j] != '\0')
		{
			if (needle[j] == haystack[i + j])
				j++;
			else
				break ;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
