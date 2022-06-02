# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "math/mrt_math.h"
# include "trace/mrt_trace.h"

t_color	checkerboard_sphere(t_list *obj, t_hit *hit)
{
	t_vec3	p;
	double	theta;
	double	phi;
	double	u, v;

	p = vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos));
	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + M_PI;
	u = phi / (2.0 * M_PI);
	v = theta / M_PI;
	if (sin(u * 2.0 * M_PI * 20) * sin(v * M_PI * 20) > 0)
		return ((t_color){1.0, 0.0, 0.0});
	else
		return ((t_color){1.0, 1.0, 1.0});
}

t_color	texture_sphere(t_list *obj, t_hit *hit)
{
	t_vec3	p;
	double	u;
	double	v;
	t_texture *c_texture;
	int pixel;

	c_texture = obj_cont(obj)->material.c_texture;
	p = vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos));
	u = (atan2(-p.z, p.x) + M_PI) / (2.0 * M_PI);
	v = acos(p.y) / M_PI;
	/*if (sin(u * 2.0 * M_PI * 20) * sin(v * M_PI * 20) > 0)
		return ((t_color){1.0, 0.0, 0.0});
	else
		return ((t_color){1.0, 1.0, 1.0});*/
	pixel = (int)(v * c_texture->height) * c_texture->width + u * c_texture->width;
	// printf("%d %f\n", pixel, u);
	return (c_texture->color[pixel]);
}

// t_color	texture_sphere(t_list *obj, t_hit *hit)
// {
// 	t_vec3	p;
// 	double	theta;
// 	double	phi;

// 	p = vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->sp.pos));
// 	theta = acos(-p.y);
// 	phi = atan2(-p.z, p.x) + M_PI;
// 	if (sin(phi * 20) * sin(theta * 20) > 0)

// 	else

// }

// t_color obj_texture(t_list *obj, t_hit *hit)
// {
// 	return (obj_cont(obj)->material.texture[hit->u][hit->u]);
// }

// t_color obj_checkerboard(t_list *obj, t_hit *hit)
// {
// 	if (sin(hit->u * 10) * sin(hit->v * 10) > 0)
// 		return ((t_color){1.0, 0.0, 0.0});
// 	else
// 		return ((t_color){1.0, 1.0, 1.0});
// }


// t_color	checkerboard_rectangle_x(t_list *obj, t_hit *hit)
// {
// 	t_vec3	p;

// 	p = vec3_normalize(vec3_subtract(hit->p, obj_cont(obj)->rt.pos));

// }
