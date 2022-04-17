#include "miniRT.h"
#include "../scene.h"

void	print_bg(struct s_bg *bg)
{
	printf("BACKGROUND:\n");
	color_print(bg->color[0]);
	color_print(bg->color[1]);
	printf("\n");
}
