#include "mrt_print.h"

void	print_material(t_material *material)
{
	print_color(material->color);
	print_scene_double(material->surface[SURF_DIFFUSE], "DIFFUSE:", COLOR_PL);
	print_scene_double(material->surface[SURF_SPECULAR], "SPECULAR:", COLOR_PL);
	print_scene_double(material->surface[SURF_DIELECTRIC], "DIELEC:", COLOR_PL);
	print_scene_double(material->surface[SURF_EMISSION], "EMISSION:", COLOR_PL);
	print_scene_double(material->fuzz, "FUZZ:", NULL);
	print_scene_double(material->refraction_index, "REFRAC:", NULL);
}
