#include "lib/libft/inc/libft.h"
#include "mrt_color.h"
#include "mrt_vec3.h"
#include "mrt_obj.h"
#include "math/mrt_math.h"
#include "trace/mrt_trace.h"

t_color	checkerboard_sphere(t_list *obj, t_hit *hit)
{
	t_vec3	p;
	double	theta;
	double	phi;

	p = vec3_norm(vec3_sub(hit->p, obj_cont(obj)->sp.pos));
	if (obj_cont(obj)->sp.rot.z != 0.0)
		sphere_rotate_z(&p, obj_cont(obj)->sp.rot.z);
	if (obj_cont(obj)->sp.rot.y != 0.0)
		sphere_rotate_z(&p, obj_cont(obj)->sp.rot.y);
	if (obj_cont(obj)->sp.rot.x != 0.0)
		sphere_rotate_z(&p, obj_cont(obj)->sp.rot.x);
	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + M_PI;
	if (sin(phi * obj_cont(obj)->material.cb_factor)
		* sin(theta * obj_cont(obj)->material.cb_factor) > 0)
		return ((t_color){0.0, 0.0, 0.0});
	else
		return (obj_color(obj, hit));
}

void	sphere_rotate_x(t_vec3 *p, double rot_x)
{
	double	tmp;
	double	sine;
	double	cosine;

	sine = sin(rot_x * DEG2RAD);
	cosine = cos(rot_x * DEG2RAD);
	tmp = cosine * p->y - sine * p->z;
	p->z = sine * p->y + cosine * p->z;
	p->y = tmp;
}

void	sphere_rotate_y(t_vec3 *p, double rot_y)
{
	double	tmp;
	double	sine;
	double	cosine;

	sine = sin(rot_y * DEG2RAD);
	cosine = cos(rot_y * DEG2RAD);
	tmp = cosine * p->x + sine * p->z;
	p->z = -sine * p->x + cosine * p->z;
	p->x = tmp;
}

void	sphere_rotate_z(t_vec3 *p, double rot_z)
{
	double	tmp;
	double	sine;
	double	cosine;

	sine = sin(rot_z * DEG2RAD);
	cosine = cos(rot_z * DEG2RAD);
	tmp = cosine * p->x - sine * p->y;
	p->y = sine * p->x + cosine * p->y;
	p->x = tmp;
}

t_color	checkerboard_rectangle(t_list *obj, t_hit *hit)
{
	t_vec3	p;
	double	u;
	double	v;

	p = vec3_sub(hit->p, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.dir.x == 1.0)
	{
		u = -p.y / obj_cont(obj)->rt.width + 0.5;
		v = p.z / obj_cont(obj)->rt.height + 0.5;
	}
	else if (obj_cont(obj)->rt.dir.y == 1.0)
	{
		u = p.x / obj_cont(obj)->rt.width + 0.5;
		v = p.z / obj_cont(obj)->rt.height + 0.5;
	}
	else
	{
		u = p.x / obj_cont(obj)->rt.width + 0.5;
		v = -p.y / obj_cont(obj)->rt.height + 0.5;
	}
	if (sin(u * M_PI * obj_cont(obj)->material.cb_factor)
		* sin(v * M_PI * obj_cont(obj)->material.cb_factor) > 0)
		return ((t_color){0.0, 0.0, 0.0});
	else
		return (obj_color(obj, hit));
}
