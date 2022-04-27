#include "mrt_print.h"

void	print_is(t_list *is)
{
	t_is	*c_is;

	c_is = is_cont(is);
	printf("IMPORTANT SAMPLING: (%p) -> (%p)\n", is, c_is->linked_obj);
	print_vec3(c_is->pos, "pos:", COLOR_BL);
	print_scene_double(c_is->radius, "radius:", COLOR_NO);
}
