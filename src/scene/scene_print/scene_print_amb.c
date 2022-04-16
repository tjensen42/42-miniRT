#include "miniRT.h"
#include "../scene.h"

void	print_amb(struct s_amb *amb)
{
	printf("AMBIENT:\n");
	color_print(amb->color);
	scene_print_double(amb->brightness, "bright", NULL);
	printf("\n");
}
