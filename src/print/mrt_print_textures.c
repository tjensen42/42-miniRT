/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_print_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:57:17 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:57:17 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_print.h"

void	print_textures(t_list *l_texture)
{
	t_texture	*c_texture;

	if (l_texture == NULL)
		return ;
	printf("TEXTURES:\n");
	while (l_texture)
	{
		c_texture = l_texture->content;
		printf("\t%s: width: %zu height: %zu\n",
			c_texture->name, c_texture->width, c_texture->height);
		l_texture = l_texture->next;
	}
	printf("\n");
}
