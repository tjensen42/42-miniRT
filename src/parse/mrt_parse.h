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
# define ERR_FILE_EMPTY		"Empty scene file"
# define ERR_FILE_TABS		"Tabs are not valid in a scene file"

# define ERR_PARSE			"Parsing failure"
# define ERR_PARSE_DUP		"This object cannot be defined twice"

# define ERR_INVAL_NUM		"Invalid number of arguments for identifier"
# define ERR_INVAL_FILE		"Is not a valid scene (<name>.rt) file"
# define ERR_INVAL_LINE		"Invalid line in scene file"
# define ERR_INVAL_IDENT	"Invalid identifier in scene file"
# define ERR_INVAL_OPTION	"Invalid option"
# define ERR_INVAL_POS		"Invalid position"
# define ERR_INVAL_DIR		"Invalid direction"

# define ERR_INVAL_ROT		"Invalid rotation angles"
# define ERR_INVAL_RAD		"Invalid radius"
# define ERR_INVAL_WIDTH	"Invalid width"
# define ERR_INVAL_HEIGHT	"Invalid height"
# define ERR_INVAL_DEPTH	"Invalid depth"

# define ERR_MAX_SAMP		"Invalid number of max_samp"
# define ERR_REC_DEPTH		"Invalid import sampling"
# define ERR_IMPORT_SAMP	"Invalid import sampling"
# define ERR_COSINE_SAMP	"Invalid cosine sampling"
# define ERR_SAMP_SUM		"Invalid: import + cosine != 1.0"
# define ERR_INVAL_GAMMA	"Invalid gamma specification"

# define ERR_INVAL_CAM		"Cam look-from and look-at cannot be equal"
# define ERR_INVAL_LOOK		"Invalid look-at"
# define ERR_INVAL_FOV		"Invalid camera FOV (range [1-179])"

# define ERR_INVAL_RES		"Invalid resolution (range [10-10000])"
# define ERR_INVAL_LW		"Invalid light-weight"

# define ERR_INVAL_COLOR	"Invalid color (range [0-255])"
# define ERR_INVAL_BRIGHT	"Invalid brightness (range [0.0-9999.99])"
# define ERR_INVAL_FUZZ		"Invalid fuzz (range [])"
# define ERR_INVAL_REFRAC	"Invalid refrac (range [])"
# define ERR_INVAL_SURF		"Invalid surfaces"
# define ERR_INVAL_DIEL		"Value for DIELECTRIC must be 0.0 for 2D Objects"

// IDENTIFIERS
# define IDENT_RES			"R"
# define IDENT_SAMPLING		"S"
# define IDENT_CAM			"C"
# define IDENT_BG			"B"
# define IDENT_AMB			"A"

# define IDENT_TEXTURE		"t"
# define IDENT_LIGHT_SP		"ls"
# define IDENT_LIGHT_RT		"lr"
# define IDENT_LIGHT_DI		"ld"
# define IDENT_PLANE		"pl"
# define IDENT_SPHERE		"sp"
# define IDENT_CYLINDER		"cy"
# define IDENT_RECTANGLE	"rt"
# define IDENT_CUBOID		"cu"
# define IDENT_DISC			"di"
# define IDENT_TUBE			"tb"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int			int_from_str(const char *str, int min, int max, int *res);
int			double_from_str(const char *str, int before_point,
				int after_point, double *res);

int			parse_color(const char *str, t_color *color);
int			parse_vec3(const char *str, t_vec3 *vec3);
int			parse_material(t_material *material, char **split, int line_num);

int			parse_amb(t_scene *scene, char **split, int line_num);
int			parse_bg(t_scene *scene, char **split, int line_num);
int			parse_sampling(t_scene *scene, char **split, int line_num);
int			parse_cam(t_scene *scene, char **split, int line_num);
int			parse_img(t_scene *scene, char **split, int line_num);
int			parse_ppm(t_scene *scene, char **split, int line_num);

int			parse_obj_rectangle_dir(t_obj *c_obj, const char *dir);
f_intersec	parse_obj_rt_intersec(t_vec3 dir);

int			parse_texture(t_scene *scene, char **split, int line_num);
t_texture	*parse_c_texture_find(t_list *l_texture, const char *name);

int			parse_obj_plane(t_scene *scene, char **split, int line_num);
int			parse_obj_disc(t_scene *scene, char **split, int line_num);
int			parse_obj_tube(t_scene *scene, char **split, int line_num);
int			parse_obj_sphere(t_scene *scene, char **split, int line_num);
int			parse_obj_cylinder(t_scene *scene, char **split, int line_num);
int			parse_obj_rectangle(t_scene *scene, char **split, int line_num);
int			parse_obj_cuboid(t_scene *scene, char **split, int line_num);

int			parse_light_sphere(t_scene *scene, char **split, int line_num);
int			parse_light_disc(t_scene *scene, char **split, int line_num);
int			parse_light_rectangle(t_scene *scene, char **split, int line_num);

int			parse_scene(t_scene *scene, const char *file);

#endif // MRT_PARSE_H
