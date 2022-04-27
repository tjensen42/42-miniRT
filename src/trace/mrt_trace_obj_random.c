#include "mrt_trace.h"
#include "mrt_trace_onb.h"

static inline t_vec3 random_to_sphere(double radius, double distance_squared);

t_vec3	random_dir_to_sphere(t_list *is, t_hit *hit)
{
    t_onb	uvw;
	t_vec3	is_dir;
	double	distance_squared;

	is_dir = vec3_subtract(is_cont(is)->pos, hit->p);
    distance_squared = vec3_scalar_product(is_dir, is_dir);

    uvw = onb_build(vec3_normalize(is_dir));
    return (onb_transform(uvw, random_to_sphere(is_cont(is)->radius, distance_squared)));
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
