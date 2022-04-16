/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 09:20:03 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 13:23:21 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that returns a substring of the string 's', begins at index 'start'
 * and being of maximum size 'len'. Memory for the substring is obtained with
 * malloc.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		subs = malloc(sizeof(char));
		if (subs == NULL)
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	subs = malloc(sizeof(char) * (len + 1));
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
