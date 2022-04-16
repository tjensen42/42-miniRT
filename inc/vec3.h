#ifndef VEC3_H
# define VEC3_H

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

bool	vec3_equal(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 a);
double	vec3_distance(t_vec3 a, t_vec3 b);
double	vec3_scalar_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_vector_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_linear_comb(double alpha, t_vec3 a, double beta, t_vec3 b);
t_vec3	vec3_scale(double alpha, t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
void	vec3_print(t_vec3 vec3, const char *str, const char *color);

#endif // VEC3_H
