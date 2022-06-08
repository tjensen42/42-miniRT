#ifndef MRT_TRACE_H
# define MRT_TRACE_H

# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "mrt_light.h"
# include "mrt_scene.h"
# include "mrt_trace_onb.h"
# include "math/mrt_math.h"

# define INSIDE		0
# define OUTSIDE	1

typedef struct s_hit
{
	bool	side;
	double	t;
	t_vec3	p;
	t_vec3	normal;
}	t_hit;

typedef struct s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}	t_ray;

t_vec3	random_in_unit_sphere(void);
t_vec3	random_cosine_direction(void);
t_vec3	random_cosine_direction_onb(t_vec3 normal);

t_vec3	dielectric(t_list *obj, t_ray *ray, t_hit *hit);
t_vec3	diffuse(t_list *obj, t_ray *ray, t_hit *hit);
t_vec3	specular(t_list *obj, t_ray *ray, t_hit *hit);

t_color	trace(t_scene *scene, t_ray *ray, int depth);

double	intersect_plane(t_list *obj, t_ray *ray, double t_min, double t_max);
double	intersect_disc(t_list *obj, t_ray *ray, double t_min, double t_max);
double	intersect_sphere(t_list *obj, t_ray *ray, double t_min, double t_max);
double	intersect_tube(t_list *obj, t_ray *ray, double t_min, double t_max);
double	intersect_rectangle_z(t_list *obj, t_ray *ray, double t_min,
			double t_max);
double	intersect_rectangle_y(t_list *obj, t_ray *ray, double t_min,
			double t_max);
double	intersect_rectangle_x(t_list *obj, t_ray *ray, double t_min,
			double t_max);

void	intersect_rectangle_move_rotate_ray(t_ray *ray, t_list *obj);

t_vec3	normal_plane(t_list *obj, t_hit *hit);
t_vec3	normal_disc(t_list *obj, t_hit *hit);
t_vec3	normal_sphere(t_list *obj, t_hit *hit);
t_vec3	normal_tube(t_list *obj, t_hit *hit);
t_vec3	normal_rectangle(t_list *obj, t_hit *hit);

double	pdf_sphere(t_list *light, t_hit *hit);
double	pdf_disc(t_list *light, t_hit *hit);
double	pdf_rectangle(t_list *light, t_hit *hit);

t_vec3	random_dir_to_sphere(t_list *light, t_hit *hit);
t_vec3	random_dir_to_disc(t_list *light, t_hit *hit);
t_vec3	random_dir_to_rectangle(t_list *light, t_hit *hit);

void	sphere_rotate_x(t_vec3 *p, double rot_x);
void	sphere_rotate_y(t_vec3 *p, double rot_y);
void	sphere_rotate_z(t_vec3 *p, double rot_z);

t_vec3	diffuse_cosine_sampling(t_hit *hit);
t_vec3	diffuse_light_sampling(t_list *l_light, t_hit *hit);
double	pdf_scaling(t_scene *scene, t_ray *ray, t_hit *hit);

t_list	*calc_hit(t_list *l_obj, t_ray *ray, t_hit *hit);

#endif // MRT_TRACE_H
