/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:54:06 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:54:10 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_obj	t_obj;
typedef struct s_scene	t_scene;
typedef struct s_hit	t_hit;

typedef void			(*t_f_print)(t_list *is);
typedef double			(*t_f_pdf_val)(t_list *is, t_hit *hit);
typedef t_vec3			(*t_f_random_dir)(t_list *is, t_hit *hit);

typedef struct s_light
{
	double			weight;
	t_f_print		print;
	t_f_pdf_val		pdf_value;
	t_f_random_dir	random_dir;
	t_obj			*linked_c_obj;
}	t_light;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// OBJECTS
t_list	*light_new(void);
t_light	*light_cont(t_list *is);

#endif // MRT_LIGHT_H
