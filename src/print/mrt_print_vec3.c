#include "mrt_print.h"

void	print_vec3(t_vec3 vec3, const char *str, const char *color)
{
	printf("\t%s%-10s %8.3f %8.3f %8.3f%s\n",
		color, str, vec3.x, vec3.y, vec3.z, "\033[m");
}
