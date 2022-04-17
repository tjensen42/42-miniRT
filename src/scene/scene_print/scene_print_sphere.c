#include "miniRT.h"
#include "../scene.h"

void	print_sphere(t_list *obj)
{
	t_obj	*c_obj;

	c_obj = object_cont(obj);
	printf("SPHERE: (%p)\n", obj);
	vec3_print(c_obj->sp.pos, "pos:", COLOR_BL);
	scene_print_double(c_obj->sp.radius, "radius:", COLOR_NO);
	scene_print_material(&(c_obj->material));
	printf("\n");
}
