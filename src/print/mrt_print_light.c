#include "mrt_print.h"

void	print_light_sphere(t_list *light)
{
	t_light	*c_light;

	c_light = light_cont(light);
	printf("LIGHT SPHERE: (%p) -> (%p)\n", c_light, c_light->linked_c_obj);
	print_vec3(c_light->linked_c_obj->sp.pos, "pos:", COLOR_BL);
	print_scene_double(
		c_light->linked_c_obj->material.brightness, "bright:", COLOR_NO);
	print_scene_double(c_light->weight, "weight:", COLOR_NO);
	printf("\n");
}

void	print_light_rectangle(t_list *light)
{
	t_light	*c_light;

	c_light = light_cont(light);
	printf("LIGHT RECTANGLE: (%p) -> (%p)\n", c_light, c_light->linked_c_obj);
	print_vec3(c_light->linked_c_obj->di.pos, "pos:", COLOR_BL);
	print_scene_double(
		c_light->linked_c_obj->material.brightness, "bright:", COLOR_NO);
	print_scene_double(c_light->weight, "weight:", COLOR_NO);
	printf("\n");
}

void	print_light_disc(t_list *light)
{
	t_light	*c_light;

	c_light = light_cont(light);
	printf("LIGHT DISC: (%p) -> (%p)\n", c_light, c_light->linked_c_obj);
	print_vec3(c_light->linked_c_obj->di.pos, "pos:", COLOR_BL);
	print_scene_double(
		c_light->linked_c_obj->material.brightness, "bright:", COLOR_NO);
	print_scene_double(c_light->weight, "weight:", COLOR_NO);
	printf("\n");
}
