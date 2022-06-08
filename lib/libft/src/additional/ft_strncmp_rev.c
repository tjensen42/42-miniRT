/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_rev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:53:55 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/08 15:10:43 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_rev(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	while (i < n && i < s1_len && i < s2_len)
	{
		if (s1[s1_len - 1 - i] != s2[s2_len - 1 - i])
			return ((unsigned char)s1[s1_len - 1 - i]
				- (unsigned char)s2[s2_len - 1 - i]);
		i++;
	}
	if (i != n && i == s1_len && i < s2_len)
		return (-(unsigned char)s2[s2_len - 1 - i]);
	if (i != n && i == s2_len && i < s1_len)
		return ((unsigned char)s1[s1_len - 1 - i]);
	return (0);
}
