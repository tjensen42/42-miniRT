#ifndef OBJECT_H
# define OBJECT_H

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define	OBJ_PLANE		0
# define	OBJ_SPHERE		1
# define	OBJ_CYLINDER	2

# define	SURF_DIFFUSE	0
# define	SURF_SPECULAR	1
# define	SURF_DIELECTRIC	2
# define	SURF_EMISSION	3

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

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
}	t_cylinder;

typedef struct s_material
{
	t_color	color;
	double	surface[4];
	double	fuzz;
	double	refraction_index;
}	t_material;

typedef void (*print)(t_list *obj);

typedef struct	s_obj
{
	int				type;
	t_material		material;
	print			print;
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

t_list	*object_new(int type);
int		object_type(t_list *obj);
t_obj	*object_cont(t_list *obj);

#endif // VEC3_H
