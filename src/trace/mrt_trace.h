#ifndef MRT_TRACE_H
# define MRT_TRACE_H

# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "mrt_is.h"
# include "mrt_scene.h"
# include "mrt_trace_onb.h"
# include "math/mrt_math.h"


#define INSIDE	false
#define OUTSIDE	true

typedef struct s_hit
{
	double	t;
	t_vec3	p;
	t_vec3	normal;
	bool	side;
}	t_hit;

// RAY
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

double	intersec_plane(t_list *obj, t_ray *ray, double t_min, double t_max);
double	intersec_sphere(t_list *obj, t_ray *ray, double t_min, double t_max);
double	intersec_cylinder(t_list *obj, t_ray *ray, double t_min, double t_max);

t_vec3	normal_plane(t_list *obj, t_hit *hit);
t_vec3	normal_sphere(t_list *obj, t_hit *hit);
t_vec3	normal_cylinder(t_list *obj, t_hit *hit);

double	pdf_sphere(t_scene *scene, t_list *is, t_hit *hit);
t_vec3	random_dir_to_sphere(t_list *is, t_hit *hit);

t_list	*calc_hit(t_list *l_obj, t_ray *ray, t_hit *hit);

#endif // MRT_TRACE_H