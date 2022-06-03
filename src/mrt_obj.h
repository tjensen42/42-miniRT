#ifndef OBJ_H
# define OBJ_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "trace/mrt_trace.h"
# include "lib/libmlx/include/MLX42/MLX42.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define SURF_DIFFUSE		0
# define SURF_SPECULAR		1
# define SURF_DIELECTRIC	2
# define SURF_EMISSION		3

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_hit t_hit;

typedef t_color	(*f_color)(t_list *obj, t_hit *hit);

typedef struct s_texture
{
	char	*name;
	size_t	width;
	size_t	height;
	t_color	*color;
}	t_texture;

typedef struct s_material
{
	t_color			color;
	t_texture		*c_texture;
	f_color			get_color;
	int				cb_factor;
	double			surface[4];
	double			fuzz;
	double			refraction_index;
	double			brightness;
}	t_material;

typedef struct s_plane
{
	t_vec3		pos;
	t_vec3		dir;
}	t_plane;

typedef struct s_disc
{
	t_vec3		pos;
	t_vec3		dir;
	double		radius;
}	t_disc;

typedef struct s_sphere
{
	t_vec3		pos;
	t_vec3		rot;
	double		radius;
}	t_sphere;

typedef struct s_tube
{
	t_vec3		pos;
	t_vec3		dir;
	double		radius;
	double		height;
}	t_tube;

typedef struct s_rectangle
{
	t_vec3		pos;
	t_vec3		dir;
	double		width;
	double		height;
	t_vec3		rot;
	t_vec3		rel_pos;
}	t_rectangle;

typedef struct s_ray t_ray;
typedef struct s_hit t_hit;

typedef void	(*f_print)(t_list *obj);
typedef double	(*f_intersec)(t_list *obj, t_ray *ray, double t_min, double t_max);
typedef t_vec3	(*f_normal)(t_list *obj, t_hit *hit);

typedef struct	s_obj
{
	int				type;
	t_material		material;
	f_print			print;
	f_intersec		intersec;
	f_normal		normal;
	union
	{
		t_plane 	pl;
		t_disc		di;
		t_sphere	sp;
		t_tube		tb;
		t_rectangle	rt;
	};
}	t_obj;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// OBJECTS
t_list	*obj_new(int type);
int		obj_type(t_list *obj);
t_obj	*obj_cont(t_list *obj);
t_color	obj_color(t_list *obj, t_hit *hit __attribute__((unused)));

t_texture	*texture_cont(t_list *texture);
t_list	*texture_new(void);
void	c_texture_destroy(void *in);

t_color	checkerboard_sphere(t_list *obj, t_hit *hit);
t_color	texture_sphere(t_list *obj, t_hit *hit);

t_color	texture_rectangle_x(t_list *obj, t_hit *hit);
t_color	texture_rectangle_y(t_list *obj, t_hit *hit);
t_color	texture_rectangle_z(t_list *obj, t_hit *hit);
t_color	checkerboard_rectangle_x(t_list *obj, t_hit *hit);
t_color	checkerboard_rectangle_y(t_list *obj, t_hit *hit);
t_color	checkerboard_rectangle_z(t_list *obj, t_hit *hit);

#endif // OBJ_H
