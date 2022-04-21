/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:37:37 by tjensen           #+#    #+#             */
/*   Updated: 2022/04/18 11:43:46 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_split_count_str(char **split)
{
	int	i;

	if (split == NULL)
		return (-1);
	i = 0;
	while (split[i])
		i++;
	return (i);
}
