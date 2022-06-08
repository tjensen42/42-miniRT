#include "mrt_trace.h"

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	vec3;

	while (1)
	{
		vec3.x = -1.0 + (rand() / (double)(RAND_MAX / 2.0));
		vec3.y = -1.0 + (rand() / (double)(RAND_MAX / 2.0));
		vec3.z = -1.0 + (rand() / (double)(RAND_MAX / 2.0));
		if (vec3_dot(vec3, vec3) < 1.0)
			return (vec3);
	}
}

t_vec3	random_cosine_direction_onb(t_vec3 normal)
{
	t_onb	uvw;

	uvw = onb_build(normal);
	return (onb_transform(uvw, random_cosine_direction()));
}

t_vec3	random_cosine_direction(void)
{
	double	r1;
	double	r2;
	double	phi;
	t_vec3	vec3;

	r1 = ft_rand_double_0_1();
	r2 = ft_rand_double_0_1();
	vec3.z = sqrt(1 - r2);
	phi = 2 * M_PI * r1;
	vec3.x = cos(phi) * sqrt(r2);
	vec3.y = sin(phi) * sqrt(r2);
	return (vec3);
}
