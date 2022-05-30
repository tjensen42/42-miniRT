#ifndef MRT_LIGHT_H
# define MRT_LIGHT_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_obj.h"
# include "trace/mrt_trace.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_obj t_obj;
typedef struct s_scene t_scene;
typedef struct s_hit t_hit;

typedef void	(*f_print)(t_list *is);
typedef double	(*f_pdf_value)(t_scene *scene, t_list *is, t_hit *hit);
typedef t_vec3	(*f_random_dir)(t_list *is, t_hit *hit);

typedef struct	s_light
{
	double			weight;
	f_print			print;
	f_pdf_value		pdf_value;
	f_random_dir	random_dir;
	t_obj			*linked_c_obj;
}	t_light;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// OBJECTS
t_list	*light_new(void);
t_light	*light_cont(t_list *is);

#endif // MRT_LIGHT_H
