#include "miniRT.h"

bool	vec3_equal(t_vec3 a, t_vec3 b)
{
	return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}

double	vec3_length(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double	vec3_distance(t_vec3 a, t_vec3 b)
{
	return (vec3_length(vec3_subtract(a, b)));
}

double	vec3_scalar_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_vector_product(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec3_subtract(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_linear_comb(double alpha, t_vec3 a, double beta, t_vec3 b)
{
	return (vec3_add(vec3_scale(alpha, a), vec3_scale(beta, b)));
}

t_vec3	vec3_scale(double alpha, t_vec3 a)
{
	return ((t_vec3){alpha * a.x, alpha * a.y, alpha * a.z});
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	alpha;
	t_vec3	b;

	alpha = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	b.x = alpha * a.x;
	b.y = alpha * a.y;
	b.z = alpha * a.z;
	return (b);
}

void	vec3_print(t_vec3 vec3, const char *str, const char *color)
{
	printf("\t%s%-10s %8.3f %8.3f %8.3f%s\n",
		color, str, vec3.x, vec3.y, vec3.z, COLOR_NO);
}
