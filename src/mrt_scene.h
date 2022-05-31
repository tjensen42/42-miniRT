#ifndef SCENE_H
# define SCENE_H

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

# define THREADS			12

# define ERR_SCENE_INCOM	"Incomplete scene file"
# define ERR_MISS_RES		""
# define ERR_MISS_SAM		""
# define ERR_MISS_CAM		""
# define ERR_MISS_BG		""
# define ERR_MISS_AMB		""
# define ERR_MISS_OBJ		""

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_scene t_scene;

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
	double	cosine_samp;
	double	import_samp;
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
	bool	ppm;
	FILE	*fp_ppm;
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
	struct s_img			img;
	struct s_sampling		sampling;
	struct s_cam			cam;
	struct s_bg				bg;
	struct s_amb			amb;
	t_list					*l_obj;
	t_list					*l_light;
	struct s_thread_data	thread[THREADS];
}	t_scene;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// SCENE
int		scene_create(t_scene *scene, const char *file);
int		scene_destroy(t_scene *scene);

void	scene_calc_img_pos(t_scene *scene);

#endif // SCENE_H
