#ifndef MRT_PRINT_H
# define MRT_PRINT_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "mrt_color.h"
# include "mrt_vec3.h"
# include "mrt_scene.h"
# include "mrt_obj.h"
# include "mrt_light.h"

# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

void	print_color(t_color color);

void	print_vec3(t_vec3 vec3, const char *str, const char *color);

void	print_material(t_material *material);

int		print_scene(t_scene *scene);
void	print_scene_int(int num, const char *str, const char *color);
void	print_scene_double(double num, const char *str, const char *color);

void	print_textures(t_list *l_texture);

void	print_obj_plane(t_list *obj);
void	print_obj_disc(t_list *obj);
void	print_obj_sphere(t_list *obj);
void	print_obj_tube(t_list *obj);
void	print_obj_rectangle(t_list *obj);

void	print_light_sphere(t_list *is);
void	print_light_rectangle(t_list *light);
void	print_light_disc(t_list *light);

int		print_error(char *s1, char *s2, char *s3, char *s4);
int		print_error_scene(int line_num, const char *msg1, const char *msg2, const char *msg3);

#endif // MRT_PRINT_H
