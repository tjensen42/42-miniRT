/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:24:58 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 13:21:22 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that creates and returns a copy of string 's1' with the characters
 * specified in 'set' removed from the beginning and the end of the string.
 * Memory for the new string is obtained with malloc.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	min;
	size_t	max;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	min = 0;
	max = ft_strlen(s1) - 1;
	while (s1[min] != '\0' && ft_strchr(set, s1[min]) != NULL)
		min++;
	while (max >= min && ft_strchr(set, s1[max]) != NULL)
		max--;
	if (max < min || s1[0] == '\0')
		s2 = (char *)ft_calloc(1, sizeof(char));
	else
		s2 = malloc(sizeof(char) * (max - min + 2));
	if (s2 == NULL)
		return (NULL);
	if (max >= min && s1[0] != '\0')
	{
		ft_memcpy(s2, s1 + min, max - min + 1);
		s2[max - min + 1] = '\0';
	}
	return (s2);
}
