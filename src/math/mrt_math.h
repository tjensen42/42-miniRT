#ifndef MRT_MATH_H
# define MRT_MATH_H

# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_scene.h"

# include <math.h>

# define DEG2RAD		(M_PI/180.0)

t_color	color_add(t_color c1, t_color c2);
t_color	color_scale(double f, t_color c1);
t_color	color_multiply(t_color c1, t_color c2);

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(double alpha, t_vec3 a);
t_vec3	vec3_linear_comb(double alpha, t_vec3 a, double beta, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 a);

bool	vec3_equal(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 a);
double	vec3_distance(t_vec3 a, t_vec3 b);
double	vec3_scalar_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_vector_product(t_vec3 a, t_vec3 b);

#endif // MRT_MATH_H
