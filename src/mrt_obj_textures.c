# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "math/mrt_math.h"
# include "trace/mrt_trace.h"

t_color	texture_sphere(t_list *obj, t_hit *hit)
{
	t_vec3		p;
	double		u;
	double		v;
	t_texture	*c_texture;
	size_t		pixel;
	double		tmp;
	double		sine;
	double		cosine;

	c_texture = obj_cont(obj)->material.c_texture;
	p = vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos));
	if (obj_cont(obj)->sp.rot.z != 0.0)
	{
		sine = sin(obj_cont(obj)->sp.rot.z * DEG2RAD);
		cosine = cos(obj_cont(obj)->sp.rot.z * DEG2RAD);
		tmp = cosine * p.x - sine * p.y;
		p.y = sine * p.x + cosine * p.y;
		p.x = tmp;
	}
	if (obj_cont(obj)->sp.rot.y != 0.0)
	{
		sine = sin(obj_cont(obj)->sp.rot.y * DEG2RAD);
		cosine = cos(obj_cont(obj)->sp.rot.y * DEG2RAD);
		tmp = cosine * p.x + sine * p.z;
		p.z = - sine * p.x + cosine * p.z;
		p.x = tmp;
	}
	if (obj_cont(obj)->sp.rot.x != 0.0)
	{
		sine = sin(obj_cont(obj)->sp.rot.x * DEG2RAD);
		cosine = cos(obj_cont(obj)->sp.rot.x * DEG2RAD);
		tmp = cosine * p.y - sine * p.z;
		p.z = sine * p.y + cosine * p.z;
		p.y = tmp;
	}
	u = (atan2(-p.z, p.x) + M_PI) / (2.0 * M_PI);
	v = acos(p.y) / M_PI;
	pixel = (size_t)(v * c_texture->height) * c_texture->width + u * c_texture->width;
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
	p = vec3_subtract(hit->p, obj_cont(obj)->rt.pos);
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
	p = vec3_subtract(hit->p, obj_cont(obj)->rt.pos);
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
	p = vec3_subtract(hit->p, obj_cont(obj)->rt.pos);
	if (obj_cont(obj)->rt.dir.z < 0.0)
		u = -p.x / obj_cont(obj)->rt.width + 0.5;
	else
		u = p.x / obj_cont(obj)->rt.width + 0.5;
	v = -p.y / obj_cont(obj)->rt.height + 0.5;
	pixel = (size_t)(v * c_texture->height) * c_texture->width
		+ u * c_texture->width;
	return (c_texture->color[pixel]);
}
