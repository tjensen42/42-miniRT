#ifndef PARSER_H
#define PARSER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "miniRT.h"
# include "global.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// GENERAL
# define	FILE_ENDING			".rt"

// ERRORS
# define	ERR_USAGE			"program usage........"
# define	ERR_FILE_EMPTY		"Empty scene file"
# define	ERR_FILE_TABS		"Tabs are not valid in a scene file"
# define	ERR_SCENE_INCOM		"Incomplete scene file" //better desc with resolution and specs stuff

# define	ERR_MISS_RES		""
# define	ERR_MISS_SAM		""
# define	ERR_MISS_CAM		""
# define	ERR_MISS_BG			""
# define	ERR_MISS_AMB		""
# define	ERR_MISS_OBJ		""

# define	ERR_PARSE			"Parsing failure"
# define	ERR_PARSE_DUP		"This object cannot be defined twice"

# define	ERR_INVAL_NUM		"Invalid number of arguments for object"
# define	ERR_INVAL_FILE		"Is not a valid scene (<name>.rt) file"
# define	ERR_INVAL_LINE		"Invalid line in scene file"
# define	ERR_INVAL_IDENT		"Invalid identifier in scene file"
# define	ERR_INVAL_OPTION	"Invalid option"
# define	ERR_INVAL_POS		"Invalid position"
# define	ERR_INVAL_DIR		"Invalid direction"
# define	ERR_INVAL_COLOR		"Invalid color (range [0-255])"
# define	ERR_INVAL_BRIGHT	"Invalid brightness (range [0.0-9999.99])"
# define	ERR_INVAL_FUZZ		"Invalid fuzz (range [])"
# define	ERR_INVAL_REFRAC	"Invalid refrac (range [])"
# define	ERR_INVAL_SURF		"Invalid surfaces"

// IDENTIFIERS
# define	IDENT_RES			"R"
# define	IDENT_SAMPLING		"S"
# define	IDENT_CAM			"C"
# define	IDENT_BG			"B"
# define	IDENT_AMB			"A"

# define	IDENT_LIGHT			"l"
# define	IDENT_PLANE			"pl"
# define	IDENT_SPHERE		"sp"
# define	IDENT_CYLINDER		"cy"


/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

struct s_ident
{
	const char	*ident;
	int			(*process_ident)(t_scene *scene, char **split, int line_num);
};


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		scene_parser(t_scene *scene, int argc, char **argv);
int		scene_open_rt_file(const char *input_file);
int		scene_check(t_scene *scene);
int		scene_setup(t_scene *scene);

int		process_img(t_scene *scene, char **split, int line_num);
int		process_sampling(t_scene *scene, char **split, int line_num);
int		process_cam(t_scene *scene, char **split, int line_num);
int		process_bg(t_scene *scene, char **split, int line_num);
int		process_amb(t_scene *scene, char **split, int line_num);
int		process_plane(t_scene *scene, char **split, int line_num);
int		process_sphere(t_scene *scene, char **split, int line_num);

int		scene_print(t_scene *scene);
int		scene_print_error(int line_num, const char *msg1, const char *msg2, const char *msg3);

void	scene_print_info(t_scene *scene);
void	scene_print_material(struct s_material *material);
void	scene_print_int(int num, const char *str, const char *color);
void	scene_print_double(double num, const char *str, const char *color);

void	print_img(struct s_img *img);
void	print_sampling(struct s_sampling *sampling);
void	print_cam(struct s_cam *cam);
void	print_bg(t_color bg[2]);
void	print_amb(struct s_amb *amb);
void	print_plane(t_list *obj);
void	print_sphere(t_list *obj);


// UTILS
int		process_material(t_material *material, char **split, int line_num);
int		str_to_vec3(const char *str, t_vec3 *vec3);
int		str_to_color(const char *str, t_color *color);
int		str_to_int(const char *str, int min, int max, int *res);
int		str_to_double(const char *str, int before_point, int after_point, double *res);
int		split_count(char **split);
int		str_count_chr(const char *str, const char c);

#endif // PARSER_H
