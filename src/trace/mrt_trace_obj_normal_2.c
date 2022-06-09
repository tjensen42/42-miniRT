/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_trace_obj_normal_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:55:24 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:55:24 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_trace.h"

static void	normal_rectangle_rotate_x(t_vec3 *normal, double rot_x);
static void	normal_rectangle_rotate_y(t_vec3 *normal, double rot_y);
static void	normal_rectangle_rotate_z(t_vec3 *normal, double rot_z);

t_vec3	normal_rectangle(t_list *obj, t_hit *hit __attribute__((unused)))
{
	t_vec3	tmp_normal;

	tmp_normal = obj_cont(obj)->rt.dir;
	if (obj_cont(obj)->rt.rot.x != 0.0)
		normal_rectangle_rotate_x(&tmp_normal, obj_cont(obj)->rt.rot.x);
	if (obj_cont(obj)->rt.rot.y != 0.0)
		normal_rectangle_rotate_y(&tmp_normal, obj_cont(obj)->rt.rot.y);
	if (obj_cont(obj)->rt.rot.z != 0.0)
		normal_rectangle_rotate_z(&tmp_normal, obj_cont(obj)->rt.rot.z);
	return (tmp_normal);
}

static void	normal_rectangle_rotate_x(t_vec3 *normal, double rot_x)
{
	double	tmp;
	double	sine;
	double	cosine;

	sine = sin(rot_x * (M_PI / 180.0));
	cosine = cos(rot_x * (M_PI / 180.0));
	tmp = cosine * normal->y + sine * normal->z;
	normal->z = -sine * normal->y + cosine * normal->z;
	normal->y = tmp;
}

static void	normal_rectangle_rotate_y(t_vec3 *normal, double rot_y)
{
	double	tmp;
	double	sine;
	double	cosine;

	sine = sin(rot_y * (M_PI / 180.0));
	cosine = cos(rot_y * (M_PI / 180.0));
	tmp = cosine * normal->x - sine * normal->z;
	normal->z = sine * normal->x + cosine * normal->z;
	normal->x = tmp;
}

static void	normal_rectangle_rotate_z(t_vec3 *normal, double rot_z)
{
	double	tmp;
	double	sine;
	double	cosine;

	sine = sin(rot_z * (M_PI / 180.0));
	cosine = cos(rot_z * (M_PI / 180.0));
	tmp = cosine * normal->x + sine * normal->y;
	normal->y = -sine * normal->x + cosine * normal->y;
	normal->x = tmp;
}
