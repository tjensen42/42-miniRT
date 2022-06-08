#include "mrt_trace.h"

static void	intersect_tube_quadratic(t_list *obj, t_ray *ray, double abc[3]);

double	intersect_plane(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_plane	*pl;
	double	denominator;
	double	t;

	pl = &(obj_cont(obj)->pl);
	denominator = vec3_dot(pl->dir, ray->dir);
	if (fabs(denominator) > 1e-6)
	{
		t = vec3_dot(vec3_sub(pl->pos, ray->pos), pl->dir) / denominator;
		if (t > t_min && t < t_max)
			return (t);
	}
	return (-1.0);
}

double	intersect_sphere(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_vec3		sphere_ray;
	double		b_half;
	double		c;
	double		d;
	double		t;

	sphere_ray = vec3_sub(ray->pos, obj_cont(obj)->sp.pos);
	b_half = vec3_dot(ray->dir, sphere_ray);
	c = vec3_dot(sphere_ray, sphere_ray)
		- obj_cont(obj)->sp.radius * obj_cont(obj)->sp.radius;
	d = b_half * b_half - c;
	if (d < 0.0)
		return (-1.0);
	d = sqrt(d);
	t = -b_half - d;
	if (t < t_min || t > t_max)
	{
		t = -b_half + d;
		if (t < t_min || t > t_max)
			return (-1.0);
	}
	return (t);
}

double	intersect_disc(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_disc	*di;
	double	denominator;
	double	t;

	di = &(obj_cont(obj)->di);
	denominator = vec3_dot(di->dir, ray->dir);
	if (fabs(denominator) > 1e-6)
	{
		t = vec3_dot(vec3_sub(di->pos, ray->pos), di->dir) / denominator;
		if (t > t_min && t < t_max && vec3_dist(di->pos,
				vec3_lin_comb(1.0, ray->pos, t, ray->dir)) <= di->radius)
			return (t);
	}
	return (-1.0);
}

double	intersect_tube(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_tube	*tb;
	double	abc[3];
	double	d;
	double	h;
	double	t;

	tb = &(obj_cont(obj)->tb);
	intersect_tube_quadratic(obj, ray, abc);
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0 || abc[0] < 1e-6)
		return (-1.0);
	d = sqrt(d);
	t = (-abc[1] - d) / (2.0 * abc[0]);
	h = vec3_dot(vec3_sub(vec3_lin_comb(
					1.0, ray->pos, t, ray->dir), tb->pos), tb->dir);
	if (t < t_min || t > t_max || fabs(h) > tb->height / 2.0)
	{
		t = (-abc[1] + d) / (2.0 * abc[0]);
		h = vec3_dot(vec3_sub(vec3_lin_comb(
						1.0, ray->pos, t, ray->dir), tb->pos), tb->dir);
		if (t < t_min || t > t_max || fabs(h) > tb->height / 2.0)
			return (-1.0);
	}
	return (t);
}

static void	intersect_tube_quadratic(t_list *obj, t_ray *ray, double abc[3])
{
	t_tube	*tb;
	t_vec3	ray_x_tube;
	t_vec3	dif_x_dir;

	tb = &(obj_cont(obj)->tb);
	ray_x_tube = vec3_cross(ray->dir, tb->dir);
	abc[0] = vec3_dot(ray_x_tube, ray_x_tube);
	dif_x_dir = vec3_cross(vec3_sub(ray->pos, tb->pos), tb->dir);
	abc[1] = 2.0 * vec3_dot(ray_x_tube, dif_x_dir);
	abc[2] = vec3_dot(dif_x_dir, dif_x_dir) - tb->radius * tb->radius;
}
