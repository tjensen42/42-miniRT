/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:25:34 by hepple            #+#    #+#             */
/*   Updated: 2021/11/25 13:25:37 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that returns a pointer to a new string which is a duplicate of the
 * string 's1'. Memory for the new string is obtained with malloc.
 */
char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*s2;

	len_s1 = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (len_s1 + 1));
	if (s2 == NULL)
		return (NULL);
	s2 = (char *)ft_memcpy(s2, s1, len_s1 + 1);
	return (s2);
}
