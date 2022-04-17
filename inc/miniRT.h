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
#include <pthread.h>

# include "libft.h"
# include "global.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define	WIN_NAME    	"miniRT"

# define	THREADS	    	12

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_scene t_scene;

struct s_thread_data
{
	pthread_t	id;
	int			num;
	t_scene		*scene;
};

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
	FILE	*fp_ppm;
	bool	res_set;
	int		width;
	int		height;
	t_color	*color;
	t_vec3	pos;
	t_vec3	px;
	t_vec3	py;
};

struct s_bg
{
	bool	set;
	t_color	color[2];
};

typedef struct s_scene
{
	struct s_img			img;
	struct s_sampling		sampling;
	struct s_cam			cam;
	struct s_bg				bg;
	struct s_amb			amb;
	t_list					*l_is;
	t_list					*l_obj;
	struct s_thread_data	thread[THREADS];
}	t_scene;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

double	double_random_0_1(void);
int		print_error(char *s1, char *s2, char *s3, char *s4);

int scene_create(t_scene *scene, int argc, char **argv);
int	scene_destroy(t_scene *scene);

void scene_img_pos(t_scene *scene);

#endif // MINIRT_H
