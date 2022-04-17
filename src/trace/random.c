#include "miniRT.h"

t_vec3 vec3_random_cosine_dir(void)
{
	double	r1;
	double	r2;
	double	phi;
	t_vec3	vec3;

	r1 = double_random_0_1();
	r2 = double_random_0_1();
	vec3.z = sqrt(1 - r2);
	phi = 2.0 * M_PI * r1;
	vec3.x = cos(phi) * sqrt(r2);
	vec3.y = sin(phi) * sqrt(r2);
	return (vec3);
}
