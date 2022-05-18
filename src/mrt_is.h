#ifndef MRT_IS_H
# define MRT_IS_H

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

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_scene t_scene;
typedef struct s_hit t_hit;

typedef void	(*f_print)(t_list *is);
typedef double	(*pdf_value)(t_scene *scene, t_list *is, t_hit *hit);
typedef t_vec3	(*random_dir)(t_list *is, t_hit *hit);

typedef struct	s_is
{
	t_vec3			pos;
	double			radius;
	double			weight;
	f_print			print;
	pdf_value		pdf_value;
	random_dir		random_dir;
	t_list			*linked_obj;
}	t_is;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// OBJECTS
t_list	*is_new(void);
t_is	*is_cont(t_list *is);

#endif // MRT_IS_H
