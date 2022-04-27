#ifndef OBJ_H
# define OBJ_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "trace/mrt_trace.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define SURF_DIFFUSE		0
# define SURF_SPECULAR		1
# define SURF_DIELECTRIC	2
# define SURF_EMISSION		3

# define CY_CAP_NONE		1
# define CY_CAP_TOP			2
# define CY_CAP_BOTTOM		4
# define CY_CAP_BOTH		8

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_material
{
	t_color	color;
	double	surface[4];
	double	fuzz;
	double	refraction_index;
	double	brightness;
}	t_material;

typedef struct s_plane
{
	t_vec3		pos;
	t_vec3		dir;
}	t_plane;

typedef struct s_sphere
{
	t_vec3		pos;
	double		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3		pos;
	t_vec3		dir;
	double		radius;
	double		height;
	int			caps;
}	t_cylinder;

typedef struct s_ray t_ray;
typedef struct s_hit t_hit;

typedef void	(*print)(t_list *obj);
typedef double	(*intersec)(t_list *obj, t_ray *ray, double t_min, double t_max);
typedef t_vec3	(*normal)(t_list *obj, t_hit *hit);

typedef struct	s_obj
{
	int				type;
	t_material		material;
	print			print;
	intersec		intersec;
	normal			normal;
	union
	{
		t_plane 	pl;
		t_sphere	sp;
		t_cylinder	cy;
	};
}	t_obj;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// OBJECTS
t_list	*obj_new(int type);
int		obj_type(t_list *obj);
t_obj	*obj_cont(t_list *obj);

#endif // OBJ_H
