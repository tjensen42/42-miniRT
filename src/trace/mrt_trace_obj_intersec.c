#include "mrt_trace.h"

double	intersec_plane(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	double	t;
	t_plane	*plane;

	plane = &(obj_cont(obj)->pl);
    double denom = vec3_scalar_product(plane->dir, ray->dir);
    if (fabs(denom) > 1e-6) //1e-6
	{
        t_vec3	p0l0 = vec3_subtract(obj_cont(obj)->pl.pos, ray->pos);
        t = (double)vec3_scalar_product(p0l0, plane->dir) / denom;
		if (t > t_min && t < t_max)
        	return (t);
    }
	return (-1);
}

double	intersec_sphere(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_vec3		cc;
	t_sphere	*sphere;
	// double		a;
	double		b_half;
	double		c;
	double		discriminant;
	double		discriminant_sqrt;
	double		t;

	sphere = &(obj_cont(obj)->sp);
	cc = vec3_subtract(ray->pos, obj_cont(obj)->sp.pos);
	// a = vec3_scalar_product(ray->dir, ray->dir);
	// a = 1; // da ray.dir normiert
	b_half = vec3_scalar_product(ray->dir, cc);
	c = vec3_scalar_product(cc, cc) - sphere->radius * sphere->radius;
	discriminant = b_half * b_half - c;
	if (discriminant < 0)
		return (-1);
	discriminant_sqrt = sqrt(discriminant);
	t = (-b_half - discriminant_sqrt);
	if (t < t_min || t > t_max)
	{
		t = (-b_half + discriminant_sqrt);
		if (t < t_min || t > t_max)
			return (-1);
	}
	return (t);
}

double	intersec_disc(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	double	t;

    double denom = vec3_scalar_product(obj_cont(obj)->di.dir, ray->dir);
    if (fabs(denom) > 1e-6) //1e-6
	{
        t_vec3	p0l0 = vec3_subtract(obj_cont(obj)->di.pos, ray->pos);
        t = (double)vec3_scalar_product(p0l0, obj_cont(obj)->di.dir) / denom;
		if (t > t_min && t < t_max)
		{
			if (vec3_distance(obj_cont(obj)->di.pos, vec3_linear_comb(1.0, ray->pos, t, ray->dir)) <= obj_cont(obj)->di.radius)
        		return (t);
		}
    }
	return (-1);
}

double	intersec_tube(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_tube	*tb;
	double	discriminant;
	double	discriminant_sqrt;
	double	a, b, c, t, h;
	t_vec3	tmp, tmp2;

	tb = &(obj_cont(obj)->tb);
	tmp = vec3_vector_product(ray->dir, tb->dir);
	a = vec3_scalar_product(tmp, tmp);
	tmp2 = vec3_vector_product(vec3_subtract(ray->pos, obj_cont(obj)->tb.pos), tb->dir);
	b = 2.0 * vec3_scalar_product(tmp, tmp2);
	c = vec3_scalar_product(tmp2, tmp2) - tb->radius * tb->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	discriminant_sqrt = sqrt(discriminant);
	t = (-b - discriminant_sqrt) / (2 * a);
	h = vec3_scalar_product(vec3_subtract(vec3_linear_comb(1.0, ray->pos, t, ray->dir), obj_cont(obj)->tb.pos), tb->dir);
	if (t < t_min || t > t_max || fabs(h) > tb->height / 2.0)
	{
		t = (-b + discriminant_sqrt) / (2 * a);
		h = vec3_scalar_product(vec3_subtract(vec3_linear_comb(1.0, ray->pos, t, ray->dir), obj_cont(obj)->tb.pos), tb->dir);
		if (t < t_min || t > t_max || fabs(h) > tb->height / 2.0)
			return (-1);
	}
	return (t);
}

void	rotate_ray_x(t_ray *ray, double rot_x)
{
	double	sine;
	double	cosine;
	double	tmp;

	sine = sin(rot_x * DEG2RAD);
	cosine = cos(rot_x * DEG2RAD);
	tmp = cosine * ray->pos.y - sine * ray->pos.z;
	ray->pos.z = sine * ray->pos.y + cosine * ray->pos.z;
	ray->pos.y = tmp;
	tmp = cosine * ray->dir.y - sine * ray->dir.z;
	ray->dir.z = sine * ray->dir.y + cosine * ray->dir.z;
	ray->dir.y = tmp;
}

void	rotate_ray_y(t_ray *ray, double rot_y)
{
	double	sine;
	double	cosine;
	double	tmp;

	sine = sin(rot_y * DEG2RAD);
	cosine = cos(rot_y * DEG2RAD);
	tmp = cosine * ray->pos.x + sine * ray->pos.z;
	ray->pos.z = - sine * ray->pos.x + cosine * ray->pos.z;
	ray->pos.x = tmp;
	tmp = cosine * ray->dir.x + sine * ray->dir.z;
	ray->dir.z = - sine * ray->dir.x + cosine * ray->dir.z;
	ray->dir.x = tmp;
}

void	rotate_ray_z(t_ray *ray, double rot_z)
{
	double	sine;
	double	cosine;
	double	tmp;

	sine = sin(rot_z * DEG2RAD);
	cosine = cos(rot_z * DEG2RAD);
	tmp = cosine * ray->pos.x - sine * ray->pos.y;
	ray->pos.y = sine * ray->pos.x + cosine * ray->pos.y;
	ray->pos.x = tmp;
	tmp = cosine * ray->dir.x - sine * ray->dir.y;
	ray->dir.y = sine * ray->dir.x + cosine * ray->dir.y;
	ray->dir.x = tmp;
}

double	intersec_rectangle_z(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_ray	tmp_ray;
	double	t;
	double	x;
	double	y;

	tmp_ray = *ray;

	tmp_ray.pos = vec3_subtract(tmp_ray.pos, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.rot.z != 0.0)
		rotate_ray_z(&tmp_ray, obj_cont(obj)->rt.rot.z);
	if (obj_cont(obj)->rt.rot.y != 0.0)
		rotate_ray_y(&tmp_ray, obj_cont(obj)->rt.rot.y);
	if (obj_cont(obj)->rt.rot.x != 0.0)
		rotate_ray_x(&tmp_ray, obj_cont(obj)->rt.rot.x);
	tmp_ray.pos = vec3_subtract(tmp_ray.pos, obj_cont(obj)->rt.rel_pos);

	if (fabs(tmp_ray.dir.z) < 1e-6)
		return (-1);
	t = - tmp_ray.pos.z / tmp_ray.dir.z;
	if (t < t_min || t > t_max)
		return (-1);
	x = tmp_ray.pos.x + t * tmp_ray.dir.x;
	y = tmp_ray.pos.y + t * tmp_ray.dir.y;
	if (fabs(x) > obj_cont(obj)->rt.width / 2.0 || fabs(y) > obj_cont(obj)->rt.height / 2.0)
		return (-1);
	return (t);
}

double	intersec_rectangle_y(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_ray	tmp_ray;
	double	t;
	double	x;
	double	z;

	tmp_ray = *ray;

	tmp_ray.pos = vec3_subtract(tmp_ray.pos, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.rot.z != 0.0)
		rotate_ray_z(&tmp_ray, obj_cont(obj)->rt.rot.z);
	if (obj_cont(obj)->rt.rot.y != 0.0)
		rotate_ray_y(&tmp_ray, obj_cont(obj)->rt.rot.y);
	if (obj_cont(obj)->rt.rot.x != 0.0)
		rotate_ray_x(&tmp_ray, obj_cont(obj)->rt.rot.x);
	tmp_ray.pos = vec3_subtract(tmp_ray.pos, obj_cont(obj)->rt.rel_pos);

	if (fabs(tmp_ray.dir.y) < 1e-6)
		return (-1);
	t = - tmp_ray.pos.y / tmp_ray.dir.y;
	if (t < t_min || t > t_max)
		return (-1);
	x = tmp_ray.pos.x + t * tmp_ray.dir.x;
	z = tmp_ray.pos.z + t * tmp_ray.dir.z;
	if (fabs(x) > obj_cont(obj)->rt.width / 2.0 || fabs(z) > obj_cont(obj)->rt.height / 2.0)
		return (-1);
	return (t);
}

double	intersec_rectangle_x(t_list *obj, t_ray *ray, double t_min, double t_max)
{
	t_ray	tmp_ray;

	double		t;
	double		y;
	double		z;

	tmp_ray = *ray;

	tmp_ray.pos = vec3_subtract(tmp_ray.pos, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.rot.z != 0.0)
		rotate_ray_z(&tmp_ray, obj_cont(obj)->rt.rot.z);
	if (obj_cont(obj)->rt.rot.y != 0.0)
		rotate_ray_y(&tmp_ray, obj_cont(obj)->rt.rot.y);
	if (obj_cont(obj)->rt.rot.x != 0.0)
		rotate_ray_x(&tmp_ray, obj_cont(obj)->rt.rot.x);
	tmp_ray.pos = vec3_subtract(tmp_ray.pos, obj_cont(obj)->rt.rel_pos);

	if (fabs(tmp_ray.dir.x) < 1e-6)
		return (-1);
	t = - tmp_ray.pos.x / tmp_ray.dir.x;
	if (t < t_min || t > t_max)
		return (-1);
	y = tmp_ray.pos.y + t * tmp_ray.dir.y;
	z = tmp_ray.pos.z + t * tmp_ray.dir.z;
	if (fabs(y) > obj_cont(obj)->rt.width / 2.0 || fabs(z) > obj_cont(obj)->rt.height / 2.0)
		return (-1);
	return (t);
}
