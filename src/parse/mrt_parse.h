/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:56:16 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 15:34:55 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_PARSE_H
# define MRT_PARSE_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "lib/libft/inc/libft.h"
# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_scene.h"
# include "mrt_obj.h"
# include "mrt_light.h"
# include "print/mrt_print.h"

# include <errno.h>
# include <stdbool.h>

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// ERRORS
# define ERR_FILE_TABS		"Tabs are not allowed"

# define ERR_PARSE			"Parsing error"
# define ERR_DUPLICATE		"Duplicate identifier"

# define ERR_NUM_PARA		"Wrong number of parameters"
# define ERR_FILE			"Invalid scene file (<scene>.rt)"
# define ERR_ID				"Invalid identifier"

# define VEC3_RANGE			"3x <double> [-999999.9999,+999999.9999]"

# define ERR_POS			"Invalid position"
# define ERR_DIR			"Invalid direction"

# define ERR_ROT			"Invalid rotation angles"
# define ERR_RAD			"Invalid radius"
# define ERR_WIDTH			"Invalid width"
# define ERR_HEIGHT			"Invalid height"
# define ERR_DEPTH			"Invalid depth"

# define ERR_CB				"Invalid checkerboard factor"
# define ERR_TEXTURE		"Invalid texture"

# define ERR_MAX_SAMP		"Invalid number of samples: <int> [1,9999]"
# define ERR_REC_DEPTH		"Invalid bounces: <int> [1,1000]"
# define ERR_IMPORT_SAMP	"Invalid light sampling: <double> [0.0,9.9999]"
# define ERR_COSINE_SAMP	"Invalid cosine sampling: <double> [0.0,9.9999]"
# define ERR_SAMP_SUM		"Invalid sampling: light + cosine = 1.0"
# define ERR_GAMMA			"Invalid gamma: <bool> true/false"

# define ERR_CAM_LOOK		"Cam look-from and look-at cannot be equal"
# define ERR_LOOK_AT		"Invalid look-at"
# define ERR_FOV			"Invalid camera FOV (range [1,179])"

# define ERR_RES			"Invalid resolution: <int> [10,10000]"
# define ERR_LIGHT_SF		"Invalid sampling factor"

# define ERR_COLOR			"Invalid color: 3x <int> [0,255]"
# define ERR_BRIGHT			"Invalid brightness: <double> [0.0,9999.99]"
# define ERR_FUZZ			"Invalid fuzz: <double> [0.0,9.99]"
# define ERR_REFRACTION		"Invalid refraction index: <double> [1.00,2.00]"
# define ERR_SURF			"Invalid surfaces: 3x <double> [0.0,1.00]"
# define ERR_SURF_SUM		"Surface parameters must add up to 1.0"
# define ERR_DIELECTRIC		"2D objects cannot be dielectric"

// IDENTIFIERS
# define ID_RES				"R"
# define ID_SAMPLING		"S"
# define ID_CAM				"C"
# define ID_BG				"B"
# define ID_AMB				"A"

# define ID_TEXTURE			"tx"
# define ID_LIGHT_SP		"ls"
# define ID_LIGHT_RT		"lr"
# define ID_LIGHT_DI		"ld"
# define ID_PLANE			"pl"
# define ID_SPHERE			"sp"
# define ID_CYLINDER		"cy"
# define ID_RECTANGLE		"rt"
# define ID_CUBOID			"cu"
# define ID_DISC			"di"
# define ID_TUBE			"tb"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int				int_from_str(const char *str, int min, int max, int *res);
int				double_from_str(const char *str, int before_point,
					int after_point, double *res);

int				parse_color(const char *str, t_color *color);
int				parse_vec3(const char *str, t_vec3 *vec3);
int				parse_material(t_material *material, char **split,
					int line_num);

int				parse_amb(t_scene *scene, char **split, int line_num);
int				parse_bg(t_scene *scene, char **split, int line_num);
int				parse_sampling(t_scene *scene, char **split, int line_num);
int				parse_cam(t_scene *scene, char **split, int line_num);
int				parse_res(t_scene *scene, char **split, int line_num);
int				parse_ppm(t_scene *scene, char **split, int line_num);

int				parse_obj_rectangle_dir(t_obj *c_obj, const char *dir);
t_f_intersect	parse_obj_rt_intersect(t_vec3 dir);

int				parse_texture(t_scene *scene, char **split, int line_num);
t_texture		*parse_c_texture_find(t_list *l_texture, const char *name);

int				parse_obj_plane(t_scene *scene, char **split, int line_num);
int				parse_obj_disc(t_scene *scene, char **split, int line_num);
int				parse_obj_tube(t_scene *scene, char **split, int line_num);
int				parse_obj_sphere(t_scene *scene, char **split, int line_num);
int				parse_obj_cylinder(t_scene *scene, char **split, int line_num);
int				parse_obj_rectangle(t_scene *scene, char **split, int line_num);
int				parse_obj_cuboid(t_scene *scene, char **split, int line_num);

int				parse_light_sphere(t_scene *scene, char **split, int line_num);
int				parse_light_disc(t_scene *scene, char **split, int line_num);
int				parse_light_rectangle(t_scene *scene, char **split,
					int line_num);

int				parse_scene(t_scene *scene, const char *file);

#endif // MRT_PARSE_H
