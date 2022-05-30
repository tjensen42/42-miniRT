#include "mrt_trace.h"
#include "mrt_trace_onb.h"

static inline t_vec3 random_to_sphere(double radius, double distance_squared);

t_vec3	random_dir_to_sphere(t_list *light, t_hit *hit)
{
    t_onb	uvw;
	t_vec3	light_dir;
	double	distance_squared;
	t_obj	*c_obj;

	c_obj = light_cont(light)->linked_c_obj;
	light_dir = vec3_subtract(c_obj->sp.pos, hit->p);
    distance_squared = vec3_scalar_product(light_dir, light_dir);
    uvw = onb_build(vec3_normalize(light_dir));
    return (onb_transform(uvw, random_to_sphere(c_obj->sp.radius, distance_squared)));
}

static inline t_vec3 random_to_sphere(double radius, double distance_squared)
{
	t_vec3 vec3;
	double r1;
	double r2;
	double phi;

	r1 = ft_rand_double_0_1();
	r2 = ft_rand_double_0_1();
	vec3.z = 1.0 + r2 * (sqrt(1.0 - radius * radius / distance_squared) - 1.0); // aus pdf
	phi = 2.0 * M_PI * r1;
	vec3.x = cos(phi) * sqrt(1.0 - vec3.z * vec3.z);
	vec3.y = sin(phi) * sqrt(1.0 - vec3.z * vec3.z);
	return (vec3);
}

t_vec3	random_dir_to_disc(t_list *light, t_hit *hit)
{
	double	r1;
	double	r2;
	t_onb	uvw;
	t_vec3	rand_point;
	t_obj	*c_obj;

	c_obj = light_cont(light)->linked_c_obj;
	uvw = onb_build(c_obj->di.dir);
	while (1)
	{
		r1 = ft_rand_double(-(c_obj->di.radius), c_obj->di.radius);
		r2 = ft_rand_double(-(c_obj->di.radius), c_obj->di.radius);
		if (r1 * r1 + r2 * r2 <= c_obj->di.radius * c_obj->di.radius)
			break ;
	}
	rand_point = vec3_add(c_obj->di.pos, vec3_linear_comb(r1, uvw.u, r2, uvw.v));
	return (vec3_normalize(vec3_subtract(rand_point, hit->p)));
}

t_vec3	random_dir_to_rectangle(t_list *light, t_hit *hit)
{
	double	r1;
	double	r2;
	t_vec3	rand_point;
	t_obj	*c_obj;

	c_obj = light_cont(light)->linked_c_obj;
	r1 = ft_rand_double(c_obj->rt.width / -2.0, c_obj->rt.width / 2.0);
	r2 = ft_rand_double(c_obj->rt.height / -2.0, c_obj->rt.height / 2.0);
	if (fabs(c_obj->rt.dir.x) > 0.9)
		rand_point = vec3_add(c_obj->rt.pos, (t_vec3){0.0, r1, r2});
	else if (fabs(c_obj->rt.dir.y) > 0.9)
		rand_point = vec3_add(c_obj->rt.pos, (t_vec3){r1, 0.0, r2});
	else
		rand_point = vec3_add(c_obj->rt.pos, (t_vec3){r1, r2, 0.0});
	return (vec3_normalize(vec3_subtract(rand_point, hit->p)));
}
