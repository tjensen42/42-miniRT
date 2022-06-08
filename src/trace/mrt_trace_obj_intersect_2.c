#include "mrt_trace.h"

double	intersect_rectangle_z(t_list *obj, t_ray *ray, double t_min,
			double t_max)
{
	t_ray	tmp_ray;
	double	t;
	double	x;
	double	y;

	tmp_ray = *ray;
	intersect_rectangle_move_rotate_ray(&tmp_ray, obj);
	if (fabs(tmp_ray.dir.z) < 1e-6)
		return (-1.0);
	t = -tmp_ray.pos.z / tmp_ray.dir.z;
	if (t < t_min || t > t_max)
		return (-1.0);
	x = tmp_ray.pos.x + t * tmp_ray.dir.x;
	y = tmp_ray.pos.y + t * tmp_ray.dir.y;
	if (fabs(x) > obj_cont(obj)->rt.width / 2.0
		|| fabs(y) > obj_cont(obj)->rt.height / 2.0)
		return (-1.0);
	return (t);
}

double	intersect_rectangle_y(t_list *obj, t_ray *ray, double t_min,
			double t_max)
{
	t_ray	tmp_ray;
	double	t;
	double	x;
	double	z;

	tmp_ray = *ray;
	intersect_rectangle_move_rotate_ray(&tmp_ray, obj);
	if (fabs(tmp_ray.dir.y) < 1e-6)
		return (-1.0);
	t = -tmp_ray.pos.y / tmp_ray.dir.y;
	if (t < t_min || t > t_max)
		return (-1.0);
	x = tmp_ray.pos.x + t * tmp_ray.dir.x;
	z = tmp_ray.pos.z + t * tmp_ray.dir.z;
	if (fabs(x) > obj_cont(obj)->rt.width / 2.0
		|| fabs(z) > obj_cont(obj)->rt.height / 2.0)
		return (-1.0);
	return (t);
}

double	intersect_rectangle_x(t_list *obj, t_ray *ray, double t_min,
			double t_max)
{
	t_ray	tmp_ray;
	double	t;
	double	y;
	double	z;

	tmp_ray = *ray;
	intersect_rectangle_move_rotate_ray(&tmp_ray, obj);
	if (fabs(tmp_ray.dir.x) < 1e-6)
		return (-1.0);
	t = -tmp_ray.pos.x / tmp_ray.dir.x;
	if (t < t_min || t > t_max)
		return (-1.0);
	y = tmp_ray.pos.y + t * tmp_ray.dir.y;
	z = tmp_ray.pos.z + t * tmp_ray.dir.z;
	if (fabs(z) > obj_cont(obj)->rt.width / 2.0
		|| fabs(y) > obj_cont(obj)->rt.height / 2.0)
		return (-1.0);
	return (t);
}
