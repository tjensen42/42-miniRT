/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_scene.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:54:44 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:54:45 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_SCENE_H
# define MRT_SCENE_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "lib/libft/inc/libft.h"
# include "math/mrt_math.h"
# include "mrt_color.h"
# include "mrt_vec3.h"

# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# ifndef THREADS
#  define THREADS			8
# endif

# define ERR_SCENE			"Incomplete scene file"
# define ERR_MISS_RES		"No resolution"
# define ERR_MISS_SAM		"No sampling specifications"
# define ERR_MISS_CAM		"No camera"
# define ERR_MISS_BG		"No background"
# define ERR_MISS_AMB		"No ambient light"
# define ERR_MISS_OBJ		"No objects or lights"

# define ERR_WEIGHT_SUM		"Invalid sampling factor sum for lights"

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_scene	t_scene;

struct s_ident
{
	const char	*ident;
	int			(*process_ident)(t_scene *scene, char **split, int line_num);
};

typedef struct s_thread_data
{
	pthread_t	id;
	int			num;
	t_scene		*scene;
	void		*mlx_img;
}	t_thread;

// SCENE
struct s_sampling
{
	bool	set;
	int		samp;
	int		max_samp;
	int		recursion_depth;
	double	cosine;
	double	light;
	bool	gamma_correction;
};

struct s_amb
{
	bool		set;
	double		brightness;
	t_color		color;
};

struct s_cam
{
	bool		set;
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		pos_initial;
	t_vec3		dir_initial;
	int			fov;
};

struct s_img
{
	bool	res_set;
	int		width;
	int		height;
	t_color	*pixel;
	t_vec3	pos;
	t_vec3	px;
	t_vec3	py;
	t_vec3	qx;
	t_vec3	qy;
};

struct s_bg
{
	bool	set;
	t_color	color[2];
};

typedef struct s_scene
{
	struct s_img		img;
	struct s_sampling	sampling;
	struct s_cam		cam;
	struct s_bg			bg;
	struct s_amb		amb;
	t_list				*l_obj;
	t_list				*l_light;
	t_list				*l_textures;
	t_thread			thread[THREADS];
}	t_scene;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// SCENE
int		scene_create(t_scene *scene, const char *file);
void	scene_destroy(t_scene *scene);

void	scene_print(t_scene *scene);

int		scene_norm_light_weights(t_list *l_light);
void	scene_calc_img_pos(t_scene *scene);

#endif // MRT_SCENE_H
