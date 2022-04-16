#ifndef MINIRT_H
# define MINIRT_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# include "libft.h"
# include "global.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define	WIN_NAME    	"miniRT"

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

// SCENE
struct s_sampling
{
	bool	set;
	int		max_samp;
	int		recursion_depth;
	double	cosine_samp;
	double	import_samp;
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
	int			fov;
};

struct s_img
{
	bool	ppm;
	bool	res_set;
	int		width;
	int		height;
	t_color	*ptr;
	t_vec3	img_pos;
	t_vec3	img_x;
	t_vec3	img_y;
};

typedef struct s_scene
{
	struct s_img		img;
	struct s_sampling	sampling;
	struct s_cam		cam;
	bool				bg_set;
	t_color				bg[2];
	struct s_amb		amb;
	t_list				*l_is;
	t_list				*l_obj;
}	t_scene;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int scene_create(t_scene *scene, int argc, char **argv);
int	scene_destroy(t_scene *scene);

#endif // MINIRT_H
