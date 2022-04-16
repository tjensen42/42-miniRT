#include "miniRT.h"
#include "../scene.h"

void	print_bg(t_color bg[2])
{
	printf("BACKGROUND:\n");
	color_print(bg[0]);
	color_print(bg[1]);
	printf("\n");
}
