/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:54:30 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:54:31 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_obj.h"
#include "lib/libmlx/include/MLX42/MLX42.h"

t_list	*obj_new(void)
{
	t_obj	*c_obj;

	c_obj = malloc(sizeof(t_obj));
	if (c_obj == NULL)
		return (NULL);
	ft_bzero(c_obj, sizeof(t_obj));
	return (ft_lstnew(c_obj));
}

inline t_material	*obj_material(t_list *obj)
{
	return (&(obj_cont(obj)->material));
}

inline t_texture	*obj_c_texture(t_list *obj)
{
	return (obj_cont(obj)->material.c_texture);
}

inline t_obj	*obj_cont(t_list *obj)
{
	return ((t_obj *)obj->content);
}

inline t_color	obj_color(t_list *obj, t_hit *hit __attribute__((unused)))
{
	return (obj_cont(obj)->material.color);
}
