/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_print_obj_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:57:26 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:57:26 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_print.h"

void	print_obj_plane(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = obj_cont(obj);
	printf("PLANE: (%p)\n", c_obj);
	print_vec3(c_obj->pl.pos, "pos:", COLOR_BL);
	print_vec3(c_obj->pl.dir, "dir:", COLOR_CY);
	print_material(&(c_obj->material));
	printf("\n");
}
