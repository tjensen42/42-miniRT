/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_obj_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:54:27 by tjensen           #+#    #+#             */
/*   Updated: 2022/12/19 12:43:17 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include "mrt_color.h"
#include "mrt_vec3.h"
#include "mrt_obj.h"
#include "math/mrt_math.h"
#include "trace/mrt_trace.h"

t_color	texture_sphere(t_list *obj, t_hit *hit)
{
	t_vec3		p;
	double		u;
	double		v;
	size_t		pixel;
	t_texture	*c_texture;

	c_texture = obj_cont(obj)->material.c_texture;
	p = vec3_norm(vec3_sub(hit->p, obj_cont(obj)->sp.pos));
	if (obj_cont(obj)->sp.rot.z != 0.0)
		sphere_rotate_z(&p, obj_cont(obj)->sp.rot.z);
	if (obj_cont(obj)->sp.rot.y != 0.0)
		sphere_rotate_y(&p, obj_cont(obj)->sp.rot.y);
	if (obj_cont(obj)->sp.rot.x != 0.0)
		sphere_rotate_x(&p, obj_cont(obj)->sp.rot.x);
	u = (atan2(-p.z, p.x) + M_PI) / (2.0 * M_PI);
	v = acos(p.y) / M_PI;
	pixel = (size_t)(v * c_texture->height)
		* c_texture->width + u * c_texture->width;
	return (c_texture->color[pixel]);
}

t_color	texture_rectangle_x(t_list *obj, t_hit *hit)
{
	t_vec3		p;
	double		u;
	double		v;
	t_texture	*c_texture;
	size_t		pixel;

	c_texture = obj_cont(obj)->material.c_texture;
	p = vec3_sub(hit->p, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.dir.x < 0.0)
		u = p.z / obj_cont(obj)->rt.width + 0.5;
	else
		u = -p.z / obj_cont(obj)->rt.width + 0.5;
	v = -p.y / obj_cont(obj)->rt.height + 0.5;
	pixel = (size_t)(v * c_texture->height) * c_texture->width
		+ u * c_texture->width;
	return (c_texture->color[pixel]);
}

t_color	texture_rectangle_y(t_list *obj, t_hit *hit)
{
	t_vec3		p;
	double		u;
	double		v;
	t_texture	*c_texture;
	size_t		pixel;

	c_texture = obj_cont(obj)->material.c_texture;
	p = vec3_sub(hit->p, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.dir.y < 0.0)
		u = -p.x / obj_cont(obj)->rt.width + 0.5;
	else
		u = p.x / obj_cont(obj)->rt.width + 0.5;
	v = p.z / obj_cont(obj)->rt.height + 0.5;
	pixel = (size_t)(v * c_texture->height) * c_texture->width
		+ u * c_texture->width;
	return (c_texture->color[pixel]);
}

t_color	texture_rectangle_z(t_list *obj, t_hit *hit)
{
	t_vec3		p;
	double		u;
	double		v;
	t_texture	*c_texture;
	size_t		pixel;

	c_texture = obj_cont(obj)->material.c_texture;
	p = vec3_sub(hit->p, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.dir.z < 0.0)
		u = -p.x / obj_cont(obj)->rt.width + 0.5;
	else
		u = p.x / obj_cont(obj)->rt.width + 0.5;
	v = -p.y / obj_cont(obj)->rt.height + 0.5;
	pixel = (size_t)(v * c_texture->height) * c_texture->width
		+ u * c_texture->width;
	return (c_texture->color[pixel]);
}
