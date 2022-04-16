#include "miniRT.h"
#include "../scene.h"

void	scene_print_info(t_scene *scene)
{
	printf("COUNTER:\n");
	scene_print_int(ft_lstsize(scene->l_obj), "objects:", NULL);
	scene_print_int(ft_lstsize(scene->l_is), "oversampl:", NULL);
	printf("\n");
}

void	scene_print_material(struct s_material *material)
{
	color_print(material->color);
	scene_print_double(material->surface[SURF_DIFFUSE], "DIFFUSE:", COLOR_PL);
	scene_print_double(material->surface[SURF_SPECULAR], "SPECULAR:", COLOR_PL);
	scene_print_double(material->surface[SURF_DIELECTRIC], "DIELEC:", COLOR_PL);
	scene_print_double(material->surface[SURF_EMISSION], "EMISSION:", COLOR_PL);
	scene_print_double(material->fuzz, "FUZZ:", NULL);
	scene_print_double(material->refraction_index, "REFRAC:", NULL);
}

void	scene_print_int(int num, const char *str, const char *color)
{
	if (color)
		printf("\t%s%-10s %8d%s\n", color, str, num, COLOR_NO);
	else
		printf("\t%-10s %8d\n", str, num);
}

void	scene_print_double(double num, const char *str, const char *color)
{
	if (color)
		printf("\t%s%-10s %8.3f%s\n", color, str, num, COLOR_NO);
	else
		printf("\t%-10s %8.3f\n", str, num);
}
